#ifndef AABB_H
#define AABB_H

#include "float3.h"
#include "ray.h"
class AABB
{
  public:
    AABB(float3 min=float3(), float3 max=float3()) : min(min), max(max) {}

    bool hit(Ray &ray, float &t)
    {
        /*
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
            }
            return tmax >= tmin;

           */ 
          float3 inv_rd = ray.getDirection();

        float tx1 = (min.x() - ray.getOrigin().x()) / inv_rd.x();
        float tx2 = (max.x() - ray.getOrigin().x()) / inv_rd.x();

        float tmin = std::min(tx1, tx2);
        float tmax = std::max(tx1, tx2);

        float ty1 = (min.y() - ray.getOrigin().y()) / inv_rd.y();
        float ty2 = (max.y() - ray.getOrigin().y()) / inv_rd.y();

        tmin = std::max(tmin, std::min(ty1, ty2));
        tmax = std::min(tmax, std::max(ty1, ty2));

        float tz1 = (min.z() - ray.getOrigin().z()) / inv_rd.z();
        float tz2 = (max.z() - ray.getOrigin().z()) / inv_rd.z();

        tmin = std::max(tmin, std::min(tz1, tz2));
        tmax = std::min(tmax, std::max(tz1, tz2));

        t = tmin;

        return tmax >= tmin;
        
    }

    void expand(const AABB &a)
    {
        if (a.min.x() < min.x())
            min.setX(a.min.x());

        if (a.min.y() < min.y())
            min.setY(a.min.y());

        if (a.min.z() < min.z())
            min.setZ(a.min.z());


        if (a.max.x() > max.x())
            max.setX(a.max.x());

        if (a.max.y() > max.y())
            max.setY(a.max.y());
            
        if (a.max.z() > max.z())
            max.setZ(a.max.z());
    }

    int getLongestAxis()
    {
        float3 diff = max - min;
        if (diff.x() > diff.y() && diff.x() > diff.z())
            return 0;
        if (diff.y() > diff.x() && diff.y() > diff.z())
            return 1;
        return 2;
    }

  private:
    float3 max, min;
};

#endif