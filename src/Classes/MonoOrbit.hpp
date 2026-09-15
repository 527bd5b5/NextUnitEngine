#pragma once

#include <vector>

#include "Classes/Mono.hpp"
#include "Classes/Vector3.hpp"

class MonoOrbit
{
  public:
    std::vector<Vector3> positions;

    MonoOrbit();
    MonoOrbit(const Mono& mono);
    void insertPosition(const Mono& mono, int remaining);
};
