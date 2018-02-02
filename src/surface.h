#pragma once
#include "material.h"
#include "aabb.h"
#include "drand.h"

class Surface
{
    public:
    virtual bool intersection(Ray &ray, HitInfo &hit) = 0;
    virtual std::shared_ptr<Material> getMatPtr() = 0;
    virtual void setMaterial(std::shared_ptr<Material> mat_type) = 0;
    virtual AABB getBoundingBox() const = 0;
    virtual float3 getMidpoint() const = 0;
};

struct Vertex
{
    float3 pos;
    float3 normal;
    float tx, ty;
};

struct UV
{
    float x,y;
};

class Sphere : public Surface
{
    public:
    Sphere(){};
    Sphere(float3 location, float radius, std::shared_ptr<Material> mat_type) : m_location(location),
    m_radius(radius),
    m_mat(mat_type) {}
    
    bool intersection(Ray &ray, HitInfo &hit);
    
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
    Triangle(float3 *pa, float3 *pb, float3 *pc,
             float3 *na, float3 *nb, float3 *nc,
             UV *uva, UV *uvb, UV *uvc,
             std::shared_ptr<Material> mat_type): m_mat(mat_type),
    p0(pa), p1(pb), p2(pc), n0(na), n1(nb), n2(nc), uv0(uva), uv1(uvb), uv2(uvc){}
    
    ~Triangle();
    bool intersection(Ray &ray, HitInfo &hit);
    
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
            std::min(std::min(p0->x, p1->x), p2->x ),
            std::min(std::min(p0->y, p1->y), p2->y ),
            std::min(std::min(p0->z, p1->z), p2->z )),
                    float3(
            std::max(std::max(p0->x, p1->x), p2->x ),
            std::max(std::max(p0->y, p1->y), p2->y ),
            std::max(std::max(p0->z, p1->z), p2->z )));
    }
    float3 getMidpoint()const
    {
        return (*p0 + *p1 + *p2) /3.0;
    }
    /*
    bool contains_vertex(Vertex *v)
    {
        //return (v == v0) || (v == v1) || (v == v2);
    }
    */
    float3 getNormal()
    {
        return unit((*p1 - *p0).cross(*p2 - *p0));
    }
    private:
    //Vertex *v0, *v1, *v2;
    float3 *p0, *p1, *p2;
    float3 *n0, *n1, *n2;
    UV *uv0, *uv1, *uv2;
    std::shared_ptr<Material> m_mat;
};
