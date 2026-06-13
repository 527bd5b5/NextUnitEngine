#include <cmath>

#include "Utils/Math.hpp"

namespace util
{
    double PI_15 = 3.141592653589793;

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
