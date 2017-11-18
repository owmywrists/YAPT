#include "../ray/ray.h"
#pragma once

class Surface{
public:
    virtual bool intersection(Ray &ray, float t) = 0;
};