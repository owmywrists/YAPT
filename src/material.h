#pragma once
#include "ray.h"
#include "float3.h"

float3 cosine(float u1, float u2);

class Material;

struct HitInfo{
    float t;
    float3 normal;
    Material *mat;
};


class Material{
public:
    virtual bool scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray)const = 0;
};

class Emissive : public Material{
public:
    Emissive(){};
    bool scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray)const;
};

class Lambertian : public Material{
public:
    Lambertian(float3 c): colour(c){}
    bool scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray)const;
private:
    float3 colour;
};

class Mirror : public Material{
public:
    Mirror(){}
    bool scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray)const;
};