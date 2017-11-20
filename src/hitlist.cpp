#include "hitlist.h"

bool Hitlist::isClosestIntsersection(Ray &ray, HitInfo &hitInfo){
    float min_hit = 1e5;
    for (Sphere &s:m_data){
        if (s.intersection(ray,hitInfo)){
            if (hitInfo.t < min_hit ){
                hitInfo.normal = unit(ray.getHit(hitInfo.t) - s.getLocation());
                hitInfo.mat = s.getMatPtr();
                min_hit = hitInfo.t;
            }   
        }
    }
    if (min_hit < 1e5 && min_hit > 1e-5){
        hitInfo.t = min_hit;
        return true;
    }
    return false;
}