#pragma once
#include "../imgui/imgui.h"
#include "../imgui-sfml/imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "screen.h"
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
    sf::RenderWindow* getWindowPtr(){return m_win;}
    bool shouldReset(){return m_should_reset;}
    bool setState(bool state){m_should_reset=state;}
    void update();
    void pollEvents();
private:
    windowProperties m_prop;
    sf::RenderWindow *m_win;
    Screen *m_screen; 
    sf::Clock m_delta_clock;
    bool m_should_reset;
private:
    void init();

};
