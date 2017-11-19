#include <vector>
#include "sphere.h"
#include "float3.h"
#pragma once

struct HitInfo{
    Sphere sphere;
    float t;
};

class Hitlist{
public:
    Hitlist(std::vector<Sphere> &spheres): m_data(spheres){};
    bool isClosestIntsersection(Ray &ray, HitInfo &hitInfo);

private:
    std::vector<Sphere> m_data;
};