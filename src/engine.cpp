#include "engine.h"

void Engine::loadObjAsScene(std::string filename){
    Obj m(filename);
    auto temp = m.getScene();
    temp.push_back(new Sphere(float3(0.0, 0.5, -1.0),0.3,
    MaterialFactory::Light, float3(1.9,1.9,1.9)
    ));
    m_data = Hitlist(temp);
}

void Engine::render(Screen *screen){
    HitInfo hit;
    m_rendering_state = true;
    #pragma omp parallel for schedule(dynamic, 1) private(hit)
    for (int x = 0; x < screen->getWidth(); ++x){
        for(int y = 0; y < screen->getHeight(); ++y){
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
        return float3(0.0,0.0,0.0);
            }

}