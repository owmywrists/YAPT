#pragma once
#include "ray.h"
#include "float3.h"

class Camera
{
  public:
    Camera(int width, int height, float fov) : m_width(width), m_height(height), m_fov(fov){};

    Ray getRay(float x, float y);

  private:
    int m_width;
    int m_height;
    float m_fov;
};