#include "screen.h"


Screen::Screen(int width, int height){
    m_width = width;
    m_height = height;
}

Screen::~Screen(){

}

void Screen::blit(SDL_Renderer *renderer, int x, int y, Colour colour){
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);

    SDL_RenderDrawPoint(renderer, x,y);

}
