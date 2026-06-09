#pragma once

#include "Classes/MonoTemplate.hpp"
#include "Classes/Vector3.hpp"
#include "Classes/Vector3i.hpp"

namespace monoTemplate
{
    class GridMonos : public MonoTemplate
    {
      public:
        Vector3i size;
        bool fixEnd;
        double noise;

        GridMonos();
        GridMonos(const Vector3& origin);
        void init();
    };
}
