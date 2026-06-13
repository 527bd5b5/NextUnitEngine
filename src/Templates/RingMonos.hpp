#pragma once

#include "Classes/MonoTemplate.hpp"

namespace monoTemplate
{
    class RingMonos : public MonoTemplate
    {
      public:
        double radius;
        double velocity;

        RingMonos();
        void init() override;
        void setFromScript() override;
    };
}
