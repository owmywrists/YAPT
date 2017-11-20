#include <SDL2/SDL.h>
#include <vector>
#pragma once
#include "colour.h"
#include "float3.h"

class Screen{
public:
    Screen(int width, int height, SDL_Renderer *renderer);
    ~Screen();

    void blit();
    void setPixel(int x, int y, float3 colour);
    unsigned int getWidth(){return m_width;}
    unsigned int getHeight(){return m_height;}
private:
    float3 avg(float3 current_avg, float3 new_colour);
    std::vector<float3> m_pixelBuffer;
    int m_width;
    int m_height;
    int sample;
    SDL_Renderer *m_renderer;
};