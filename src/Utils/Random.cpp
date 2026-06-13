#include <functional>
#include <random>

#include "Utils/Random.hpp"

namespace util
{
    std::function<double(void)>
    getDoubleRandFunc(double min = 0.0, double max = 1.0)
    {
        std::random_device rd;
        std::mt19937 engine(rd());
        std::uniform_real_distribution<double> dist(min, max);

        return std::bind(dist, engine);
    }
}
