#include "material.h"

float fresnel(float ior, float ndotv) {
    float r0 = pow((1.0f - ior) / (1.0f + ior), 2);
    float x = pow(1.0f - ndotv, 5);
    
    return(r0 + (1.0f - r0)*x);
}

v3f cosineSampleHemi(float u1, float u2)
{
    
    float z = sqrtf(1-u2);
    float phi = 2*M_PI*u1;
    float x = cos(phi)*2*sqrtf(u2);
    float y = sin(phi)*2*sqrtf(u2);
    return v3f(x, y, z);
    
}

bool Emissive::BRDF(Ray &ray, HitInfo &hit, v3f &attenuation, Ray &new_ray) const
{
    return false;
}



bool Lambertian::BRDF(Ray &ray, HitInfo &hit, v3f &attenuation, Ray &new_ray) const
{
    v3f offset = hit.normal*(1e-5);
    float u1 = drand48(); float u2 = drand48();
    hit.costheta = u1;
    new_ray = Ray(ray.get_hit(hit.t) + offset, make_orthonormal_basis(cosineSampleHemi(u1, u2), hit.normal));
    
    attenuation = sample_texture(texture, hit.u, hit.v);
    return true;
}

bool Mirror::BRDF(Ray &ray, HitInfo &hit, v3f &attenuation, Ray &new_ray) const
{
    v3f r = v3f(drand48(), drand48(), drand48())*glossiness;
    new_ray = Ray(ray.get_hit(hit.t), ray.direction - hit.normal * 2.0 * ray.direction.dot(hit.normal) + r);
    attenuation = m_colour;
    return true;
}

bool Mix::BRDF(Ray &ray, HitInfo &hit, v3f &attenuation, Ray &new_ray) const
{
    v3f att1, att2;
    Ray nray1, nray2;
    float f = fresnel(mix, hit.normal.dot(unit(ray.direction*(-1))));
    mat1->BRDF(ray, hit, att1, nray1);
    mat2->BRDF(ray, hit, att2, nray2);
    if (f > 1.0) f = 1.0f;
    if (drand48() > f) new_ray = nray1; else new_ray = nray2;
    attenuation = (att2* f) + (att1 * (1.0f - f));
    return true;
}

bool Glass::BRDF(Ray &ray, HitInfo &hit, v3f &attenuation, Ray &new_ray) const
{
    v3f r = v3f(drand48(), drand48(), drand48())*glossiness;
    new_ray = Ray(ray.get_hit(hit.t), ray.direction - hit.normal * 2.0 * ray.direction.dot(hit.normal*(-1)) + r);
    attenuation = m_colour;
    return true;
}