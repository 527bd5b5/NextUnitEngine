#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

#include <GL/glut.h>

#include "Classes/Vector2.hpp"
#include "Classes/Vector3.hpp"
#include "Engine/World.hpp"
#include "GlutTools/GlutCamera.hpp"
#include "GlutTools/GlutDraw.hpp"

#define UPDATE_CYCLE_MSEC 10 // 100 fps

namespace glutDraw
{
    Vector3 prevPosition;

    // deprecated
    void setPosition(double x, double y, double z)
    {
        glTranslated(
            x - prevPosition.x, y - prevPosition.y, z - prevPosition.z
        );

        prevPosition.set(x, y, z);
    }

    // deprecated
    void setPosition(const Vector3& vector)
    {
        setPosition(vector.x, vector.y, vector.z);
    }

    void
    drawObject(double x, double y, double z, std::function<void()> drawFunc)
    {
        glPushMatrix();
        glTranslated(x, y, z);

        drawFunc();

        glPopMatrix();
    }

    void drawObject(const Vector3& vector, std::function<void()> drawFunc)
    {
        drawObject(vector.x, vector.y, vector.z, drawFunc);
    }

    void display()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        Vector3& position = glutCamera::cameraPosition;
        Vector2& rotation = glutCamera::cameraRotation;

        glRotated(-rotation.x, 1.0, 0.0, 0.0);
        glRotated(-rotation.y, 0.0, 1.0, 0.0);
        glTranslated(-position.x, -position.y, -position.z);

        prevPosition.set(0.0, 0.0, 0.0);

        world::draw();

        glutSwapBuffers();
    }

    void idle()
    {
        auto wake = std::chrono::system_clock::now() +
                    std::chrono::milliseconds(UPDATE_CYCLE_MSEC);

        glutCamera::update();
        world::update();

        glutPostRedisplay();

        try
        {
            std::this_thread::sleep_until(wake);
        }
        catch (const std::exception& e)
        {
            std::cerr << "Sleep interrupted: " << e.what() << std::endl;
        }
    }

    void play()
    {
        glutIdleFunc(idle);
    }

    void freeze()
    {
        glutIdleFunc(NULL);
    }

    void init()
    {
        glutDisplayFunc(display);
        glutIdleFunc(idle);

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
}
