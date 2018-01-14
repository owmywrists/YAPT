#include "material.h"

float3 sample_skybox(sf::Image &img, float u, float v)
{
	int width = img.getSize().x;
	int height = img.getSize().y;
	sf::Color temp = img.getPixel(int(u*width )%width, int(v*height)%height);
	return float3(temp.r, temp.g, temp.b);
}

float3 cosineSampleHemi(float u1, float u2)
{
    float z = std::pow(1.0 - u1, 1.0 / 1.0);
    float phi = 2.0 * M_PI * u2;
    float theda = sqrt(std::max(0.0, 1.0 - z * z));

    float theta = 2 * M_PI * u2;
    float x = theda * cos(phi);
    float y = theda * sin(phi);

    return float3(x, y, z);
}

float3 WorldSpaceHemi(float u1, float u2, float3 normal)
{

    float3 p = cosineSampleHemi(u1, u2);
    float3 v = float3(0.0, 1.0, 0.0).cross(normal);
    v = unit(v);
    float3 u = v.cross(normal);

    float3 sample = unit((u * p.x) + (v * p.y) + (normal * p.z));

    return sample;
}

bool Emissive::scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const
{
    attenuation = m_colour;
    return false;
}

bool Lambertian::scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const
{
    float3 target = ray.getHit(hit.t) + WorldSpaceHemi(drand48(), drand48(), hit.normal);
    new_ray = Ray(ray.getHit(hit.t), target - ray.getHit(hit.t));

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