#include "surface.h"

bool Sphere::intersection(Ray &ray, HitInfo &hit){
    float3 oc = ray.getOrigin() - m_location;
    float a = ray.getDirection().dot(ray.getDirection());
    float b = oc.dot(ray.getDirection());
    float c = oc.dot(oc) - m_radius*m_radius;
    float disc = b*b - a*c;
    if (disc <= 0.0)
        return false;
    else{
        float temp = (-b - sqrt(disc))/a;
        if (temp < 1e5 && temp > 1e-5){
            //hit.mat = m_mat;
            hit.t = temp;
            return true;
        }
        temp = (-b + sqrt(disc))/a;
        if (temp < 1e5 && temp > 1e-5){
            //hit.mat = m_mat;
            hit.t = temp;
            return true;
        }
    } 

    return false;
}
