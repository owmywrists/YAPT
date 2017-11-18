#include "scene.h"


Scene::Scene(std::vector<Sphere> &spheres){
    m_data = spheres;
}

bool Scene::isClosestIntsersection(Ray &ray, float t){
    float min_hit = 1e5;
    for (Sphere &s:m_data){

        if (s.intersection(ray,t)){
            if (t < min_hit){
                min_hit = t; 
                
            }   
        }
    }
}