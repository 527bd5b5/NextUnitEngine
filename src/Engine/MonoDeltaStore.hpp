#pragma once

#include "Classes/Vector3.hpp"

namespace monoDeltaStore
{
    struct MonoDelta
    {
        Vector3 positionDelta;
        double magnitude;
        double power;
    };

    void init(int num);
    void set(int i, int j, MonoDelta& monoDelta);
    MonoDelta& get(int i, int j);
}
