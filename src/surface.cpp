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
    float3 edge1 = v1->pos - v0->pos;
    float3 edge2 = v2->pos - v0->pos;
    
    float3 h = ray.getDirection().cross(edge2);
    float a = edge1.dot(h);
    
    float f = 1.0 / a;
    float3 s = ray.getOrigin() - v0->pos;
    float u = f * (s.dot(h));
    
    if (u < 0.0 || u > 1.0) return false;
    
    float3 q = s.cross(edge1);
    float v = f * ray.getDirection().dot(q);
    if (v < 0.0 || u + v > 1.0) return false;
    
    float t = edge2.dot(q) * f;
    if (t > 1e-9 && t < ray.tmin)
    {
        hit.t = t;
        
        //float3 temp_normal = unit(edge1.cross(edge2));
        //temp_normal = unit((v0->pos - v1->pos).cross(v0->pos - v2->pos));
        float3 temp_normal = unit(v1->normal*u + v2->normal*v + v0->normal*(1. - u - v));
        hit.u = (v1->tx*u + v2->tx*v + v0->tx*(1. -u - v));
        hit.v = 1.0 -(v1->ty*u + v2->ty*v + v0->ty*(1. -u - v));
        hit.normal = temp_normal;
        return true;
    }
    else
    {
        return false;
    }
}