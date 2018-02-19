#include "window.h"

Window::~Window()
{
    delete sf_win;
    delete m_screen;
}

void Window::init()
{
    sf_win = new sf::RenderWindow(sf::VideoMode(m_prop.width, m_prop.height), m_prop.title);
    ImGui::SFML::Init(*sf_win);
    sf::Image icon;
    icon.loadFromFile("../../res/icon/yapt.jpg");
    
    sf_win->setIcon(1024, 1024, icon.getPixelsPtr());
    
    m_screen = new Screen(m_prop.width, m_prop.height);
    m_delta_clock.restart();
}

void Window::pollEvents()
{
    sf::Event event;
    
    while (sf_win->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed)
        {
            sf_win->close();
        }
    }
}

void Window::update()
{
    ImGui::SFML::Update(*sf_win, m_delta_clock.restart());
    sf_win->clear();
    m_drawableView = m_screen->getDrawableView();
    sf_win->draw(m_drawableView);
    ImGui::SFML::Render(*sf_win);
    sf_win->display();
}
