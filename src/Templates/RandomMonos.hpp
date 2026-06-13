#pragma once

#include "Classes/MonoTemplate.hpp"
#include "Classes/Vector3.hpp"

namespace monoTemplate
{
    class RandomMonos : public MonoTemplate
    {
      public:
        Vector3 size;

        RandomMonos();
        void init() override;
        void setFromScript() override;
    };
}
