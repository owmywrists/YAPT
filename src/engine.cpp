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
    float * temp_col = m_screen->getColour();
    float3 rand_num = float3(temp_col[0],temp_col[1], temp_col[2]);
    std::cout << rand_num << std::endl;
    for(int face = 0; face < 12; face++)
        m_data[face]->setMaterial(MaterialFactory::Diffuse, float3(rand_num));
    m_screen->reset();
}
void Engine::loadBuffer(std::vector<float3> image){
    for (int x = 0; x < m_screen->getWidth(); x++){
        for (int y = 0; y < m_screen->getHeight(); y++){
            float3 col = image[x + m_screen->getWidth()*y];
            m_screen->setPixel(x,(m_screen->getHeight()-y),col);
        }
    }
}
void Engine::render(){
    HitInfo hit;
    omp_set_num_threads(24);
    std::vector<float3> temp_img;
    temp_img.resize(m_screen->getWidth()*m_screen->getHeight());
    #pragma omp parallel for schedule(dynamic, 1) private(hit)
    for (int x = 0; x < m_screen->getWidth(); x++){
    for(int y = 0; y < m_screen->getHeight(); y++){
                Ray ortho = Ray(float3(x,y,0), float3(0,0,-1));
                float3 colour= float3(0.0, 0.0,0.0);
                float u = float(x + drand48());
                float v = float(y + drand48());
                Ray persp = m_cam.getRay(u,v);
                colour = colour + trace(persp,m_data,hit,0);
                temp_img[x + y*m_screen->getWidth()] = colour;
                }
    }
    m_screen->loadImage(temp_img);
    m_screen->blit();
    if(m_screen->getState()) restart();
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