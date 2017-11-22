#include "renderer.h"

Camera cam = Camera(640, 480, 90.0);
float3 cosineSampleHemisphere(float u1, float u2);


void render(Hitlist scene, Screen *screen){
    HitInfo hit;
    #pragma omp parallel for schedule(dynamic, 1) private(hit)
    for (int x = 0; x < screen->getWidth(); ++x){
        for(int y = 0; y < screen->getHeight(); ++y){
            Ray ortho = Ray(float3(x,y,0), float3(0,0,-1));
            float3 colour= float3(0.0, 0.0,0.0);
            float u = float(x + drand48());
            float v = float(y + drand48());
            Ray persp = cam.getRay(u,v);
            colour = colour + trace(persp,scene,hit,0);
            screen->setPixel(x, y, colour);
        }
        
}

screen->blit();
}

float3 randomInUnitHemisphere(){
    float3 p;
    do {
        p = float3(drand48(),drand48(),drand48())*2.0 - float3(1.0,1.0,1.0);

    }while (p.sqrtLength() >= 1.0);
    return p;
}


float3 trace(Ray &ray, Hitlist scene,HitInfo &hit, int depth){
    

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