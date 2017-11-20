#include "screen.h"


Screen::Screen(int width, int height, SDL_Renderer *renderer){
    m_renderer = renderer;
    m_width = width;
    m_height = height;
    sample = 1;
    m_pixelBuffer.reserve(width*height);
    std::fill(m_pixelBuffer.begin(), m_pixelBuffer.end(), float3(0.0,0.0,0.0));
}

Screen::~Screen(){

}

void Screen::blit(){
    sample++;
    printf("SAMPLE: %d\n", sample);
    for (int x = 0; x < m_width; x++){
        for (int y = 0; y < m_height; y++){
            float3 col = m_pixelBuffer[y + m_height*x];
            SDL_SetRenderDrawColor(m_renderer, std::min(sqrtf(col.x())*255.0, 255.0),std::min(sqrtf(col.y())*255.0, 255.0),std::min(sqrtf(col.z())*255.0, 255.0), 255);
            SDL_RenderDrawPoint(m_renderer, x,(m_height - y));
        }
    }


}

float3 Screen::avg(float3 current_avg, float3 new_colour){
    return current_avg +((new_colour - current_avg)/float(sample));
}

void Screen::setPixel(int x, int y, float3 colour){
    m_pixelBuffer[y + m_height*x] = avg(m_pixelBuffer[y + m_height*x], colour);
}