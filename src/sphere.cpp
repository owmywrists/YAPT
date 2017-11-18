#include "sphere.h"

Sphere::Sphere(float3 location, float radius, Colour colour){
    m_location = location;
    m_radius = radius;
    m_colour = colour;
}

bool Sphere::intersection(Ray &ray, float t){
    float3 oc = ray.getOrigin() - m_location;
    float a = ray.getDirection().dot(ray.getDirection());
    float b = oc.dot(ray.getDirection());
    float c = oc.dot(oc) - m_radius*m_radius;
    float disc = b*b - a*c;
    if (disc > 0.0){
        float temp = (-b - sqrt(disc))/a;
        if (temp < 1e5 && temp > 1e-5){
            t = temp;
            return true;
        }
        temp = (-b + sqrt(disc))/a;
        if (temp < 1e5 && temp > 1e-5){
            t = temp;
            return true;
        }
    } 

    return false;
}