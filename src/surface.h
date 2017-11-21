#pragma once
#include "material.h"

class Surface{
public:
    virtual bool intersection(Ray &ray, HitInfo &hit) = 0;
};