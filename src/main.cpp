#include <iostream>
#include "window.h"
#include "float3.h"
#include "renderer.h"
#include "hitlist.h"

int main(){
    std::vector<Sphere> scene;
    scene.push_back(Sphere(float3(0.0, 0.0, -1.0), 0.5, float3(0,0.6,0)));
    scene.push_back(Sphere(float3(0.0, 100.5, -1.0),100, float3(0.6,0,0)));
    Window *win = new Window("YAPT", 500, 500);
    while (win->isRunning()){
        win->update();
        render(scene, win->getScreenPtr());
    }

}

