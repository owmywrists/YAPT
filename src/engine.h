#include <string>
#include "obj_parser.h"
#include "surface.h"
#include "hitlist.h"
#include "camera.h"
#include "screen.h"
#include <mutex>
#include <omp.h>
#include <condition_variable>

class Engine
{
  public:
    Engine(Camera cam, Screen *screen) : m_cam(cam), m_screen(screen) {}
    void loadObjAsScene(std::string filename);
    void render();
    void restart();

  private:
    std::vector<Surface *> m_data;
    Camera m_cam;
    static float3 trace(Ray &ray, Hitlist scene, HitInfo &hit, int depth);
    void loadBuffer(std::vector<float3> image);
    Screen *m_screen;
};