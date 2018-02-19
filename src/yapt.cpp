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
    while (win->sf_win->isOpen())
    {
        engine->render();
    }
}

int main(int argc, char* argv[])
{
    Scene* scene = new Scene();
    Window *win = new Window("YAPT", 900, 900);
    Camera *cam= new Camera(900, 900, float3(2.5, 2.7, 2.5), float3(-0.0, 0.8, -0.0), float3(0, 1.0, 0), 0.0f, 3.5f, 50.0f);
    Engine engine(cam, win->getScreenPtr(), scene);
    
    std::thread t(render_thread, &engine, win);
    sf::Clock c;
    c.restart();
    sf::Time time;
    while (win->sf_win->isOpen())
    {
        win->update();
        sf::Time time = c.getElapsedTime();
        //cam->origin = cam->origin + float3(sin(time.asSeconds()),0.0,0.0);
        //scene->lights[0]->update(float3(0.0f, time.asSeconds()*5.0,0.0));
        win->pollEvents();
    }
    t.join();
    ImGui::SFML::Shutdown();
    return 0;
}
