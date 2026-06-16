#include <map>
#include <string>
#include <vector>

#include <GL/glut.h>

#include "Classes/KeySignal.hpp"
#include "Classes/Mono.hpp"
#include "Classes/MonoCluster.hpp"
#include "Engine/MonoEffectManager.hpp"
#include "Engine/WorldReader.hpp"
#include "Engine/WorldRunner.hpp"
#include "GlutTools/GlutCamera.hpp"
#include "GlutTools/GlutDraw.hpp"
#include "GlutTools/GlutEvent.hpp"
#include "GlutTools/GlutUtil.hpp"

#define GRAPHIC_SCALE 0.1
#define DELTA_TIMES 1.0 / 16384
#define CLUSTER_THRESHOLD 0.3913165154385
#define MONO_GRAPHIC_POINT_SIZE 1.0 / 16
#define SHOW_MONO_INDEX_LABEL false

namespace worldRunner
{
    std::vector<MonoTemplate*> monoTemplates;

    KeySignal keySignals[4] = {
        KeySignal('r', 1.0), KeySignal('t', 1.0), KeySignal('c', 1.0),
        KeySignal('v', 1.0)
    };
    KeySignal& resetKeySignal = keySignals[0];
    KeySignal& reloadKeySignal = keySignals[1];
    KeySignal& playKeySignal = keySignals[2];
    KeySignal& stepKeySignal = keySignals[3];

    bool playWorld = true;

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

        if (resetKeySignal.getIsPressed())
        {
            reset();

            mem::calcNextState(DELTA_TIMES, CLUSTER_THRESHOLD);
        }
        else if (reloadKeySignal.getIsPressed())
        {
            reload();

            mem::calcNextState(DELTA_TIMES, CLUSTER_THRESHOLD);
        }
        else if (playWorld || stepKeySignal.getIsPressed())
        {
            mem::calcNextState(DELTA_TIMES, CLUSTER_THRESHOLD);
        }
    }

    void draw()
    {
        namespace mem = monoEffectManager;

        glutDraw::drawObject(
            0.0, -1.0e-4, 0.0, [=]() { glutUtil::drawGridGround(10, 10, 1.0); }
        );

        glutDraw::drawObject(
            0.0, 0.0, 0.0, [=]() { glutUtil::drawCoordinateSystem(1.0); }
        );

        for (int i = 0; i < mem::monos.size(); i++)
        {
            glColor3d(1.0, 1.0, 1.0);

            glutDraw::drawObject(
                mem::monos[i].position * GRAPHIC_SCALE,
                [=]() { glutSolidSphere(0.01, 8, 8); }
            );

            if (SHOW_MONO_INDEX_LABEL)
            {
                glColor3d(0.25, 0.25, 0.25);
                glRasterPos3d(0.0, 0.0, 0.0);
                glutUtil::drawString(std::to_string(i));
            }
        }

        glColor3d(1.0, 0.0, 0.0);

        for (MonoCluster& cluster : mem::clusters)
        {
            glutDraw::drawObject(
                cluster.getCenterPosition() * GRAPHIC_SCALE,
                [=]() { glutSolidSphere(0.01, 8, 8); }
            );

            for (Mono& monoA : cluster.monos)
            {
                GLdouble monoPositionA[] = {
                    monoA.position.x * GRAPHIC_SCALE,
                    monoA.position.y * GRAPHIC_SCALE,
                    monoA.position.z * GRAPHIC_SCALE
                };

                for (Mono& monoB : cluster.monos)
                {
                    if (monoA.index >= monoB.index)
                        continue;

                    GLdouble monoPositionB[] = {
                        monoB.position.x * GRAPHIC_SCALE,
                        monoB.position.y * GRAPHIC_SCALE,
                        monoB.position.z * GRAPHIC_SCALE
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
}
