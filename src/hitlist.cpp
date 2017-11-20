#include "hitlist.h"

bool Hitlist::isClosestIntsersection(Ray &ray, HitInfo &hitInfo){
    //hitInfo.t = 1e5;
    float min_hit = 1e5;
    for (Sphere &s:m_data){
        if (s.intersection(ray,hitInfo.t)){
            if (hitInfo.t < min_hit){
                min_hit = hitInfo.t; 
                //hitInfo.t = t;
                hitInfo.sphere = s;
            }   
        }
    }
    if (min_hit < 1e5){
        hitInfo.t = min_hit;
        return true;
    }
    return false;
}