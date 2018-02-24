#include "surface.h"

bool Sphere::intersection(Ray &ray, HitInfo &hit)
{
    v3f oc = ray.origin - m_location;
    float a = ray.direction.dot(ray.direction);
    float b = oc.dot(ray.direction);
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
    v3f edge1 = *p1 - *p0;
    v3f edge2 = *p2 - *p0;
    
    v3f h = ray.direction.cross(edge2);
    float a = edge1.dot(h);
    
    float f = 1.0 / a;
    v3f s = ray.origin - *p0;
    float u = f * (s.dot(h));
    
    if (u < 0.0 || u > 1.0) return false;
    
    v3f q = s.cross(edge1);
    float v = f * ray.direction.dot(q);
    if (v < 0.0 || u + v > 1.0) return false;
    
    float t = edge2.dot(q) * f;
    if (t > 1e-9 && t < ray.tmin)
    {
        hit.t = t;
        
        //v3f temp_normal = unit(edge1.cross(edge2));
        //temp_normal = unit((p0 - p1).cross(p0 - p2));
        v3f temp_normal = unit(*n1*u + *n2*v + *n0*(1. - u - v));
        hit.u = (uv1->x*u + uv2->x*v + uv0->x*(1. -u - v));
        hit.v = 1.0 -(uv1->y*u + uv2->y*v + uv0->y*(1. -u - v));
        hit.normal = temp_normal;
        return true;
    }
    else
    {
        return false;
    }
}