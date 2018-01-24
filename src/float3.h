#pragma once
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <omp.h>

template <class T> class v3
{
  public:
    v3()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
		assert(!HasNans());
    }
	v3(float xyz) :x(xyz), y(xyz), z(xyz) {}
    v3(T x, T y, T z): x(x), y(y), z(z)
    {
		assert(!HasNans());
    }

	bool HasNans() const {
		return std::isnan(x) || std::isnan(y) || std::isnan(z);
	}
    inline float dot(v3<T> rhs)
    {
        return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z;
    }
    inline v3<T> cross(v3 rhs)
    {
        return v3(this->y * rhs.z - this->z * rhs.y,
                      this->z * rhs.x - this->x * rhs.z,
                      this->x * rhs.y - this->y * rhs.x);
    }
    inline float length()
    {
        return sqrt(this->dot(*this));
    }
    inline float sqrtLength()
    {
        return this->dot(*this);
    }


    void setX(float num) { x = num; }
    void setY(float num) { y = num; }
    void setZ(float num) { z = num; }
    void set(float x, float y, float z)
    {
        setX(x);
        setY(y);
        setZ(z);
    }
    inline float operator[](int i) const { return entity[i]; }

    template<typename T> friend std::ostream &operator<<(std::ostream &os, v3 &rhs);
    template<typename T> friend std::istream &operator>>(std::istream &is, v3 &rhs);

    float entity[3];
	T x, y, z;
};

template <typename T>
inline v3<T> operator+(const v3<T> &lhs, const float &rhs)
{
    return v3<T>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
}

template <typename T>
inline v3<T> operator-(const v3<T> &lhs, const float &rhs)
{
    return v3<T>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
}
template <typename T> inline v3<T> operator/(const v3<T> &lhs, const float &rhs)
{
    return v3<T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

template <typename T>
inline v3<T> operator*(const v3<T> &lhs, const float &rhs)
{
    return v3<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

template <typename T>
inline v3<T> operator+(const v3<T> &lhs, const v3<T> &rhs)
{
    return v3<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

template <typename T>
inline v3<T> operator-(const v3<T> &lhs, const v3<T> &rhs)
{
    return v3<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}
template <typename T>
inline v3<T> operator*(const v3<T> &lhs, const v3<T> &rhs)
{
    return v3<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}
template <typename T>
inline bool operator==(const v3<T> &lhs, const v3<T> &rhs)
{
    return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
}

template <typename T>
inline std::ostream &operator<<(std::ostream &os, v3<T> &rhs)
{
    os << rhs.x << " " << rhs.y << " " << rhs.z;
    return os;
}

template <typename T>
inline std::istream &operator>>(std::istream &is, v3<T> &rhs)
{
    is >> rhs.x >> rhs.y >> rhs.z;
    return is;
}
template <typename T> inline v3<T> unit(v3<T> v) {
	return v/ v.length();
}
typedef v3<float> v3f;
typedef v3<float> float3;
