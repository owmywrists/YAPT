#include "window.h"


Window::Window(std::string title, int width, int height){
    m_prop.title = title;
    m_prop.width = width;
    m_prop.height = height;

    init();

}

Window::~Window(){

}

void Window::init(){

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL failed to initialise");
    }

    m_win = SDL_CreateWindow(m_prop.title.c_str(), SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,m_prop.width, m_prop.height, 0);

    if (m_win == NULL){
        printf("SDL failed to create window");
    }

    m_screen = new Screen(m_prop.width, m_prop.height);

    m_renderer = SDL_CreateRenderer(m_win, -1, SDL_RENDERER_ACCELERATED);

}

bool Window::isRunning(){
    SDL_Event event;

    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT)
            return false;
    }

    return true;

}


void Window::update(){
    for (int x = 0; x < m_prop.width; x++)
        for(int y = 0; y < m_prop.height; y++){
            Colour colour = Colour((x+SDL_GetTicks()/10)%255,(y+SDL_GetTicks()/5)%255,255);
            m_screen->blit(m_renderer, x, y, colour);
        }
    SDL_RenderPresent(m_renderer);
}
