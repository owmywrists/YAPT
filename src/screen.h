#include <SDL2/SDL.h>
#include <vector>
#pragma once
#include "colour.h"

class Screen{
public:
    Screen(int width, int height, SDL_Renderer *renderer);
    ~Screen();

    void blit(int x, int y, Colour colour);
    unsigned int getWidth(){return m_width;}
    unsigned int getHeight(){return m_height;}
private:
    std::vector<int> m_pixelBuffer;
    int m_width;
    int m_height;
    SDL_Renderer *m_renderer;
};