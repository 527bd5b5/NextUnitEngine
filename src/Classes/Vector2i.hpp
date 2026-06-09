#pragma once

#include "Classes/Vector2.hpp"

class Vector2;

class Vector2i
{
  public:
    int x;
    int y;

    Vector2i();
    Vector2i(int x, int y);
    Vector2i(const Vector2i& v);
    Vector2i(const Vector2& v);
    Vector2i& operator=(const Vector2i& v);
    Vector2i operator+(const Vector2i& v) const;
    Vector2i operator-(const Vector2i& v) const;
    Vector2i operator*(int i) const;
    Vector2i operator/(int i) const;
    Vector2i& operator+=(const Vector2i& v);
    Vector2i& operator-=(const Vector2i& v);
    Vector2i& operator*=(int i);
    Vector2i& operator/=(int i);
    void set(int x, int y);
    void set(const Vector2i& v);
};
