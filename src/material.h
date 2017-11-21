#pragma once
#include "ray.h"
#include "float3.h"
#include <memory>
float3 cosine(float u1, float u2);

class Material;

struct HitInfo{
    float t;
    float3 normal;
    std::shared_ptr<Material> mat;
};

class Material{
public:
    virtual bool scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray)const = 0;
};

class Emissive : public Material{
public:
    Emissive(float3 c): m_colour(c){};
    bool scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray)const;
private:
    float3 m_colour;
};

class Lambertian : public Material{
public:
    Lambertian(float3 c): m_colour(c){}
    bool scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray)const;
private:
    float3 m_colour;
};

class Mirror : public Material{
public:
    Mirror(){}
    bool scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray)const;
};

class MaterialFactory{
public:
    enum MaterialType{
        Light,
        Diffuse,
        Metal
    };

    static std::unique_ptr<Material> createMaterial(MaterialType type, float3 albedo){
        switch (type){
            case Light: return std::make_unique<Emissive>(albedo);
            case Diffuse: return std::make_unique<Lambertian>(albedo);
            case Metal: return std::make_unique<Mirror>();
        }

    }
};