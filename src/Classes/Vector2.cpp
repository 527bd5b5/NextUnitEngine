#include <cmath>
#include <iostream>

#include "Classes/Vector2.hpp"

Vector2::Vector2()
{
    set(0.0, 0.0);
}

Vector2::Vector2(double x, double y)
{
    set(x, y);
}

Vector2::Vector2(const Vector2& v)
{
    set(v);
}

Vector2::Vector2(const Vector2i& v)
{
    set((double)v.x, (double)v.y);
}

Vector2& Vector2::operator=(const Vector2& v)
{
    if (this == &v)
        return *this;

    x = v.x;
    y = v.y;

    return *this;
}

Vector2 Vector2::operator+(const Vector2& v) const
{
    return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v) const
{
    return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(double d) const
{
    return Vector2(x * d, y * d);
}

Vector2 Vector2::operator/(double d) const
{
    if (d == 0.0)
        throw std::runtime_error("Error: Division by zero.");

    return Vector2(x / d, y / d);
}

Vector2& Vector2::operator+=(const Vector2& v)
{
    x += v.x;
    y += v.y;

    return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
    x -= v.x;
    y -= v.y;

    return *this;
}

Vector2& Vector2::operator*=(double d)
{
    x *= d;
    y *= d;

    return *this;
}

Vector2& Vector2::operator/=(double d)
{
    if (d == 0.0)
        throw std::runtime_error("Error: Division by zero.");

    x /= d;
    y /= d;

    return *this;
}

void Vector2::set(double x, double y)
{
    this->x = x;
    this->y = y;
}

void Vector2::set(const Vector2& v)
{
    x = v.x;
    y = v.y;
}

double Vector2::direction() const
{
    return std::atan2(y, x);
}

double Vector2::magnitude() const
{
    return std::sqrt(x * x + y * y);
}
