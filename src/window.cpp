#include "window.h"


Window::Window(std::string title, int width, int height){
    m_prop.title = title;
    m_prop.width = width;
    m_prop.height = height;
    m_should_reset = false;
    init();

}

Window::~Window(){

}

void Window::init(){
    m_win = new sf::RenderWindow(sf::VideoMode(m_prop.width, m_prop.height), m_prop.title);
    ImGui::SFML::Init(*m_win);

    m_screen = new Screen(m_prop.width, m_prop.height);
    m_delta_clock.restart();
}

void Window::pollEvents(){
    sf::Event event;

    while(m_win->pollEvent(event)){
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed){
            m_win->close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            std::cout << "YOU PRESSED ME" << std::endl;
            std::cout << event.mouseButton.x << std::endl;
            m_should_reset = true;
        }
            
    }

}


void Window::update(){
    ImGui::SFML::Update(*m_win, m_delta_clock.restart());
    m_screen->drawUI();
    m_win->clear();
    m_win->draw(m_screen->getDrawableView());
    ImGui::SFML::Render(*m_win);
    m_win->display();
}
