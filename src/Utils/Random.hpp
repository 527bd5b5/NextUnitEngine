#pragma once

#include <functional>

namespace util
{
    std::function<double(void)> getDoubleRandFunc(double min, double max);
}
