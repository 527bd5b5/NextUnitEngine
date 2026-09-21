#include <cmath>

#include "Classes/Vector3.hpp"
#include "Utils/Math.hpp"

namespace util
{
    double PI_15 = 3.141592653589793;

    double convertDegToRad(double deg)
    {
        return 2.0 * util::PI_15 * (deg / 360.0);
    }

    Vector3 getSphericalCoordinates(double theta, double phi, double radius)
    {
        theta = convertDegToRad(theta);
        phi = convertDegToRad(phi);

        return Vector3(
            radius * std::sin(theta) * std::cos(phi), radius * std::cos(theta),
            radius * std::sin(theta) * std::sin(phi)
        );
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

    // Singularity Waltz
    //     (Named by gpt-5.6-terra-xhigh)
    //
    //            │y┃ │
    //        ┌─┐ │ ┃ │ ┌4┐
    //        │ │ │ ┃ │ │ │
    //    ┌─┐ │ │ │ ┃ │ │ │ ┌8┐
    // ━━━┷━┿━┿━┿━┿━╋━1━3━5━7━9━━━
    //      │ │ │ │0┃ │ │ │ │    x
    //      └─┘ │ │ ┃ │ │ └6┘
    //          │ │ ┃ │ │
    //          └─┘ ┃ └2┘
    //
    // P1: x = 0.25,            y =  0
    // P2: x = 0.3913165133326, y = -5.0660651157838
    // P3: x = 0.75,            y =  0
    // P4: x = 0.9484666750106, y =  1.0538537814258
    // P5: x = 1.25,            y =  0
    // P6: x = 1.4659705110914, y = -0.4547218260266
    // P7: x = 1.75,            y =  0
    // P8: x = 1.9745622217186, y =  0.2532138117366
    // P9: x = 2.25,            y =  0

    double singularityWaltzFunc(double x)
    {
        return 1.0 / (x * x) * std::cos(2.0 * PI_15 * x);
    }

    double singularityWaltzFunc(double x, double a, double d)
    {
        return 1.0 * a / (x * x) * std::cos(d * 2.0 * PI_15 * x);
    }
}
