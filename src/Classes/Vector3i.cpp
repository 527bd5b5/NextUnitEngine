#include <cmath>
#include <iostream>

#include "Classes/Vector3i.hpp"

Vector3i::Vector3i()
{
    set(0, 0, 0);
}

Vector3i::Vector3i(int x, int y, int z)
{
    set(x, y, z);
}

Vector3i::Vector3i(const Vector3i& v)
{
    set(v);
}

Vector3i::Vector3i(const Vector3& v)
{
    set((int)v.x, (int)v.y, (int)v.z);
}

Vector3i& Vector3i::operator=(const Vector3i& v)
{
    if (this == &v)
        return *this;

    x = v.x;
    y = v.y;
    z = v.z;

    return *this;
}

Vector3i Vector3i::operator+(const Vector3i& v) const
{
    return Vector3i(x + v.x, y + v.y, z + v.z);
}

Vector3i Vector3i::operator-(const Vector3i& v) const
{
    return Vector3i(x - v.x, y - v.y, z - v.z);
}

Vector3i Vector3i::operator*(int i) const
{
    return Vector3i(x * i, y * i, z * i);
}

Vector3i Vector3i::operator/(int i) const
{
    if (i == 0.0)
        throw std::runtime_error("Error: Division by zero.");

    return Vector3i(x / i, y / i, z / i);
}

Vector3i& Vector3i::operator+=(const Vector3i& v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

Vector3i& Vector3i::operator-=(const Vector3i& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

Vector3i& Vector3i::operator*=(int i)
{
    x *= i;
    y *= i;
    z *= i;

    return *this;
}

Vector3i& Vector3i::operator/=(int i)
{
    if (i == 0.0)
        throw std::runtime_error("Error: Division by zero.");

    x /= i;
    y /= i;
    z /= i;

    return *this;
}

void Vector3i::set(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3i::set(const Vector3i& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}
