#pragma once

#include "Classes/MonoTemplate.hpp"
#include "Classes/Vector3.hpp"

namespace monoTemplate
{
    class RingMonos : public MonoTemplate
    {
      public:
        double radius;
        double velocity;
        double positionNoise;
        double positionDeltaNoise;

        RingMonos();
        RingMonos(const Vector3& origin);
        void init(int monoNum) override;
    };
}
