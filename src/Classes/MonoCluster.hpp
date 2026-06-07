#pragma once

#include <vector>

#include "Classes/Mono.hpp"
#include "Classes/Vector3.hpp"

class MonoCluster
{
  public:
    std::vector<Mono> monos;

    MonoCluster();
    MonoCluster(const Mono& mono1, const Mono& mono2);
    bool contains(const Mono& targetMono) const;
    int size() const;
    bool join(const Mono& mono1, const Mono& mono2);
    Vector3 getCenterPosition() const;
};
