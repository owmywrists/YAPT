#pragma once
#include "material.h"
#include "aabb.h"
#include "drand.h"
class Surface
{
  public:
    virtual bool intersection(Ray &ray, HitInfo &hit) = 0;
    virtual std::shared_ptr<Material> getMatPtr(float3 hit) = 0;
    virtual float3 getNormal(float3 hit) = 0;
    virtual void setMaterial(std::vector<std::shared_ptr<Material>> mat_types) = 0;
    virtual AABB getBoundingBox() const = 0;
    virtual float3 getMidpoint() const = 0;
};

class Sphere : public Surface
{
  public:
    Sphere(){};
    Sphere(float3 location, float radius, std::vector<std::shared_ptr<Material>> mat_types) : m_location(location),
                                                                                                   m_radius(radius)
    {
		for (auto &mat : mat_types) {
			m_mats.push_back(mat);
		}
        //m_mat = MaterialFactory::createMaterial(mat_type, albedo);
    };
    bool intersection(Ray &ray, HitInfo &hit);
    float3 getNormal(float3 hit)
    {
        return unit(hit - m_location);
    }
    std::shared_ptr<Material> getMatPtr(float3 hit) { 
		int m = rand() % m_mats.size();
		return m_mats[m];
	}
    void setMaterial(std::vector<std::shared_ptr<Material>> mat_types)
    {
		m_mats = mat_types;
    }
    AABB getBoundingBox()const
    {
        return AABB(m_location - float3(m_radius, m_radius, m_radius), m_location +
                                                                           float3(m_radius, m_radius, m_radius));
    }
    float3 getMidpoint()const
    {
        return m_location;
    }

  private:
    float3 m_location;
    float m_radius;
	std::vector<std::shared_ptr<Material>> m_mats;
    std::shared_ptr<Material> m_mat;
};

class Triangle : public Surface
{
  public:
    Triangle(float3 v0, float3 v1, float3 v2, std::vector<std::shared_ptr<Material>> mat_types,
             float3 normal = float3()) : m_v0(v0), m_v1(v1), m_v2(v2), m_normal(normal)
    {
		for (auto &mat : mat_types) {
			m_mats.push_back(mat);
		}
        //m_mat = MaterialFactory::createMaterial(mat_type, albedo);
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
    std::shared_ptr<Material> getMatPtr(float3 hit) { 
		int m = int(hit.x()*10) % m_mats.size();
		return m_mats[m];
	}
    void setMaterial(std::vector<std::shared_ptr<Material>> mat_types)
    {
		m_mats = mat_types;
    }
    AABB getBoundingBox()const
    {


     return AABB(float3(
        std::min(std::min(v0().x(), v1().x()), v2().x() ),
        std::min(std::min(v0().y(), v1().y()), v2().y() ),
        std::min(std::min(v0().z(), v1().z()), v2().z() )),
        float3(
        std::max(std::max(v0().x(), v1().x()), v2().x() ),
        std::max(std::max(v0().y(), v1().y()), v2().y() ),
        std::max(std::max(v0().z(), v1().z()), v2().z() ))
     );
    }
    float3 getMidpoint()const
    {
        float3 sum = (v0() + v1() + v2());
        float3 avg = sum/3.0;
        return (v0() + v1() + v2()) / 3.0;
    }

  private:
    float3 m_v0, m_v1, m_v2;
	std::vector<std::shared_ptr<Material>> m_mats;
    std::shared_ptr<Material> m_mat;
    float3 m_normal;
};
