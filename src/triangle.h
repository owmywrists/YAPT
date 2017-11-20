#pragma once
#include "surface.h"

class Triangle : public Surface{
public:
    Triangle();
    ~Triangle();
    bool intersection(Ray &ray, float &t);
private:

};