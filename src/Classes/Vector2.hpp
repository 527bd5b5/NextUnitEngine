#pragma once

class Vector2
{
  public:
    double x;
    double y;

    Vector2();
    Vector2(double x, double y);
    Vector2(const Vector2& v);
    Vector2& operator=(const Vector2& v);
    Vector2 operator+(const Vector2& v) const;
    Vector2 operator-(const Vector2& v) const;
    Vector2 operator*(double d) const;
    Vector2 operator/(double d) const;
    Vector2& operator+=(const Vector2& v);
    Vector2& operator-=(const Vector2& v);
    Vector2& operator*=(double d);
    Vector2& operator/=(double d);
    void set(double x, double y);
    void set(const Vector2& v);
    double direction() const;
    double magnitude() const;
};
