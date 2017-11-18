#include "../surface/surface.h"
#pragma once


class Sphere : public Surface{
public:
    Sphere(float3 location, float radius);
    bool intersection(Ray &ray, float t);
private:
    float3 m_location;
    float m_radius;
};