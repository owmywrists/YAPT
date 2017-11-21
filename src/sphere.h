#pragma once
#include "surface.h"
#include "material.h"


class Sphere : public Surface{
public:
    Sphere(){};
    Sphere(float3 location, float radius,MaterialFactory::MaterialType mat_type, float3 albedo): 
        m_location(location),
        m_radius(radius){
            m_mat = MaterialFactory::createMaterial(mat_type, albedo);
        }
    bool intersection(Ray &ray, HitInfo &hit);
    float3 getLocation(){return m_location;}
    std::shared_ptr<Material>getMatPtr(){return m_mat;}
private:
    float3 m_location;
    float m_radius;
    std::shared_ptr<Material> m_mat;

};