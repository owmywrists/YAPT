#pragma once
#include <string>
#include "obj_parser.h"
#include "surface.h"
#include "hitlist.h"
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
		  hdri.loadFromFile("../res/hdris/road.jpg");
		  clock.restart();
		  mesh.load("../res/objs/dragon_ground.obj");
		  mesh.calculate_normals();

	  }
	~Engine();
    void render();
    void restart();

  private:
	Mesh mesh;
    Camera m_cam;
	sf::Clock clock;
    float3 trace(Ray &ray,HitInfo &hit, int depth);
    void loadBuffer(std::vector<float3> image);
    Screen *m_screen;
	sf::Image hdri;
};
