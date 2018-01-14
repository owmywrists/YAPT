#pragma once
#include "ray.h"
#include "float3.h"
#include <memory>
#include "drand.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML\Graphics.hpp>
class Material;

float3 sample_skybox(sf::Image &img, float u, float v);

struct HitInfo
{
    float t;
    float3 normal;
    std::shared_ptr<Material> mat;
};

class Material
{
  public:
    virtual bool scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const = 0;
    virtual float3 emitted() const { return float3(0.0, 0.0, 0.0); }
};

class Emissive : public Material
{
  public:
    Emissive(float3 c) : m_colour(c){};
    bool scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const;
    float3 emitted() const { return m_colour; }

  private:
    float3 m_colour;
};

class Lambertian : public Material
{
  public:
    Lambertian(float3 c) : m_colour(c) {}
    bool scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const;

  private:
    float3 m_colour;
};

class Mirror : public Material
{
  public:
    Mirror(float3 c, float glossiness = 0.0f): m_colour(c), glossiness(glossiness){}
    bool scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const;

private:
	float3 m_colour;
	float glossiness;
};

class MaterialFactory
{
    //material factory allows me to change materials at runtime
  public:
    enum MaterialType
    {
        Light,
        Diffuse,
        Metal
    };
    //I used different names than the subclasses as I may mix and match materials

    static std::unique_ptr<Material> createMaterial(MaterialType type, float3 albedo)
    {
        switch (type)
        {
        case Light:
            return std::make_unique<Emissive>(albedo);
        case Diffuse:
            return std::make_unique<Lambertian>(albedo);
        case Metal:
            return std::make_unique<Mirror>(albedo);
        }
    }
};
