#include "material.h"

float fresnel(float ior, float ndotv) {
    float r0 = pow((1.0f - ior) / (1.0f + ior), 2);
    float x = pow(1.0f - ndotv, 5);
    
    return(r0 + (1.0f - r0)*x);
}

float3 cosineSampleHemi(float u1, float u2)
{
    
    float z = sqrt(1-u2);
    float phi = 2*M_PI*u1;
    float x = cos(phi)*2*sqrt(u2);
    float y = sin(phi)*2*sqrt(u2);
    return float3(x, y, z);
    
}

bool Emissive::BSDF(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const
{
    //attenuation = float3(hit.normal.x,hit.normal.y, hit.normal.z);
    return false;
}

bool Lambertian::BSDF(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const
{
    float3 offset = hit.normal*(1e-5);
    float u1 = drand48(); float u2 = drand48();
    hit.costheta = u1;
    new_ray = Ray(ray.getHit(hit.t) + offset, make_orthonormal_basis(cosineSampleHemi(u1, u2), hit.normal));
    
    attenuation = sample_texture(texture, hit.u, hit.v);
    return true;
}

bool Mirror::BSDF(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const
{
    float3 r = float3(drand48(), drand48(), drand48())*glossiness;
    new_ray = Ray(ray.getHit(hit.t), ray.getDirection() - hit.normal * 2.0 * ray.getDirection().dot(hit.normal) + r);
    attenuation = m_colour;
    return true;
}

bool Mix::BSDF(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const
{
    float3 att1, att2;
    Ray nray1, nray2;
    float f = fresnel(mix, hit.normal.dot(unit(ray.getDirection()*(-1))));
    mat1->BSDF(ray, hit, att1, nray1);
    mat2->BSDF(ray, hit, att2, nray2);
    if (f > 1.0) f = 1.0f;
    if (drand48() > f) new_ray = nray1; else new_ray = nray2;
    attenuation = (att2* f) + (att1 * (1.0f - f));
    return true;
}

bool Glass::BSDF(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const
{
    float3 r = float3(drand48(), drand48(), drand48())*glossiness;
    new_ray = Ray(ray.getHit(hit.t), ray.getDirection() - hit.normal * 2.0 * ray.getDirection().dot(hit.normal*(-1)) + r);
    attenuation = m_colour;
    return true;
}