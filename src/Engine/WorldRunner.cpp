#include <map>
#include <string>
#include <vector>

#include <GL/glut.h>

#include "Classes/KeySignal.hpp"
#include "Classes/Mono.hpp"
#include "Classes/MonoCluster.hpp"
#include "Classes/MonoOrbit.hpp"
#include "Engine/MonoEffectManager.hpp"
#include "Engine/WorldReader.hpp"
#include "Engine/WorldRunner.hpp"
#include "GlutTools/GlutCamera.hpp"
#include "GlutTools/GlutDraw.hpp"
#include "GlutTools/GlutEvent.hpp"
#include "GlutTools/GlutUtil.hpp"

namespace worldRunner
{
    double monoGraphicScale = 1.0;
    double monoGraphicSize = 0.01;
    double deltaTimes = 1.0 / 16384; // 2^(-14)
    double clusterThreshold = 0.3913165154385;
    bool showMonoIndexLabel = false;
    std::vector<MonoTemplate*> monoTemplates;

    int orbitRemaining = 10;
    int orbitThinning = 2;

    KeySignal keySignals[8] = {KeySignal('r', 1.0), KeySignal('t', 1.0),
                               KeySignal('c', 1.0), KeySignal('v', 1.0),
                               KeySignal('f', 1.0), KeySignal('g', 1.0),
                               KeySignal('[', 1.0), KeySignal(']', 1.0)};
    KeySignal& resetKeySignal = keySignals[0];
    KeySignal& reloadKeySignal = keySignals[1];
    KeySignal& playKeySignal = keySignals[2];
    KeySignal& stepKeySignal = keySignals[3];
    KeySignal& toggleClusterKeySignal = keySignals[4];
    KeySignal& toggleOrbitKeySignal = keySignals[5];
    KeySignal& shortenOrbitKeySignal = keySignals[6];
    KeySignal& lengthenOrbitKeySignal = keySignals[7];

    bool playWorld = true;
    bool showCluster = true;
    bool showOrbit = true;

    void addMonoTemplate(
        MonoTemplate* mt,
        std::map<std::string, std::vector<std::string>>& properties
    )
    {
        mt->script = properties;

        mt->setFromScript();

        monoTemplates.push_back(mt);
    }

    void deleteMonoTemplates()
    {
        for (MonoTemplate* mt : monoTemplates)
            delete mt;

        monoTemplates.clear();
    }

    void reset()
    {
        monoEffectManager::clear();

        for (MonoTemplate* mt : monoTemplates)
            mt->init();
    }

    void reload()
    {
        worldReader::readNueFile();
        glutCamera::reset();

        reset();
    }

    void update()
    {
        namespace mem = monoEffectManager;

        for (KeySignal& keySignal : keySignals)
        {
            keySignal.setState(glutEvent::pressedKeys[keySignal.getKey()]);
            keySignal.updateState();
        }

        if (playKeySignal.getIsPressed())
            playWorld = !playWorld;

        if (toggleClusterKeySignal.getIsPressed())
            showCluster = !showCluster;

        if (toggleOrbitKeySignal.getIsPressed())
            showOrbit = !showOrbit;

        if (shortenOrbitKeySignal.getIsPressed() &&
            orbitRemaining - orbitThinning > orbitThinning)
            orbitRemaining -= orbitThinning;

        if (lengthenOrbitKeySignal.getIsPressed())
            orbitRemaining += orbitThinning;

        if (resetKeySignal.getIsPressed())
        {
            reset();
        }
        else if (reloadKeySignal.getIsPressed())
        {
            reload();
        }
        else if (!playWorld && !stepKeySignal.getIsPressed())
        {
            return;
        }

        mem::calcNextState(
            deltaTimes, showCluster ? clusterThreshold : 0, orbitRemaining
        );
    }

    void drawMonos()
    {
        namespace mem = monoEffectManager;

        for (int i = 0; i < mem::monos.size(); i++)
        {
            glColor3d(1.0, 1.0, 1.0);

            Vector3 position = mem::monos[i].position * monoGraphicScale;

            glutDraw::drawObject(
                position, [=]() { glutSolidSphere(monoGraphicSize, 8, 8); }
            );

            if (showMonoIndexLabel)
            {
                glColor3d(0.25, 0.25, 0.25);
                glRasterPos3d(position.x, position.y, position.z);
                glutUtil::drawString(std::to_string(i));
            }
        }
    }

    void drawClusters()
    {
        namespace mem = monoEffectManager;

        glColor3d(1.0, 0.0, 0.0);

        for (MonoCluster& cluster : mem::clusters)
        {
            glutDraw::drawObject(
                cluster.getCenterPosition() * monoGraphicScale,
                [=]() { glutSolidSphere(monoGraphicSize, 8, 8); }
            );

            for (Mono& monoA : cluster.monos)
            {
                GLdouble monoPositionA[] = {
                    monoA.position.x * monoGraphicScale,
                    monoA.position.y * monoGraphicScale,
                    monoA.position.z * monoGraphicScale
                };

                for (Mono& monoB : cluster.monos)
                {
                    if (monoA.index >= monoB.index)
                        continue;

                    GLdouble monoPositionB[] = {
                        monoB.position.x * monoGraphicScale,
                        monoB.position.y * monoGraphicScale,
                        monoB.position.z * monoGraphicScale
                    };

                    glutDraw::drawObject(
                        0.0, 0.0, 0.0,
                        [=]()
                        {
                            glBegin(GL_LINES);

                            glVertex3dv(monoPositionA);
                            glVertex3dv(monoPositionB);

                            glEnd();
                        }
                    );
                }
            }
        }
    }

    void drawOrbits()
    {
        namespace mem = monoEffectManager;

        for (int i = 0; i < mem::monos.size(); i++)
        {
            bool isCluster = false;

            for (MonoCluster& cluster : mem::clusters)
            {
                if (cluster.contains(mem::monos[i]))
                {
                    isCluster = true;

                    break;
                }
            }

            MonoOrbit& orbit = mem::orbits[i];
            int size = orbit.positions.size();

            for (int i = 0; i < size - orbitThinning; i += orbitThinning)
            {
                GLdouble orbitPositionA[] = {
                    orbit.positions[i].x * monoGraphicScale,
                    orbit.positions[i].y * monoGraphicScale,
                    orbit.positions[i].z * monoGraphicScale
                };

                GLdouble orbitPositionB[] = {
                    orbit.positions[i + orbitThinning].x * monoGraphicScale,
                    orbit.positions[i + orbitThinning].y * monoGraphicScale,
                    orbit.positions[i + orbitThinning].z * monoGraphicScale
                };

                double level = (double)(size - i) / size;

                if (isCluster)
                {
                    glColor3d(level, level / 2.0, 0.0);
                }
                else
                {
                    glColor3d(level, level, level);
                }

                glutDraw::drawObject(
                    0.0, 0.0, 0.0,
                    [=]()
                    {
                        glBegin(GL_LINES);

                        glVertex3dv(orbitPositionA);
                        glVertex3dv(orbitPositionB);

                        glEnd();
                    }
                );
            }
        }
    }

    void draw()
    {
        glutDraw::drawObject(
            0.0, -1.0e-4, 0.0, [=]() { glutUtil::drawGridGround(10, 10, 1.0); }
        );

        glutDraw::drawObject(
            0.0, 0.0, 0.0, [=]() { glutUtil::drawCoordinateSystem(1.0); }
        );

        drawMonos();

        if (showCluster)
            drawClusters();

        if (showOrbit)
            drawOrbits();
    }
}
