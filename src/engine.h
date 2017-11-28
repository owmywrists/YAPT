#include <string>
#include "obj_parser.h"
#include "surface.h"
#include "hitlist.h"
#include "camera.h"
#include "screen.h"
#include <mutex>

class Engine{
public:
    Engine(Camera cam): m_cam(cam){    m_rendering_state = false;}
    void loadObjAsScene(std::string filename);
    void render(Screen *screen);
    bool getState(){
        std::lock_guard<std::mutex> lk(m_mtx);
        return m_rendering_state;
        }
    void restart();

private:
    std::vector<Surface*> m_data;
    Camera m_cam;
    static float3 trace(Ray &ray, Hitlist scene, HitInfo &hit, int depth);
    bool m_rendering_state;
    std::mutex m_mtx;
};