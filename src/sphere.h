#pragma once
#include "surface.h"
#include "material.h"


class Sphere : public Surface{
public:
    Sphere(){};
    Sphere(float3 location, float radius, float3 colour, Material *mat): m_location(location),
                                                          m_radius(radius),
                                                          m_colour(colour),
                                                          m_mat(mat){};
    bool intersection(Ray &ray, HitInfo &hit);
    float3 getColour(){return m_colour;}
    float3 getLocation(){return m_location;}
    Material* getMatPtr(){return m_mat;}
private:
    float3 m_location;
    float m_radius;
    float3 m_colour;
    Material *m_mat;

};