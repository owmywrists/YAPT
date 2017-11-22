#pragma once
#include <iostream>
#include <stdlib.h>
#include <math.h>



class float3{ 
public:

    float3(){entity[0] = 0.0; entity[1] = 0.0; entity[2] = 0.0;}
    float3(float x, float y, float z){
        entity[0] = x;
        entity[1] = y;
        entity[2] = z;
    }
    float x() const {return entity[0];}
    float y() const {return entity[1];}
    float z() const {return entity[2];}
    float dot(float3 rhs){
        return this->x()*rhs.x() + this->y()*rhs.y() + this->z()*rhs.z();
    }
    float3 cross(float3 rhs){
        return float3(this->y()*rhs.z() - this->z()*rhs.y(),
                      this->z()*rhs.x() - this->x()*rhs.z(),
                      this->x()*rhs.y() - this->y()*rhs.x());
    }
    float length(){
        return sqrt(this->dot(*this));
    }
    float sqrtLength(){
        return this->dot(*this);
    }

    inline float3 unit(float3 v);
    void setX(float num){ entity[0] = num;}
    void setY(float num){ entity[1] = num;}
    void setZ(float num){ entity[2] = num;}
    void set(float x, float y, float z) {
        setX(x);
        setY(y);
        setZ(z);
    }
    inline float operator[](int i)const { return entity[i];}

    friend std::ostream& operator<<(std::ostream& os, float3 &rhs);
    friend std::istream& operator>>(std::istream& is, float3 &rhs);

    float entity[3];

};

inline float3 operator+(const float3 &lhs, const float &rhs){
    return float3(lhs.x() + rhs, lhs.y() + rhs, lhs.z() + rhs);
}

inline float3 operator-(const float3 &lhs, const float &rhs){
    return float3(lhs.x() - rhs, lhs.y() - rhs, lhs.z() - rhs);
}

inline float3 operator/(const float3 &lhs, const float &rhs){
    return float3(lhs.x() / rhs, lhs.y() / rhs, lhs.z() / rhs);
}

inline float3 operator*(const float3 &lhs, const float &rhs){
    return float3(lhs.x() * rhs, lhs.y() * rhs, lhs.z() * rhs);
}

inline float3 operator+(const float3 &lhs, const float3 &rhs){
    return float3(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
}
inline float3 operator-(const float3 &lhs, const float3 &rhs){
    return float3(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
}

inline float3 operator*(const float3 &lhs, const float3 &rhs){
    return float3(lhs.x() * rhs.x(), lhs.y() * rhs.y(), lhs.z() * rhs.z());
}

inline bool operator==(const float3 &lhs, const float3 &rhs){
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z());
}


inline std::ostream& operator<<(std::ostream &os, float3 &rhs){
    os << rhs.x() << " " << rhs.y() << " " << rhs.z();
    return os;
}

inline std::istream& operator>>(std::istream &is, float3 &rhs){
    is >> rhs.entity[0] >> rhs.entity[1] >> rhs.entity[2];
    return is;
    
}

inline float3 unit(float3 v){
    return v/v.length();
}