#include "surface.h"

bool Sphere::intersection(Ray &ray, HitInfo &hit)
{
    float3 oc = ray.getOrigin() - m_location;
    float a = ray.getDirection().dot(ray.getDirection());
    float b = oc.dot(ray.getDirection());
    float c = oc.dot(oc) - m_radius * m_radius;
    float disc = b * b - a * c;
    if (disc <= 0.0)
        return false;
    else
    {
        float temp = (-b - sqrt(disc)) / a;
        if (temp < 1e5 && temp > 1e-5)
        {
            hit.t = temp;
            return true;
        }
        temp = (-b + sqrt(disc)) / a;
        if (temp < 1e5 && temp > 1e-5)
        {
            hit.t = temp;
            return true;
        }
    }

    return false;
}

Triangle::~Triangle()
{
}

bool Triangle::intersection(Ray &ray, HitInfo &hit)
{
    float3 edge1 = m_v1 - m_v0;
    float3 edge2 = m_v2 - m_v0;
    float3 h = ray.getDirection().cross(edge2);
    float a = edge1.dot(h);

    float f = 1.0 / a;
    float3 s = ray.getOrigin() - m_v0;
    float u = f * (s.dot(h));

    if (u < 0.0 || u > 1.0)
        return false;

    float3 q = s.cross(edge1);
    float v = f * ray.getDirection().dot(q);
    if (v < 0.0 || u + v > 1.0)
        return false;
    float t = edge2.dot(q) * f;
    if (t > 1e-9)
    {
        hit.t = t;
        return true;
    }
    else
    {
        return false;
    }
}