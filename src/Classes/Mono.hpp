#pragma once

#include "Classes/Vector3.hpp"

class Mono
{
  public:
    int index;
    Vector3 position;
    Vector3 positionDelta; // = velocity
    bool fixed;

    Mono();
    Mono(int index);
    Mono(const Mono& mono);
};
