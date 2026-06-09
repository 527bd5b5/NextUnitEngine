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
        RandomMonos(const Vector3& origin);
        void init(int monoNum) override;
    };
}
