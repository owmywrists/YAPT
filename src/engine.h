#pragma once
#include <string>
#include "obj_parser.h"
#include "surface.h"
#include "camera.h"
#include "screen.h"
#include "kd_tree.h"
#include "drand.h"
#include <omp.h>
#include "mesh.h"

class Engine
{
    public:
    Engine(Camera cam, Screen *screen) : m_cam(cam), m_screen(screen) 
    { 
        hdri.loadFromFile("../../res/hdris/road.jpg");
        clock.restart();
        strcpy(m_screen->texture_atlas, "Hamburger.png");
        mesh.load("../../res/objs/Hamburger.obj", "../../res/tex/Hamburger.png");
        strcpy(m_screen->obj_to_open, "Hamburger.obj");
        strcpy(m_screen->hdri_to_load, "road.jpg");
        mesh.calculate_normals();
    }
    ~Engine();
    void render();
    void restart();
    Mesh mesh;
    
    private:
    Camera m_cam;
    sf::Clock clock;
    float3 trace(Ray &ray,HitInfo &hit, int depth);
    void loadBuffer(std::vector<float3> image);
    Screen *m_screen;
    sf::Image hdri;
};
