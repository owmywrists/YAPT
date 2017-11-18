#include "renderer.h"

void render(Screen *screen){
    for (int x = 0; x < screen->getWidth(); x++)
        for(int y = 0; y < screen->getHeight(); y++){
            Sphere s = Sphere(float3(100,150,1),20.0, Colour(255,0,0));
            Ray ray = Ray(float3(x,y,0),float3(0,0,-1));
            float t = 0;
            Colour colour = Colour((x+SDL_GetTicks()/10)%255,(y+SDL_GetTicks()/5)%255,255);
            //Colour colour = Colour(255,255,255);
            if (s.intersection(ray, t)){
                //std::cout << "I HAVE DONE THE INTERSECT" << std::endl;
                colour = s.getColour();
            }
            
            screen->blit(x, y, colour);
        }
}