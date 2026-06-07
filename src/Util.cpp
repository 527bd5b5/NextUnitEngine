#include <cmath>
#include <functional>
#include <iostream>
#include <random>

#include "Util.hpp"

#define PI_15 3.141592653589793

namespace util
{
    void printDebugLine(const std::string& text)
    {
        std::cout << "[DEBUG] " + text << std::endl;
    }

    std::function<double(void)>
    getDoubleRandFunc(double min = 0.0, double max = 1.0)
    {
        std::random_device rd;
        std::mt19937 engine(rd());
        std::uniform_real_distribution<double> dist(min, max);

        return std::bind(dist, engine);
    }

    double sigmoidFunc(double x)
    {
        return 1.0 / (1.0 + std::exp(-x));
    }

    double sigmoidFunc(double x, double a)
    {
        return 1.0 / (1.0 + std::exp(-a * x));
    }

    double normalDistributionFunc(double x)
    {
        return 1.0 / (std::sqrt(2.0 * PI_15)) * std::exp(-1.0 * x * x / 2.0);
    }

    double normalDistributionFunc(double x, double s, double m)
    {
        double s2 = s * s;
        double sx = x - m;

        return 1.0 / (std::sqrt(2.0 * PI_15 * s2)) *
               std::exp(-1.0 * sx * sx / (2.0 * s2));
    }

    // Memo: 正式版の公開前には固有名詞を決めること。
    //       そのままだと「untiFunc」と略されるため。

    double untitledFunc(double x)
    {
        return 1.0 / x * std::cos(2.0 * PI_15 * x);
    }

    double untitledFunc(double x, double a, double d)
    {
        return a / x * std::cos(d * 2.0 * PI_15 * x);
    }
}
