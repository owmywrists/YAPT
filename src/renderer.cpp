#include "renderer.h"


void render(Hitlist scene, Screen *screen){
    HitInfo hit;
    for (int x = 0; x < screen->getWidth(); x++){
        for(int y = 0; y < screen->getHeight(); y++){
            Camera cam = Camera(500, 500,90.0);
            Ray r = Ray(float3(x,y,0), float3(0,0,-1));
            Ray ray = cam.getRay(x,y);
            //float t = 0;
            Colour colour = Colour(0,0,0);
            if (scene.isClosestIntsersection(ray, hit)){
                colour = hit.sphere.getColour();
            }
            screen->blit(x, y, colour);
        }
        
}
}
