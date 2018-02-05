#include <iostream>
#include "window.h"
#include "float3.h"
#include "material.h"
#include "obj_parser.h"
#include "engine.h"
#include "drand.h"

#include <thread>
#include <atomic>
#include <stdio.h>

void render_thread(Engine *engine, Window *win)
{
    while (win->getWindowPtr()->isOpen())
    {
        engine->render();
    }
}

int main(int argc, char* argv[])
{
    Window *win = new Window("YAPT", 1280, 720);
    Camera cam(1280, 720, float3(0, 0, 6.7), float3(0, 0, -1.0), float3(0, 1.0, 0), 0.0f, 9.f, 50.0f);
    Engine engine(cam, win->getScreenPtr());
    
    std::thread t(render_thread, &engine, win);
    
    while (win->getWindowPtr()->isOpen())
    {
        win->update();
        win->pollEvents();
    }
    t.join();
    ImGui::SFML::Shutdown();
    return 0;
}
