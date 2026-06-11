#include <string>

#include <GL/glut.h>

#include "Classes/KeySignal.hpp"
#include "Classes/Mono.hpp"
#include "Classes/MonoCluster.hpp"
#include "Engine/MonoEffectManager.hpp"
#include "Engine/WorldRunner.hpp"
#include "GlutTools/GlutCamera.hpp"
#include "GlutTools/GlutDraw.hpp"
#include "GlutTools/GlutEvent.hpp"
#include "GlutTools/GlutUtil.hpp"

#define DELTA_TIMES 1.0 / 65536
#define CLUSTER_THRESHOLD 1.0 / 8
#define MONO_GRAPHIC_POINT_SIZE 1.0 / 16
#define SHOW_MONO_INDEX_LABEL false

namespace worldRunner
{
    std::vector<MonoTemplate*> monoTemplates;

    KeySignal keySignals[3] = {
        KeySignal('r', 1.0), KeySignal('c', 1.0), KeySignal('v', 1.0)
    };
    KeySignal& resetKeySignal = keySignals[0];
    KeySignal& playKeySignal = keySignals[1];
    KeySignal& stepKeySignal = keySignals[2];

    bool playWorld = true;

    void reset()
    {
        monoEffectManager::clear();

        for (MonoTemplate* mt : monoTemplates)
            mt->init();
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
                mem::monos[i].position, [=]() { glutSolidSphere(0.01, 8, 8); }
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
                cluster.getCenterPosition(),
                [=]() { glutSolidSphere(0.01, 8, 8); }
            );

            for (Mono& monoA : cluster.monos)
            {
                GLdouble monoPositionA[] = {
                    monoA.position.x, monoA.position.y, monoA.position.z
                };

                for (Mono& monoB : cluster.monos)
                {
                    if (monoA.index >= monoB.index)
                        continue;

                    GLdouble monoPositionB[] = {
                        monoB.position.x, monoB.position.y, monoB.position.z
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
