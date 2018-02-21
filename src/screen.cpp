#include "screen.h"

void Screen::reset()
{
    sample = 1;
    should_reset = false;
}

sf::Sprite Screen::getDrawableView()
{
    m_tex.loadFromImage(m_img);
    sf::Sprite sprite;
    sprite.setTexture(m_tex, true);
    sprite.setTextureRect(sf::IntRect(0, height, width, -height)); //flip image vertically
    return sprite;
}

float3 Screen::avg(float3 current_avg, float3 new_colour)
{
    return current_avg + ((new_colour - current_avg) / float(sample));
}

void Screen::loadImage(float3* img)
{
    sf::Image temp;
    temp.create(width, height, sf::Color::Black);
    
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            float3 col = img[x + y * width];
            m_pixelBuffer[x + width * y] = avg(m_pixelBuffer[x + width * y], col);
            float3 avg_col = m_pixelBuffer[x + y * width];
            temp.setPixel(x, y, transform(avg_col));
        }
    }
    temp.flipVertically();
    m_img = temp;
}


void Screen::set_tile(int start_x, int start_y, int tile_size, float3* pixels)
{
    
    for (int x = 0; x < tile_size; x++)
    {
        for (int y = 0; y < tile_size; y++)
        {
            setPixel(start_x + x,start_y + y, pixels[ x + start_x + (y + start_y)*width]);
        }
        
    }
    
}

void Screen::begin_tile(int start_x, int start_y, int tile_size)
{
    
    for (int x = 0; x < tile_size; x++)
    {
        for (int y = 0; y < tile_size; y++)
        {
            if (x ==0 || x == tile_size-1) m_img.setPixel((start_x + x), start_y + y, transform(float3(0.0,0.6,1.0)));
            if (y ==0 || y == tile_size-1) m_img.setPixel((start_x + x), start_y + y,transform(float3(0.0, 0.6,1.0)));
        }
        
        
    }
}

sf::Color Screen::transform(float3 pixel)
{
    
    sf::Color colour = sf::Color(powf(std::min(pixel.x, 1.0f), 1./2.2)*255.0,
                                 powf(std::min(pixel.y, 1.0f), 1./2.2)*255.0,
                                 powf(std::min(pixel.z, 1.0f), 1./2.2)*255.0);
    return colour;
}

void Screen::setPixel(int x, int y, float3 colour)
{
    m_pixelBuffer[y + height * x] = avg(m_pixelBuffer[y + height * x], colour);
    float3 avg_col = m_pixelBuffer[y + height * x];
    m_img.setPixel(x, y, transform(avg_col));
}