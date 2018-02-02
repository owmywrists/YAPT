#pragma once
#include "../imgui/imgui.h"
#include "../imgui-sfml/imgui-SFML.h"
#include <vector>
#include "float3.h"
#include <SFML/Graphics.hpp>
#include <mutex>
#include <exception>

class Screen
{
    public:
    Screen(int width, int height) : m_width(width), m_height(height),
    sample(1)
    {
        m_pixelBuffer.resize(width * height);
        m_img.create(width, height, sf::Color::Black);
        m_tex.loadFromImage(m_img);
        should_reset = false;
        m_win_states.save = false;
        m_win_states.hdri = false;
        m_win_states.open = false;
        m_win_states.colour = false;
        debug_text.move(sf::Vector2f(20, height - 40));
        debug_text.scale(sf::Vector2f(0.8,0.8));
        
        Font.loadFromFile("../../res/fonts/helvetica.ttf");
        
    };
    ~Screen();
    void setPixel(int x, int y, float3 colour);
    unsigned int getWidth() { return m_width; }
    unsigned int getHeight() { return m_height; }
    float *getColour() { return m_color; }
    bool getState() { return should_reset; }
    sf::Sprite getDrawableView();
    void drawUI();
    void loadImage(std::vector<float3> img);
    void reset();
    sf::Text debug_text;
    sf::Font Font;
    int sample;
    
    char obj_to_open[64];
    char hdri_to_load[64];
    char texture_atlas[64];
    
    private:
    float3 avg(float3 current_avg, float3 new_colour);
    sf::Color transform(float3 pixel);
    struct Window_states
    {
        bool save;
        bool colour;
        bool open;
        bool hdri;
    };
    sf::Clock clock;
    std::vector<float3> m_pixelBuffer;
    sf::Image m_img;
    char m_img_name[32];
    sf::Texture m_tex;
    Window_states m_win_states;
    bool should_reset;
    float m_color[3] = {1.0f, 1.0f, 1.0f};
    int m_width;
    int m_height;
};
