#pragma once
#include "../imgui/imgui.h"
#include "../imgui-sfml/imgui-SFML.h"

#include <SDL2/SDL.h>
#include <vector>
#include "float3.h"
#include <SFML/Graphics.hpp>

class Screen{
public:
    Screen(int width, int height);
    ~Screen();

    void blit();
    void setPixel(int x, int y, float3 colour);
    unsigned int getWidth(){return m_width;}
    unsigned int getHeight(){return m_height;}
    void drawUI();
private:
    float3 avg(float3 current_avg, float3 new_colour);
    std::vector<float3> m_pixelBuffer;
    std::vector<sf::Uint8> m_sf_pixelBuffer;
    int m_width;
    int m_height;
    int sample;
};