#pragma once
#include "material.h"

class Surface
{
  public:
    virtual bool intersection(Ray &ray, HitInfo &hit) = 0;
    virtual std::shared_ptr<Material> getMatPtr() = 0;
    virtual float3 getNormal(float3 hit) = 0;
    virtual void setMaterial(MaterialFactory::MaterialType mat_type, float3 albedo) = 0;
};

class Sphere : public Surface
{
  public:
    Sphere(){};
    Sphere(float3 location, float radius, MaterialFactory::MaterialType mat_type, float3 albedo) : m_location(location),
                                                                                                   m_radius(radius)
    {
        m_mat = MaterialFactory::createMaterial(mat_type, albedo);
    };
    bool intersection(Ray &ray, HitInfo &hit);
    float3 getNormal(float3 hit)
    {
        return unit(hit - m_location);
    }
    std::shared_ptr<Material> getMatPtr() { return m_mat; }
    void setMaterial(MaterialFactory::MaterialType mat_type, float3 albedo)
    {
        m_mat = MaterialFactory::createMaterial(mat_type, albedo);
    }

  private:
    float3 m_location;
    float m_radius;
    std::shared_ptr<Material> m_mat;
};

class Triangle : public Surface
{
  public:
    Triangle(float3 v0, float3 v1, float3 v2, MaterialFactory::MaterialType mat_type, float3 albedo,
             float3 normal = float3()) : m_v0(v0), m_v1(v1), m_v2(v2), m_normal(normal)
    {
        m_mat = MaterialFactory::createMaterial(mat_type, albedo);
    };
    ~Triangle();
    bool intersection(Ray &ray, HitInfo &hit);
    float3 getNormal(float3 hit)
    {
        float3 edge1 = m_v1 - m_v0;
        float3 edge2 = m_v2 - m_v0;
        return unit(edge1.cross(edge2));
    }
    float3 v0() const { return m_v0; }
    float3 v1() const { return m_v1; }
    float3 v2() const { return m_v2; }
    std::shared_ptr<Material> getMatPtr() { return m_mat; }
    void setMaterial(MaterialFactory::MaterialType mat_type, float3 albedo)
    {
        m_mat = MaterialFactory::createMaterial(mat_type, albedo);
    }

  private:
    float3 m_v0, m_v1, m_v2;
    std::shared_ptr<Material> m_mat;
    float3 m_normal;
};