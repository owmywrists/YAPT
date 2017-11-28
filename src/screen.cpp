#include "screen.h"


Screen::Screen(int width, int height){
    m_width = width;
    m_height = height;
    sample = 1;
    m_pixelBuffer.resize(width*height);
    m_img.create(width, height, sf::Color::Black);
        m_tex.loadFromImage(m_img);
}

Screen::~Screen(){

}
void Screen::drawUI(){
    ImGui::Begin("HELLO");
    ImGui::Button("lel");
    ImGui::End();
}
sf::Sprite Screen::getDrawableView(){
    m_tex.loadFromImage(m_img);
    sf::Sprite sprite;
    sprite.setTexture(m_tex, true);
    return sprite;
}
void Screen::blit(){
    sample++;
}

float3 Screen::avg(float3 current_avg, float3 new_colour){
    return current_avg +((new_colour - current_avg)/float(sample));
}

sf::Color Screen::transform(float3 pixel){
    sf::Color colour =  sf::Color(sqrtf(std::min(pixel.x(), 1.0f))*255.0, 
                            sqrtf(std::min(pixel.y(), 1.0f))*255.0, 
                            sqrtf(std::min(pixel.z(), 1.0f))*255.0);
    return colour;
}

void Screen::setPixel(int x, int y, float3 colour){
    m_pixelBuffer[y + m_height*x] = avg(m_pixelBuffer[y + m_height*x], colour);
    float3 avg_col = m_pixelBuffer[y + m_height*x];
    m_img.setPixel(x,y,transform(avg_col));
}