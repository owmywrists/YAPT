#include <iostream>
#include "window.h"
#include "float3.h"
#include "renderer.h"
#include "material.h"
#include "hitlist.h"
#include "obj_parser.h"

int main(){
    std::vector<Surface*> scene;
    Obj m("../src/cornell4.obj");

    scene = m.getScene();;

        scene.push_back(new Sphere(float3(0.0, 0.5, -1.0),0.3,
    MaterialFactory::Light, float3(1.9,1.9,1.9)
    ));

    Hitlist data(scene);



    Window *win = new Window("YAPT", 640, 480);
    while (win->isRunning()){
        win->update();
        render(data, win->getScreenPtr());
    }

}


