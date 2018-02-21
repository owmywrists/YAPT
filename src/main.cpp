#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <thread>
#include <stdio.h>
#include <SFML\Graphics.hpp>
#include "../lib/imgui/imgui.h"
#include "../imgui-sfml/imgui-SFML.h"
#include <string>
#include <memory>
#include <omp.h>
#include <stdlib.h>
#include "float3.h"
#include "drand.h"
#include "ray.h"
#include "camera.cpp"
#include "screen.cpp"
#include "aabb.h"
#include "material.cpp"
#include "light.h"
#include "surface.cpp"
#include "kd_tree.cpp"
#include "obj_parser.cpp"
#include "mesh.cpp"
#include "scene.h"
#include "window.cpp"
#include "engine.cpp"


void render_thread(Engine *engine, Window *win)
{
    while (win->getWindowPtr()->isOpen())
    {
        engine->render();
    }
}

int main(int argc, char* argv[])
{
    Scene* scene = new Scene();
    Window *win = new Window("YAPT", 1280, 720);
    Camera cam(1280, 720, float3(6.7, 10.0, 6.7), float3(0, 0, -1.0), float3(0, 1.0, 0), 1.0f, 6.f, 50.0f);
    Engine engine(cam, win->getScreenPtr(), scene);
    
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
