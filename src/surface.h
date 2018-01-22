#pragma once
#include "material.h"
#include "aabb.h"
#include "drand.h"

class Surface
{
  public:
    virtual bool intersection(Ray &ray, HitInfo &hit) = 0;
    virtual std::shared_ptr<Material> getMatPtr() = 0;
    virtual float3 getNormal(float3 hit) = 0;
	virtual void setMaterial(std::shared_ptr<Material> mat_type) = 0;
    virtual AABB getBoundingBox() const = 0;
    virtual float3 getMidpoint() const = 0;
};

struct Vertex
{
	float3 pos;
	float3 normal;
};

class Sphere : public Surface
{
  public:
    Sphere(){};
	Sphere(float3 location, float radius, std::shared_ptr<Material> mat_type) : m_location(location),
		m_radius(radius),
		m_mat(mat_type) {}

    bool intersection(Ray &ray, HitInfo &hit);
    float3 getNormal(float3 hit)
    {
        return unit(hit - m_location);
    }
    void setMaterial(std::shared_ptr<Material> mat_type)
    {
		m_mat = mat_type;
    }
    AABB getBoundingBox()const
    {
        return AABB(m_location - float3(m_radius, m_radius, m_radius), m_location +
                                                                           float3(m_radius, m_radius, m_radius));
    }
	std::shared_ptr<Material> getMatPtr() { return m_mat; }
    float3 getMidpoint()const
    {
        return m_location;
    }

  private:
    float3 m_location;
    float m_radius;
    std::shared_ptr<Material> m_mat;
};

class Triangle : public Surface
{
  public:
	  Triangle(Vertex *va, Vertex *vb, Vertex *vc, std::shared_ptr<Material> mat_type): m_mat(mat_type),
		  v0(va), v1(vb), v2(vc)
	  {
		 // v0.normal = v1.normal = v2.normal = float3();
		 m_normal = unit((v1->pos - v0->pos).cross(v2->pos - v0->pos));
	  }

    ~Triangle();
    bool intersection(Ray &ray, HitInfo &hit);

    float3 getNormal(float3 hit)
    {
		return m_normal;
    }
	float3 getFaceNormal()
	{
		return unit((v1->pos - v0->pos).cross(v2->pos - v0->pos));
	}
    std::shared_ptr<Material> getMatPtr() { 
		return m_mat;
	}
    void setMaterial(std::shared_ptr<Material> mat_type)
    {
		m_mat = mat_type;
    }
    AABB getBoundingBox()const
    {
     return AABB(float3(
        std::min(std::min(v0->pos.x, v1->pos.x), v2->pos.x ),
        std::min(std::min(v0->pos.y, v1->pos.y), v2->pos.y ),
        std::min(std::min(v0->pos.z, v1->pos.z), v2->pos.z )),
        float3(
        std::max(std::max(v0->pos.x, v1->pos.x), v2->pos.x ),
        std::max(std::max(v0->pos.y, v1->pos.y), v2->pos.y ),
        std::max(std::max(v0->pos.z, v1->pos.z), v2->pos.z )));
    }
    float3 getMidpoint()const
    {
        float3 sum = (v0->pos + v1->pos + v2->pos);
        float3 avg = sum/3.0;
        return (v0->pos + v1->pos + v2->pos) / 3.0;
    }

	bool contains_vertex(Vertex *v)
	{
		return (v == v0) || (v == v1) || (v == v2);
	}
  private:
	Vertex *v0, *v1, *v2;
    std::shared_ptr<Material> m_mat;
    float3 m_normal;
};
