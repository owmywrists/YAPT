#include "renderer.h"

Camera cam = Camera(500, 500, 90.0);



void render(Hitlist scene, Screen *screen){
    HitInfo hit;
    omp_set_num_threads(24);
    
    
    #pragma omp parallel for schedule(dynamic, 1) private(hit)
    for (int x = 0; x < screen->getWidth(); ++x){
        //#pragma omp parallel for
        srand(time(0));
        for(int y = 0; y < screen->getHeight(); ++y){
            Ray ortho = Ray(float3(x,y,0), float3(0,0,-1));
            //srand(x);
            //colour = float3(0.0,0.0,0.0);
            float3 colour= float3(0.0, 0.0,0.0);
            float u = float(x + drand48());
            float v = float(y + drand48());
            Ray persp = cam.getRay(u,v);
            colour = colour+ trace(persp,scene,hit,0);
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
    //loat3 colour = float3(0.0,0.0,0.0);
    float3 normal = (ray.getHit(hit.t) - hit.sphere.getLocation());
    normal = unit(normal);
    float3 target = ray.getHit(hit.t) + normal + randomInUnitHemisphere();

    if (scene.isClosestIntsersection(ray, hit)){
        Ray new_ray = Ray(ray.getHit(hit.t),target-ray.getHit(hit.t));
        return trace(new_ray, scene,hit,depth+1)*0.5;
    }else{
        float3 u_d = unit(ray.getDirection());
        float t = (u_d.y() + 1.0)*0.5;
        return float3(1.0,1.0,1.0)*(1.0-t) + float3(0.5,0.7,1.0)*t;
        //return float3(0.5, 0.5, 0.5);
    }

}