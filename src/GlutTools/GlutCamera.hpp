#pragma once

#include "Classes/Vector2.hpp"
#include "Classes/Vector3.hpp"

namespace glutCamera
{
    extern Vector3 cameraPosition;
    extern Vector2 cameraRotation;

    void update();
}
