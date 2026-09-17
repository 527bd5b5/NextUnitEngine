#pragma once

#include "Classes/Vector3.hpp"

namespace util
{
    extern double PI_15;

    double convertDegToRad(double deg);
    Vector3 getSphericalCoordinates(double theta, double phi, double radius);
    double sigmoidFunc(double x);
    double sigmoidFunc(double x, double a);
    double normalDistributionFunc(double x);
    double normalDistributionFunc(double x, double s, double m);
    double untitledFunc(double x);
    double untitledFunc(double x, double a, double d);
}
