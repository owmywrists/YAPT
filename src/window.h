#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "screen.h"
#include "sphere.h"
#include <string>

struct windowProperties{
    int width;
    int height;
    std::string title;
};


class Window {
public:
    Window(std::string title, int width, int height);
    ~Window();

    Screen* getScreenPtr(){return m_screen;}
    void update();
    bool isRunning();
private:
    windowProperties m_prop;
    SDL_Window *m_win;
    Screen *m_screen;
    SDL_Renderer *m_renderer;
private:
    void init();

};
