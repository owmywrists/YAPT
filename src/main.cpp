#include <iostream>
#include "window.h"
#include "float3.h"
#include "renderer.h"
#include "material.h"
#include "hitlist.h"
#include "obj_parser.h"

int main(){
    std::vector<Surface*> scene;
    std::vector<Surface*> scene2;
    Obj m("../src/suzanne.obj");
    /*
        scene.push_back(new Sphere(float3(0.0, 4.99, -7.0), 3,
        MaterialFactory::Diffuse, float3(1.9,1.9,1.9)
    ));
    */
        scene.push_back(new Sphere(float3(0.0, -5, -1.0),5,
    MaterialFactory::Metal, float3(1.0,1.0,1.0)
    ));
            scene.push_back(new Triangle(float3(-2.0, 1.0, -5.0),float3(-5.0, 0.0, -5.0),
            float3(2.0, 3.0, -1.0), MaterialFactory::Diffuse, float3(0.4, 0.0, 0.9)
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
    scene2 = m.getScene();
    printf("%f\n", scene2[4]->getNormal(float3(0.0,0.0,0.0)).x());
    Hitlist data(m.getScene());

    Window *win = new Window("YAPT", 640, 480);
    while (win->isRunning()){
        win->update();
        render(data, win->getScreenPtr());
    }

}


