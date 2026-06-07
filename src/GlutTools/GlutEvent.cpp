#include <GL/glut.h>

#include "Classes/Vector2.hpp"
#include "GlutTools/GlutDebug.hpp"
#include "GlutTools/GlutEvent.hpp"

#define FOV 60.0
#define DEBUG_MOUSE false
#define DEBUG_MOTION false
#define DEBUG_KEYBOARD false

namespace glutEvent
{
    bool pressedKeys[256] = {};
    bool pressedMouseButtons[3] = {};
    Vector2 mousePosition(0.0, 0.0);

    void resize(int w, int h)
    {
        glViewport(0, 0, w, h);

        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();
        gluPerspective(FOV, (double)w / (double)h, 0.1, 100.0);

        glMatrixMode(GL_MODELVIEW);
    }

    void mouse(int button, int state, int x, int y)
    {
        if (DEBUG_MOUSE)
            glutDebug::debugMouse(button, state, x, y);

        switch (button)
        {
        case GLUT_LEFT_BUTTON:
            pressedMouseButtons[0] = state == GLUT_DOWN;
            break;
        case GLUT_MIDDLE_BUTTON:
            pressedMouseButtons[1] = state == GLUT_DOWN;
            break;
        case GLUT_RIGHT_BUTTON:
            pressedMouseButtons[2] = state == GLUT_DOWN;
            break;
        default:
            return;
        }

        mousePosition.x = x;
        mousePosition.y = y;
    }

    void motion(int x, int y)
    {
        if (DEBUG_MOTION)
            glutDebug::debugMotion(x, y);

        mousePosition.x = x;
        mousePosition.y = y;
    }

    void keyPressDown(unsigned char key, int x, int y)
    {
        if (DEBUG_KEYBOARD)
            glutDebug::debugKeyPressDown(key, x, y);

        if (key == 27)
            exit(0);

        pressedKeys[key] = true;
    }

    void keyPressUp(unsigned char key, int x, int y)
    {
        if (DEBUG_KEYBOARD)
            glutDebug::debugKeyPressUp(key, x, y);

        pressedKeys[key] = false;
    }

    void init()
    {
        glutReshapeFunc(resize);
        glutMouseFunc(mouse);
        glutMotionFunc(motion);
        glutKeyboardFunc(keyPressDown);
        glutKeyboardUpFunc(keyPressUp);
        glutIgnoreKeyRepeat(GL_TRUE);
    }
}
