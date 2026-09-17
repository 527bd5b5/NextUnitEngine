#pragma once

#include "Classes/Vector2.hpp"
#include "Classes/Vector3.hpp"

namespace glutCamera
{
    extern Vector3 cameraPosition;
    extern Vector2 cameraRotation;
    extern Vector3 initCameraPosition;
    extern Vector2 initCameraRotation;

    void reset();
    void update();
}
