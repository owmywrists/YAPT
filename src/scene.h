#include <vector>
#include "sphere.h"
#include "float3.h"
#pragma once

class Scene{
public:
    Scene(std::vector<Sphere> &spheres);
    bool isClosestIntsersection(Ray &ray, float t);

private:
    std::vector<Sphere> m_data;
};