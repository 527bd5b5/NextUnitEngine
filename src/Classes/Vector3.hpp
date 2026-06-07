#pragma once

class Vector3
{
  public:
    double x;
    double y;
    double z;

    Vector3();
    Vector3(double x, double y, double z);
    Vector3(const Vector3& v);
    Vector3& operator=(const Vector3& v);
    Vector3 operator+(const Vector3& v) const;
    Vector3 operator-(const Vector3& v) const;
    Vector3 operator*(double d) const;
    Vector3 operator/(double d) const;
    Vector3& operator+=(const Vector3& v);
    Vector3& operator-=(const Vector3& v);
    Vector3& operator*=(double d);
    Vector3& operator/=(double d);
    void set(double x, double y, double z);
    void set(const Vector3& v);
    Vector3 direction() const;
    double magnitude() const;
};
