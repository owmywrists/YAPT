#pragma once
#include "surface.h"
#include "colour.h"



class Sphere : public Surface{
public:
    Sphere(){};
    Sphere(float3 location, float radius, float3 colour): m_location(location),
                                                          m_radius(radius),
                                                          m_colour(colour){};
    bool intersection(Ray &ray, float &t);
    float3 getColour(){return m_colour;}
    float3 getLocation(){return m_location;}
private:
    float3 m_location;
    float m_radius;
    float3 m_colour;
};