#include <iostream>
#include "window.h"
#include "float3.h"
#include "material.h"
#include "hitlist.h"
#include "obj_parser.h"
#include "engine.h"
#include <thread>


int main(){
    Window *win = new Window("YAPT", 640, 480);
    Engine engine(Camera(640, 480, 90.0));
    engine.loadObjAsScene("../src/monkey.obj");

    while (win->getWindowPtr()->isOpen()){
        win->update();
        win->pollEvents();
        //engine.render(win->getScreenPtr());
        
    }
}


