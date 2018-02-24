#pragma once
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <omp.h>


template <class T> class v2
{
    public:
    v2()
    {
        x = 0.0;
        y = 0.0;
    }
    v2(T xy):x(xy),y(xy){}
    v2(T x, T y): x(x), y(y){}
    inline float dot(v2<T> rhs)
    {
        return x*rhs.x + y*rhs.y;
    }
    inline float length()
    {
        return sqrt(dot(*this));
    }
    inline float sqrd_length()
    {
        return dot(*this);
    }
    
    template<typename T> friend std::ostream &operator<<(std::ostream &os, v2 &rhs);
    template<typename T> friend std::istream &operator>>(std::istream &is, v2 &rhs);
    T x,y;
};


template <typename T>
inline v2<T> operator+(const v2<T> &lhs, const float &rhs)
{
    return v2<T>(lhs.x + rhs, lhs.y + rhs);
}

template <typename T>
inline v2<T> operator-(const v2<T> &lhs, const float &rhs)
{
    return v2<T>(lhs.x - rhs, lhs.y - rhs);
}
template <typename T> inline v2<T> operator/(const v2<T> &lhs, const float &rhs)
{
    return v2<T>(lhs.x / rhs, lhs.y / rhs);
}

template <typename T>
inline v2<T> operator*(const v2<T> &lhs, const float &rhs)
{
    return v2<T>(lhs.x * rhs, lhs.y * rhs);
}

template <typename T>
inline v2<T> operator+(const v2<T> &lhs, const v2<T> &rhs)
{
    return v2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <typename T>
inline v2<T> operator-(const v2<T> &lhs, const v2<T> &rhs)
{
    return v2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <typename T>
inline v2<T> operator*(const v2<T> &lhs, const v2<T> &rhs)
{
    return v2<T>(lhs.x * rhs.x, lhs.y * rhs.y);
}

template <typename T>
inline bool operator==(const v2<T> &lhs, const v2<T> &rhs)
{
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

template <typename T>
inline std::ostream &operator<<(std::ostream &os, v2<T> rhs)
{
    os << rhs.x << " " << rhs.y;
    return os;
}

template <typename T>
inline std::istream &operator>>(std::istream &is, v2<T> &rhs)
{
    is >> rhs.x >> rhs.y;
    return is;
}
template <typename T> inline v2<T> unit(v2<T> v) {
    return v/ v.length();
}
typedef v2<float> v2f;
typedef v2<int> v2i;

inline v2f maxf2(v2f lhs, float max)
{
    return v2f(fmax(lhs.x,max), fmax(lhs.y,max));
}
inline v2f minf2(v2f lhs, float min)
{
    return v2f(fmin(lhs.x, min), fmin(lhs.y, min));
}


template <class T> class v3
{
    public:
    v3()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }
    v3(T xyz) :x(xyz), y(xyz), z(xyz) {}
    v3(T x, T y, T z): x(x), y(y), z(z){}
    v3(cpptoml::option<std::vector<double>> arr):x((*arr)[0]),y((*arr)[1]),z((*arr)[2]){}
    
    bool HasNans() const {
        return std::isnan(x) || std::isnan(y) || std::isnan(z);
    }
    
    inline float dot(v3<T> rhs)
    {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }
    inline v3<T> cross(v3 rhs)
    {
        return v3(y * rhs.z - z * rhs.y,
                  z * rhs.x - x * rhs.z,
                  x * rhs.y - y * rhs.x);
    }
    inline float length()
    {
        return sqrt(dot(*this));
    }
    inline float sqrd_length()
    {
        return dot(*this);
    }
    
    
    template<typename T> friend std::ostream &operator<<(std::ostream &os, v3 &rhs);
    template<typename T> friend std::istream &operator>>(std::istream &is, v3 &rhs);
    
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
inline std::ostream &operator<<(std::ostream &os, v3<T> rhs)
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
typedef v3<int> v3i;

inline v3f maxf3(v3f lhs, float max)
{
    return v3f(fmax(lhs.x,max), fmax(lhs.y,max), fmax(lhs.z,max));
}
inline v3f minf3(v3f lhs, float min)
{
    return v3f(fmin(lhs.x, min), fmin(lhs.y, min), fmin(lhs.z, min));
}
