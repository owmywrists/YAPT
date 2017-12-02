#ifndef AABB_H
#define AABB_H

#include "float3.h"
#include "ray.h"
class AABB
{
  public:
    AABB() {}
    AABB(float3 min, float3 max) : m_min(min), m_max(max) {}

    float3 getMin() const { return m_min; }
    float3 getMax() const { return m_max; }

    bool hit(Ray &ray, float &t) const
    {
        
            float tmin, tmax;
            for (int a=0; a <3; a++){
                float invD = 1.0f / ray.getDirection()[a];
                float t0 = (getMin()[a] - ray.getOrigin()[a])*invD;
                float t1 = (getMax()[a] - ray.getOrigin()[a]) * invD;
                if (invD <0.0f){
                    std::swap(t0,t1);
                }
                tmin = t0 > tmin ? t0: tmin;
                tmax = t1 < tmax ? t1 : tmax;
                t = tmin;
                if (tmax <=)
            }

            
/*
        float tx1 = (m_min.x() - ray.getOrigin().x()) / ray.getDirection().x();
        float tx2 = (m_max.x() - ray.getOrigin().x()) / ray.getDirection().x();

        float tmin = std::min(tx1, tx2);
        float tmax = std::max(tx1, tx2);

        float ty1 = (m_min.y() - ray.getOrigin().y()) / ray.getDirection().y();
        float ty2 = (m_max.y() - ray.getOrigin().y()) / ray.getDirection().y();

        tmin = std::max(tmin, std::min(ty1, ty2));
        tmax = std::min(tmax, std::max(ty1, ty2));

        float tz1 = (m_min.z() - ray.getOrigin().z()) / ray.getDirection().z();
        float tz2 = (m_max.z() - ray.getOrigin().z()) / ray.getDirection().z();

        tmin = std::max(tmin, std::min(tz1, tz2));
        tmax = std::min(tmax, std::max(tz1, tz2));

        t = tmin;

        return tmax >= tmin;
        */
    }

    void expand(const AABB &a)
    {
        if (a.getMin().x() < m_min.x())
            m_min.setX(a.getMin().x());
        if (a.getMin().y() < m_min.y())
            m_min.setY(a.getMin().y());
        if (a.getMin().z() < m_min.z())
            m_min.setZ(a.getMin().z());

        if (a.getMax().x() > getMax().x())
            getMax().setX(a.getMax().x());
        if (a.getMax().y() > getMax().y())
            getMax().setY(a.getMax().y());
        if (a.getMax().z() > getMax().z())
            getMax().setZ(a.getMax().z());
    }

    int getLongestAxis()
    {
        float3 diff = m_max - m_min;
        if (diff.x() > diff.y() && diff.x() > diff.z())
            return 0;
        if (diff.y() > diff.x() && diff.y() > diff.z())
            return 1;
        return 2;
    }

  private:
    float3 m_max, m_min;
};

#endif