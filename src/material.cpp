#include "material.h"



float fresnel(float ior, float ndotv) {
	float r0 = pow((1.0f - ior) / (1.0f + ior), 2);
	float x = pow(1.0f - ndotv, 5);

	return(r0 + (1.0f - r0)*x);
}


float3 cosineSampleHemi(float u1, float u2)
{
    float z = std::pow(1.0 - u1, 3.0 / 5.0);
    float phi = 2.0 * M_PI * u2;
    float theta = sqrt(std::max(0.0, 1.0 - z * z));
    float x = theta * cos(phi);
    float y = theta * sin(phi);

    return float3(x, y, z);
}

bool Emissive::scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const
{
    attenuation = m_colour;
    return false;
}

bool Lambertian::scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const
{
	
    float3 target = ray.getHit(hit.t) + cosineSampleHemi(drand48(), drand48());
    new_ray = Ray(ray.getHit(hit.t) + hit.normal*0.001, target - ray.getHit(hit.t));

    attenuation = m_colour;
    return true;
}

bool Mirror::scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const
{
	float3 r = float3(drand48(), drand48(), drand48())*glossiness;
    new_ray = Ray(ray.getHit(hit.t), ray.getDirection() - hit.normal * 2.0 * ray.getDirection().dot(hit.normal) + r);
	attenuation = m_colour;
    return true;
}

bool Mix::scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const
{
	float3 att1, att2;
	Ray nray1, nray2;
	float f = fresnel(mix, hit.normal.dot(unit(ray.getDirection()*(-1))));
	mat1->scatter(ray, hit, att1, nray1);
	mat2->scatter(ray, hit, att2, nray2);
	if (f > 1.0) f = 1.0f;
	if (drand48() > f) new_ray = nray1; else new_ray = nray2;
	attenuation = (att2* f) + (att1 * (1.0f - f));
	return true;
}

bool Transparent::scatter(Ray & ray, HitInfo & hit, float3 & attenuation, Ray & new_ray) const
{
	return false;
}



