#pragma once
#include <vector>
#include "surface.h"
#include "float3.h"

class Hitlist
{
  public:
    Hitlist(std::vector<Surface *> surfaces) : m_data(surfaces){};
    Hitlist(){};
    bool isClosestIntsersection(Ray &ray, HitInfo &hitInfo);

  private:
    std::vector<Surface *> m_data;
};