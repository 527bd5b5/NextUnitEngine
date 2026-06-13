#pragma once

#include <vector>

#include "Classes/MonoTemplate.hpp"

namespace worldRunner
{
    extern std::vector<MonoTemplate*> monoTemplates;

    void reset();
    void update();
    void draw();
}
