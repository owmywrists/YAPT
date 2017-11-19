#include "screen.h"


Screen::Screen(int width, int height, SDL_Renderer *renderer){
    m_renderer = renderer;
    m_width = width;
    m_height = height;
    m_pixelBuffer.reserve(width*height);
}

Screen::~Screen(){

}

void Screen::blit(){
    for (int x = 0; x < m_width; x++){
        for (int y = 0; y < m_height; y++){
            float3 col = m_pixelBuffer[x + y*m_width];
            SDL_SetRenderDrawColor(m_renderer, col.x(), col.y(), col.z(), 255);
            SDL_RenderDrawPoint(m_renderer, x,y);
        }
    }


}

void Screen::setPixel(int x, int y, float3 colour){
    m_pixelBuffer[x + y*m_width] = (m_pixelBuffer[x + y*m_width] + colour)/2.0;
}