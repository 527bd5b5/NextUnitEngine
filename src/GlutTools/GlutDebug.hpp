#pragma once

namespace glutDebug
{
    void debugMouse(int button, int state, int x, int y);
    void debugMotion(int x, int y);
    void debugKeyPressDown(unsigned char key, int x, int y);
    void debugKeyPressUp(unsigned char key, int x, int y);
}
