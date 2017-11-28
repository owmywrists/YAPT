#include "engine.h"

void Engine::loadObjAsScene(std::string filename){
    Obj m(filename);
    auto temp = m.getScene();
    temp.push_back(new Sphere(float3(0.0, -22.0, -2.0),20.0,
    MaterialFactory::Diffuse, float3(0.5,0.5,0.5)
    ));
    m_data = temp;
}

void Engine::restart(){
    float rand_num = drand48();
    for(int face = 0; face < 12; face++)
        m_data[face]->setMaterial(MaterialFactory::Diffuse, float3(drand48(),drand48(),drand48()));
}

void Engine::render(Screen *screen){
    HitInfo hit;
    m_rendering_state = true;
    #pragma omp parallel for schedule(dynamic, 1) private(hit)
    for (int x = 0; x < screen->getWidth(); x++){
        for(int y = 0; y < screen->getHeight(); y++){
            Ray ortho = Ray(float3(x,y,0), float3(0,0,-1));
            float3 colour= float3(0.0, 0.0,0.0);
            float u = float(x + drand48());
            float v = float(y + drand48());
            Ray persp = m_cam.getRay(u,v);
            colour = colour + trace(persp,m_data,hit,0);
            screen->setPixel(x, (screen->getHeight()-y), colour);
        }
    }
    m_rendering_state = false;
    screen->blit();
}

float3 Engine::trace(Ray &ray, Hitlist scene,HitInfo &hit, int depth){
    

    if (scene.isClosestIntsersection(ray, hit)){
        Ray new_ray;
        float3 col(1.0,1.0,1.0);
        float3 light = hit.mat->emitted();
        if (depth < 50 && hit.mat->scatter(ray, hit,col, new_ray)){
                return light +col*trace(new_ray, scene,hit,depth+1);
            }    
        else{
            return light;
        }
        
    }else{

        float3 unit_direction = unit(ray.getDirection());
        float t = 0.5*(unit_direction.y() + 1.0);
        return float3(1.0, 1.0, 1.0)*(1.0-t) + float3(0.5, 0.7, 1.0)*t;
        //return float3(0.0,0.0,1.0);
            }

}