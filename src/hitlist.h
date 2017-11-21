#pragma once
#include <vector>
#include "surface.h"
#include "float3.h"



class Hitlist{
public:
    Hitlist(std::vector<Sphere> &spheres): m_data(spheres){};
    bool isClosestIntsersection(Ray &ray, HitInfo &hitInfo);

private:
    std::vector<Sphere> m_data;
};