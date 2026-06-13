#include <iostream>
#include <string>

#include <GL/glut.h>

#include "GlutTools/GlutDebug.hpp"
#include "Utils/String.hpp"

namespace glutDebug
{
    std::string getPositionString(int x, int y)
    {
        return "x: " + std::to_string(x) + ", y: " + std::to_string(y);
    }

    std::string getKeyName(unsigned char key)
    {
        switch (key)
        {
        case 8:
            return "backspace";
        case 9:
            return "tab";
        case 10:
            return "feed";
        case 13:
            return "enter";
        case 27:
            return "escape";
        case 32:
            return "space";
        case 127:
            return "delete";
        default:
            return "\"" + std::string(1, key) + "\"";
        }
    }

    void debugMouse(int button, int state, int x, int y)
    {
        std::string text = "A ";

        switch (button)
        {
        case GLUT_LEFT_BUTTON:
            text += "left";
            break;
        case GLUT_MIDDLE_BUTTON:
            text += "middle";
            break;
        case GLUT_RIGHT_BUTTON:
            text += "right";
            break;
        default:
            return;
        }

        text += " button was ";

        switch (state)
        {
        case GLUT_UP:
            text += "up";
            break;
        case GLUT_DOWN:
            text += "down";
            break;
        default:
            return;
        }

        text += " at (" + getPositionString(x, y) + ").";

        util::printDebugLine(text);
    }

    void debugMotion(int x, int y)
    {
        util::printDebugLine(
            "The cursor moved to (" + getPositionString(x, y) + ")."
        );
    }

    void debugKeyPressDown(unsigned char key, int x, int y)
    {
        util::printDebugLine(
            "The " + getKeyName(key) + " key (" + std::to_string(key) +
            ") was pressed down at (" + getPositionString(x, y) + ")."
        );
    }

    void debugKeyPressUp(unsigned char key, int x, int y)
    {
        util::printDebugLine(
            "The " + getKeyName(key) + " key (" + std::to_string(key) +
            ") was pressed up at (" + getPositionString(x, y) + ")."
        );
    }
}
