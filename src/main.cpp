#include <iostream>
#include "window.h"
#include "float3.h"
#include "material.h"
#include "hitlist.h"
#include "obj_parser.h"
#include "engine.h"
#include "drand.h"
#include <thread>
#include <atomic>

void render_thread(Engine *engine, Window *win)
{
    while (win->getWindowPtr()->isOpen())
    {
        engine->render();
    }
}

int main()
{
    Window *win = new Window("YAPT", 1280, 720);
	Camera cam(1280, 720, float3(0, 0, 3.0), float3(0, 0, -1.0), float3(0, 1.0, 0), 0.0f, 6.f, 90.0f);
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
