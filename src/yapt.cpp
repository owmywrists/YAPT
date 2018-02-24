#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <thread>
#include <stdio.h>
#include <SFML\Graphics.hpp>
#include "../lib/toml/cpptoml.h"
#include <string>
#include <memory>
#include <omp.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "v3.h"
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

int main(int argc, char** args)
{
    SceneSettings scene_settings;
    
    auto config = cpptoml::parse_file("../../scene/scene.toml");
    scene_settings.filename = config->get_qualified_as<std::string>("mesh.file").value_or("teapot.obj");
    scene_settings.texture = config->get_qualified_as<std::string>("mesh.texture").value_or("error.png");
    scene_settings.hdri = config->get_qualified_as<std::string>("scene.hdri").value_or("error.png");
    
    auto camera = config->get_table("camera");
    auto cam_pos = camera->get_array_of<double>("position");
    auto cam_look = camera->get_array_of<double>("lookat");
    auto cam_fov = camera->get_as<double>("fov");
    auto dimensions = camera->get_array_of<int64_t>("dimensions");
    auto lights = config->get_table("lights");
    
    
    Scene* scene = new Scene(scene_settings);
    
    Window *win = new Window("YAPT", 
                             (*dimensions)[0], 
                             (*dimensions)[1]);
    
    Camera *cam= new Camera((*dimensions)[0],
                            (*dimensions)[1], 
                            v3f(cam_pos), 
                            v3f(cam_look), 
                            v3f(0, 1.0, 0), 
                            0.0f, 
                            3.5f, 
                            *cam_fov);
    
    Engine engine(cam, win->screen, scene);
    engine.tile_size = *(camera->get_as<int64_t>("tile_size"));
    std::thread t(render_thread, &engine, win);
    sf::Clock c;
    c.restart();
    sf::Time time;
    while (win->sf_win->isOpen())
    {
        win->update();
        sf::Time time = c.getElapsedTime();
        win->poll_events();
    }
    t.join();
    return 0;
}
