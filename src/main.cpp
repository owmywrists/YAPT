#include <iostream>
#include "window.h"
#include "float3.h"
#include "renderer.h"
#include "material.h"
#include "hitlist.h"

int main(){
    std::vector<Surface*> scene;
    /*
        scene.push_back(new Sphere(float3(0.0, 4.99, -7.0), 3,
        MaterialFactory::Diffuse, float3(1.9,1.9,1.9)
    ));
    */
        scene.push_back(new Sphere(float3(0.0, -1000, -1.0),1000,
    MaterialFactory::Diffuse, float3(1.0,1.0,1.0)
    ));
            scene.push_back(new Triangle(float3(-2.0, 1.0, -5.0),float3(-5.0, 0.0, -5.0),
            float3(2.0, 3.0, -3.0), MaterialFactory::Light, float3(1.9, 1.9, 1.9)
    ));
      /*  scene.push_back(Sphere(float3(0.0, 1013, -1.0),1000,
    new Lambertian(float3(1.0,1.0,1.0)
    )));

        scene.push_back(Sphere(float3(-1010, 0, -1.0),1000, 
    new Lambertian(float3(0.0,1.0,0.0)
    )));
        scene.push_back(Sphere(float3(1010, 0, -1.0),1000, 
    new Lambertian(float3(1.0,0.0,0.0)
    )));
        scene.push_back(Sphere(float3(0, 0, -1020),1000,
    new Lambertian(float3(1.0,1.0,1.0)
    )));

            scene.push_back(Sphere(float3(5, -4, -12),3, 
    new Mirror()
    ));
                scene.push_back(Sphere(float3(-5, -4, -10),3,
    new Mirror()
    ));*/

    Window *win = new Window("YAPT", 640, 480);
    while (win->isRunning()){
        win->update();
        render(scene, win->getScreenPtr());
    }

}


