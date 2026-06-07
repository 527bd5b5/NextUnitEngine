#pragma once

#include <iostream>

namespace glutUtil
{
    void drawCoordinateSystem(double scale);
    void drawSampleCube(double scale);
    void drawGridGround(int x, int z, double scale);
    void drawString(const char* text);
    void drawString(const std::string& text);
}
