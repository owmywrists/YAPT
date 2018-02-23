#include "window.h"

Window::~Window()
{
    delete sf_win;
    delete screen;
}

void Window::init()
{
    sf_win = new sf::RenderWindow(sf::VideoMode(m_prop.width, m_prop.height), m_prop.title);
    sf::Image icon;
    icon.loadFromFile("../../res/icon/yapt.jpg");
    
    sf_win->setIcon(1024, 1024, icon.getPixelsPtr());
    
    screen = new Screen(m_prop.width, m_prop.height);
    m_delta_clock.restart();
}

void Window::poll_events()
{
    sf::Event event;
    
    while (sf_win->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            sf_win->close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            screen->should_save = true;
        }
    }
}

void Window::update()
{
    sf_win->clear();
    m_drawable_view = screen->get_drawable_view();
    sf_win->draw(m_drawable_view);
    sf_win->display();
}
