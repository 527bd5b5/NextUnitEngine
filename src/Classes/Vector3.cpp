#include <cmath>
#include <iostream>

#include "Classes/Vector3.hpp"

Vector3::Vector3()
{
    set(0.0, 0.0, 0.0);
}

Vector3::Vector3(double x, double y, double z)
{
    set(x, y, z);
}

Vector3::Vector3(const Vector3& v)
{
    set(v);
}

Vector3::Vector3(const Vector3i& v)
{
    set((double)v.x, (double)v.y, (double)v.z);
}

Vector3& Vector3::operator=(const Vector3& v)
{
    if (this == &v)
        return *this;

    x = v.x;
    y = v.y;
    z = v.z;

    return *this;
}

Vector3 Vector3::operator+(const Vector3& v) const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator*(double d) const
{
    return Vector3(x * d, y * d, z * d);
}

Vector3 Vector3::operator/(double d) const
{
    if (d == 0.0)
        throw std::runtime_error("Error: Division by zero.");

    return Vector3(x / d, y / d, z / d);
}

Vector3& Vector3::operator+=(const Vector3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

Vector3& Vector3::operator*=(double d)
{
    x *= d;
    y *= d;
    z *= d;

    return *this;
}

Vector3& Vector3::operator/=(double d)
{
    if (d == 0.0)
        throw std::runtime_error("Error: Division by zero.");

    x /= d;
    y /= d;
    z /= d;

    return *this;
}

void Vector3::set(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3::set(const Vector3& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

Vector3 Vector3::direction() const
{
    return Vector3(std::atan2(y, -z), std::atan2(-z, x), std::atan2(y, x));
}

double Vector3::magnitude() const
{
    return std::sqrt(x * x + y * y + z * z);
}
