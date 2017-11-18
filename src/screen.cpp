#include "screen.h"


Screen::Screen(int width, int height, SDL_Renderer *renderer){
    m_renderer = renderer;
    m_width = width;
    m_height = height;
}

Screen::~Screen(){

}

void Screen::blit(int x, int y, Colour colour){
    SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, 255);
    
    SDL_RenderDrawPoint(m_renderer, x,y);

}
