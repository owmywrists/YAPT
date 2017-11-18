#include "float3.h"
#pragma once

class Ray{
public:
    Ray(float3 origin, float3 direction);
    float3 getHit(){return m_origin + m_direction*t;}
    float3 getOrigin(){return m_origin;}
    float3 getDirection(){return m_direction;}
private:
    float3 m_origin, m_direction;
    float t;
};


//could probably just make this a struct