#include <string>

#include <GL/glut.h>

#include "Classes/KeySignal.hpp"
#include "Classes/Mono.hpp"
#include "Classes/MonoCluster.hpp"
#include "Classes/Vector2.hpp"
#include "Classes/Vector3.hpp"
#include "Classes/Vector3i.hpp"
#include "Engine/MonoEffectManager.hpp"
#include "Engine/World.hpp"
#include "GlutTools/GlutCamera.hpp"
#include "GlutTools/GlutDraw.hpp"
#include "GlutTools/GlutEvent.hpp"
#include "GlutTools/GlutUtil.hpp"
#include "Templates/GridMonos.hpp"
#include "Templates/RandomMonos.hpp"
#include "Templates/RingMonos.hpp"
#include "Util.hpp"

#define DELTA_TIMES 1.0 / 65536
#define CLUSTER_THRESHOLD 1.0 / 8
#define MONO_GRAPHIC_POINT_SIZE 1.0 / 16
#define SHOW_MONO_INDEX_LABEL false

namespace world
{
    KeySignal keySignals[3] = {
        KeySignal('r', 1.0), KeySignal('c', 1.0), KeySignal('v', 1.0)
    };
    KeySignal& resetKeySignal = keySignals[0];
    KeySignal& playKeySignal = keySignals[1];
    KeySignal& stepKeySignal = keySignals[2];

    bool playWorld = true;

    void reset()
    {
        glutCamera::cameraPosition = Vector3(0.0, 10.0, 0.0);
        glutCamera::cameraRotation = Vector2(-90.0, 0.0);

        namespace mt = monoTemplate;

        monoEffectManager::clear();

        mt::RingMonos ringMonos;

        ringMonos.radius = 1.0 / 256;
        ringMonos.velocity = 1.0 / 256;
        ringMonos.positionNoise = 1.0 / 256;

        for (int i = 0; i < 16; i++)
        {
            ringMonos.origin.x = (double)(i % 4) * 2.0 - 3.0;
            ringMonos.origin.z = (double)(i / 4) * 2.0 - 3.0;

            ringMonos.init(i + 3);
        }
    }

    void update()
    {
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

            monoEffectManager::calcNextState(DELTA_TIMES, CLUSTER_THRESHOLD);
        }
        else if (playWorld || stepKeySignal.getIsPressed())
        {
            monoEffectManager::calcNextState(DELTA_TIMES, CLUSTER_THRESHOLD);
        }
    }

    void draw()
    {
        glutDraw::drawObject(
            0.0, -1.0e-4, 0.0, [=]() { glutUtil::drawGridGround(20, 20, 0.5); }
        );

        glutDraw::drawObject(
            0.0, 0.0, 0.0, [=]() { glutUtil::drawCoordinateSystem(0.5); }
        );

        for (int i = 0; i < monoEffectManager::monos.size(); i++)
        {
            glColor3d(1.0, 1.0, 1.0);

            glutDraw::drawObject(
                monoEffectManager::monos[i].position,
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

        for (MonoCluster& cluster : monoEffectManager::clusters)
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
