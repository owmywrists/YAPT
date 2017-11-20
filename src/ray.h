#pragma once
#include "float3.h"


class Ray{
public:
    Ray(float3 origin, float3 direction);
    Ray(){};
    float3 getHit(float t){return m_origin + m_direction*t;}
    float3 getOrigin(){return m_origin;}
    float3 getDirection(){return m_direction;}
private:
    float3 m_origin, m_direction;
    //float t;
};


//could probably just make this a struct