#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <thread>
#include <stdio.h>
#include <SFML\Graphics.hpp>
#include "../lib/imgui/imgui.h"
#include "../imgui-sfml/imgui-SFML.h"
#include "../lib/toml/cpptoml.h"
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
    auto config = cpptoml::parse_file("../../scene/scene.toml");
    auto file = config->get_qualified_as<std::string>("mesh.file");
    
    auto camera = config->get_table("camera");
    auto cam_pos = camera->get_array_of<double>("position");
    auto cam_look = camera->get_array_of<double>("lookat");
    auto cam_fov = camera->get_as<double>("fov");
    auto dimensions = camera->get_array_of<int64_t>("dimensions");
    auto lights = config->get_table("lights");
    
    
    Scene* scene = new Scene(file.value_or("mountain.obj"));
    Window *win = new Window("YAPT", (*dimensions)[0], (*dimensions)[1]);
    Camera *cam= new Camera((*dimensions)[0],(*dimensions)[1], float3(cam_pos), float3(cam_look), float3(0, 1.0, 0), 0.0f, 3.5f, *cam_fov);
    Engine engine(cam, win->getScreenPtr(), scene);
    engine.tile_size = *(camera->get_as<int64_t>("tile_size"));
    std::thread t(render_thread, &engine, win);
    sf::Clock c;
    c.restart();
    sf::Time time;
    while (win->sf_win->isOpen())
    {
        win->update();
        sf::Time time = c.getElapsedTime();
        win->pollEvents();
    }
    t.join();
    ImGui::SFML::Shutdown();
    return 0;
}
