#include <string>
#include "obj_parser.h"
#include "surface.h"
#include "hitlist.h"
#include "camera.h"
#include "screen.h"
#include "kd_tree.h"
#include "drand.h"
#include <omp.h>

class Engine
{
  public:
	  Engine(Camera cam, Screen *screen) : m_cam(cam), m_screen(screen) { hdri.loadFromFile("../hdri_indoor.jpg"); }
	~Engine();
    void loadObjAsScene(std::string filename);
    void render();
    void restart();

  private:
    std::vector<Surface*> m_data;
    KDNode *node;
    Camera m_cam;
    float3 trace(Ray &ray,HitInfo &hit, int depth);
    void loadBuffer(std::vector<float3> image);
    Screen *m_screen;
	sf::Image hdri;
};
