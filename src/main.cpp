#include <iostream>
#include "window.h"
#include "float3.h"
#include "material.h"
#include "hitlist.h"
#include "obj_parser.h"
#include "engine.h"
#include <thread>
#include <atomic>


void render_thread(Engine *engine, Window *win){
    while(win->getWindowPtr()->isOpen()){
        engine->render(win->getScreenPtr());
        std::cout <<"IM RENDERING" << std::endl;
    }
}

int main(){
    Window *win = new Window("YAPT", 640, 480);
    Engine engine(Camera(640, 480, 90.0));
    engine.loadObjAsScene("../src/monkey.obj");
    std::thread t(render_thread, &engine, win);


    while (win->getWindowPtr()->isOpen()){
        win->update();
        win->pollEvents();

    }
    t.join();
}


