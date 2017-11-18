#pragma once
#include "surface.h"
#include "colour.h"



class Sphere : public Surface{
public:
    Sphere(float3 location, float radius, Colour colour);
    bool intersection(Ray &ray, float t);
    Colour getColour(){return m_colour;}
private:
    float3 m_location;
    float m_radius;
    Colour m_colour;
};