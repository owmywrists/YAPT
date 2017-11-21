#include "material.h"

float3 cosineSample(float u1, float u2){
    const float r = sqrtf(u1);
    const float theta = 2.0 * M_PI* u2;
    const float x = r* cos(theta);
    const float y = r * sin(theta);

    return float3(x,y, sqrtf(std::max(0.0f,1 - u1)));
}

bool Emissive::scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray)const{

        attenuation = m_colour;
        return false;
}

bool Lambertian::scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray)const{
        float3 target = ray.getHit(hit.t) + hit.normal + cosineSample(drand48(),drand48());
        new_ray = Ray(ray.getHit(hit.t), target-ray.getHit(hit.t));
        attenuation = m_colour;
        return true;
}

bool Mirror::scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray)const{
    new_ray = Ray(ray.getHit(hit.t),ray.getDirection() - hit.normal * 2.0*ray.getDirection().dot(hit.normal));
    return true;
}