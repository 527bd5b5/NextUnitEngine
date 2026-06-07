#pragma once

#include <functional>
#include <iostream>

namespace util
{
    void printDebugLine(const std::string& text);
    std::function<double(void)> getDoubleRandFunc(double min, double max);
    double sigmoidFunc(double x);
    double sigmoidFunc(double x, double a);
    double normalDistributionFunc(double x);
    double normalDistributionFunc(double x, double s, double m);
    double untitledFunc(double x);
    double untitledFunc(double x, double a, double d);
}
