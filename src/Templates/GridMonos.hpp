#pragma once

#include "Classes/MonoTemplate.hpp"
#include "Classes/Vector3i.hpp"

namespace monoTemplate
{
    class GridMonos : public MonoTemplate
    {
      public:
        Vector3i size;
        double scale;
        bool fixEnd;

        GridMonos();
        void init() override;
        void setFromScript() override;
    };
}
