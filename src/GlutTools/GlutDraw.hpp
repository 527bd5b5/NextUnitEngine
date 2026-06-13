#pragma once

#include <functional>

#include "Classes/Vector3.hpp"

namespace glutDraw
{
    void
    drawObject(double x, double y, double z, std::function<void()> drawFunc);
    void drawObject(const Vector3& vector, std::function<void()> drawFunc);
    void init();
}
