#pragma once

#include "Classes/Vector3.hpp"

class Vector3;

class Vector3i
{
  public:
    int x;
    int y;
    int z;

    Vector3i();
    Vector3i(int x, int y, int z);
    Vector3i(const Vector3i& v);
    Vector3i(const Vector3& v);
    Vector3i& operator=(const Vector3i& v);
    Vector3i operator+(const Vector3i& v) const;
    Vector3i operator-(const Vector3i& v) const;
    Vector3i operator*(int i) const;
    Vector3i operator/(int i) const;
    Vector3i& operator+=(const Vector3i& v);
    Vector3i& operator-=(const Vector3i& v);
    Vector3i& operator*=(int i);
    Vector3i& operator/=(int i);
    void set(int x, int y, int z);
    void set(const Vector3i& v);
};
