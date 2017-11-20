#include <iostream>
#include "window.h"
#include "float3.h"
#include "renderer.h"
#include "material.h"
#include "hitlist.h"

int main(){
    std::vector<Sphere> scene;
        scene.push_back(Sphere(float3(0.0, 312.7, -6.0), 300, float3(0,0.6,0),
    new Emissive()));
        scene.push_back(Sphere(float3(0.0, -1007, -1.0),1000, float3(0.6,0,0),
    new Lambertian(float3(1.0,1.0,1.0)
    )));
        scene.push_back(Sphere(float3(0.0, 1013, -1.0),1000, float3(0.6,0,0),
    new Lambertian(float3(1.0,1.0,1.0)
    )));

        scene.push_back(Sphere(float3(-1010, 0, -1.0),1000, float3(0.6,0,0),
    new Lambertian(float3(0.0,1.0,0.0)
    )));
        scene.push_back(Sphere(float3(1010, 0, -1.0),1000, float3(0.6,0,0),
    new Lambertian(float3(1.0,0.0,0.0)
    )));
        scene.push_back(Sphere(float3(0, 0, -1020),1000, float3(0.6,0,0),
    new Lambertian(float3(1.0,1.0,1.0)
    )));

            scene.push_back(Sphere(float3(5, -4, -12),3, float3(0.6,0,0),
    new Mirror()
    ));
                scene.push_back(Sphere(float3(-5, -4, -10),3, float3(0.6,0,0),
    new Mirror()
    ));

    Window *win = new Window("YAPT", 500, 500);
    while (win->isRunning()){
        win->update();
        render(scene, win->getScreenPtr());
    }

}


