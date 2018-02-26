#include <smmintrin.h>
class v2
{
    public:
    v2()
    {
        x = 0.0;
        y = 0.0;
    }
    v2(float xy):x(xy),y(xy){}
    v2(float x, float y): x(x), y(y){}
    inline float dot(v2 rhs)
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
    
    friend std::ostream &operator<<(std::ostream &os, v2 &rhs);
    friend std::istream &operator>>(std::istream &is, v2 &rhs);
    float x,y;
};


inline v2 operator+(const v2 &lhs, const float &rhs)
{
    return v2(lhs.x + rhs, lhs.y + rhs);
}


inline v2 operator-(const v2 &lhs, const float &rhs)
{
    return v2(lhs.x - rhs, lhs.y - rhs);
}
inline v2 operator/(const v2 &lhs, const float &rhs)
{
    return v2(lhs.x / rhs, lhs.y / rhs);
}


inline v2 operator*(const v2 &lhs, const float &rhs)
{
    return v2(lhs.x * rhs, lhs.y * rhs);
}


inline v2 operator+(const v2 &lhs, const v2 &rhs)
{
    return v2(lhs.x + rhs.x, lhs.y + rhs.y);
}


inline v2 operator-(const v2 &lhs, const v2 &rhs)
{
    return v2(lhs.x - rhs.x, lhs.y - rhs.y);
}


inline v2 operator*(const v2 &lhs, const v2 &rhs)
{
    return v2(lhs.x * rhs.x, lhs.y * rhs.y);
}


inline bool operator==(const v2 &lhs, const v2 &rhs)
{
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}


inline std::ostream &operator<<(std::ostream &os, v2 rhs)
{
    os << rhs.x << " " << rhs.y;
    return os;
}


inline std::istream &operator>>(std::istream &is, v2 &rhs)
{
    is >> rhs.x >> rhs.y;
    return is;
}
inline v2 unit(v2 v) {
    return v/ v.length();
}
typedef v2 v2f;
typedef v2 v2i;

inline v2f maxf2(v2f lhs, float max)
{
    return v2f(fmax(lhs.x,max), fmax(lhs.y,max));
}
inline v2f minf2(v2f lhs, float min)
{
    return v2f(fmin(lhs.x, min), fmin(lhs.y, min));
}


_MM_ALIGN16 class v3
{
    public:
    v3()
    {
        value= _mm_setzero_ps();
    }
    v3(float xyz){value = _mm_set_ps(0,xyz,xyz,xyz);}
    v3(float x, float y, float z){value = _mm_set_ps(0,z,y,x);}
    v3(__m128 val):value(val){}
    v3(cpptoml::option<std::vector<double>> arr)
    {
        value = _mm_set_ps( 0,(*arr)[2], (*arr)[1], (*arr)[0]);
    }
    
    bool HasNans() const {
    }
    
    inline float dot(v3 rhs)
    {
        return _mm_cvtss_f32(_mm_dp_ps(value, rhs.value, 0x71));
    }
    inline v3 cross(v3 rhs)
    {
        return v3(_mm_sub_ps(
            _mm_mul_ps(_mm_shuffle_ps(value, value, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(rhs.value, rhs.value, _MM_SHUFFLE(3, 1, 0, 2))), 
            _mm_mul_ps(_mm_shuffle_ps(value, value, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(rhs.value, rhs.value, _MM_SHUFFLE(3, 0, 2, 1)))));
    }
    inline float length()
    {
        return sqrt(dot(*this));
    }
    inline float sqrd_length()
    {
        return dot(*this);
    }
    
    
    friend std::ostream &operator<<(std::ostream &os, v3 &rhs);
    friend std::istream &operator>>(std::istream &is, v3 &rhs);
    union{
        __m128 value;
        struct{float x, y, z;};
    };
};


inline v3 operator+(const v3 &lhs, const float &rhs)
{
    return v3(_mm_add_ps(lhs.value, _mm_set1_ps(rhs)));
}


inline v3 operator-(const v3 &lhs, const float &rhs)
{
    return v3(_mm_sub_ps(lhs.value, _mm_set1_ps(rhs)));
}
inline v3 operator/(const v3 &lhs, const float &rhs)
{
    return v3(_mm_div_ps(lhs.value, _mm_set1_ps(rhs)));
}


inline v3 operator*(const v3 &lhs, const float &rhs)
{
    return v3(_mm_mul_ps(lhs.value, _mm_set1_ps(rhs)));
}


inline v3 operator+(const v3 &lhs, const v3 &rhs)
{
    return v3(_mm_add_ps(lhs.value, rhs.value));
}


inline v3 operator-(const v3 &lhs, const v3 &rhs)
{
    return v3(_mm_sub_ps(lhs.value, rhs.value));
}


inline v3 operator*(const v3 &lhs, const v3 &rhs)
{
    return v3(_mm_mul_ps(lhs.value, rhs.value));
}

/*
inline bool operator==(const v3 &lhs, const v3 &rhs)
{
    return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
}
*/

inline std::ostream &operator<<(std::ostream &os, v3 rhs)
{
    os << rhs.x << " " << rhs.y << " " << rhs.z;
    return os;
}


inline std::istream &operator>>(std::istream &is, v3 &rhs)
{
    
    is >> rhs.x >> rhs.y >> rhs.z;
    return is;
}
inline v3 unit(v3 v) {
    return v3(_mm_div_ps(v.value, _mm_set1_ps(v.length())));
}
typedef v3 v3f;
typedef v3 v3i;

inline v3f maxf3(v3f lhs, float max)
{
    
    return v3f(fmax(lhs.x, max), fmax(lhs.y,max), fmax(lhs.z,max));
}
inline v3f minf3(v3f lhs, float min)
{
    return v3f(fmin(lhs.x, min), fmin(lhs.y, min), fmin(lhs.z, min));
}
