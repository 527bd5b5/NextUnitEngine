#pragma once

#include "Classes/Vector2.hpp"

namespace glutEvent
{
    extern bool pressedKeys[256];
    extern bool pressedMouseButtons[3];
    extern Vector2 mousePosition;

    void init();
}
