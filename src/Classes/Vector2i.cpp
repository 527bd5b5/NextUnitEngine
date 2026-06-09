#include <cmath>
#include <iostream>

#include "Classes/Vector2i.hpp"

Vector2i::Vector2i()
{
    set(0, 0);
}

Vector2i::Vector2i(int x, int y)
{
    set(x, y);
}

Vector2i::Vector2i(const Vector2i& v)
{
    set(v);
}

Vector2i::Vector2i(const Vector2& v)
{
    set((int)v.x, (int)v.y);
}

Vector2i& Vector2i::operator=(const Vector2i& v)
{
    if (this == &v)
        return *this;

    x = v.x;
    y = v.y;

    return *this;
}

Vector2i Vector2i::operator+(const Vector2i& v) const
{
    return Vector2i(x + v.x, y + v.y);
}

Vector2i Vector2i::operator-(const Vector2i& v) const
{
    return Vector2i(x - v.x, y - v.y);
}

Vector2i Vector2i::operator*(int i) const
{
    return Vector2i(x * i, y * i);
}

Vector2i Vector2i::operator/(int i) const
{
    if (i == 0)
        throw std::runtime_error("Error: Division by zero.");

    return Vector2i(x / i, y / i);
}

Vector2i& Vector2i::operator+=(const Vector2i& v)
{
    x += v.x;
    y += v.y;

    return *this;
}

Vector2i& Vector2i::operator-=(const Vector2i& v)
{
    x -= v.x;
    y -= v.y;

    return *this;
}

Vector2i& Vector2i::operator*=(int i)
{
    x *= i;
    y *= i;

    return *this;
}

Vector2i& Vector2i::operator/=(int i)
{
    if (i == 0)
        throw std::runtime_error("Error: Division by zero.");

    x /= i;
    y /= i;

    return *this;
}

void Vector2i::set(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Vector2i::set(const Vector2i& v)
{
    x = v.x;
    y = v.y;
}
