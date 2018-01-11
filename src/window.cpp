#include "window.h"

Window::~Window()
{
	delete m_win;
	delete m_screen;
}

void Window::init()
{
    m_win = new sf::RenderWindow(sf::VideoMode(m_prop.width, m_prop.height), m_prop.title);
    ImGui::SFML::Init(*m_win);

    m_screen = new Screen(m_prop.width, m_prop.height);
    m_delta_clock.restart();
}

void Window::pollEvents()
{
    sf::Event event;

    while (m_win->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed)
        {
            m_win->close();
        }
    }
}

void Window::update()
{
    ImGui::SFML::Update(*m_win, m_delta_clock.restart());
    m_screen->drawUI();
    m_win->clear();
    m_drawableView = m_screen->getDrawableView();
    m_win->draw(m_drawableView);
    ImGui::SFML::Render(*m_win);
    m_win->display();
}
