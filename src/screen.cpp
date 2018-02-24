#include "screen.h"

void Screen::reset()
{
    sample = 1;
    should_reset = should_save = false;
}

sf::Sprite Screen::get_drawable_view()
{
    m_tex.loadFromImage(m_img);
    sf::Sprite sprite;
    sprite.setTexture(m_tex, true);
    sprite.setTextureRect(sf::IntRect(0, height, width, -height)); //flip image vertically
    return sprite;
}

v3f Screen::avg(v3f current_avg, v3f new_colour)
{
    return current_avg + ((new_colour - current_avg) / float(sample));
}

void Screen::loadImage(v3f* img)
{
    
    sf::Image temp;
    temp.create(width, height, sf::Color::Black);
    
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            v3f col = img[x + y * width];
            m_pixelBuffer[x + width * y] = avg(m_pixelBuffer[x + width * y], col);
            v3f avg_col = m_pixelBuffer[x + y * width];
            temp.setPixel(x, y, transform(avg_col));
        }
    }
    temp.flipVertically();
    m_img = temp;
}

void Screen::save_frame(v3f* img, std::string filename)
{
    sf::Image temp;
    temp.create(width, height, sf::Color::Black);
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            temp.setPixel(x,y,transform(m_pixelBuffer[y+x*width]));
        }
    }
    temp.flipVertically();
    temp.saveToFile(filename+".png");
    should_save = false;
}
void Screen::set_tile(int start_x, int start_y, int tile_size, v3f* pixels)
{
    for (int x = 0; x < tile_size; x++)
        for (int y = 0; y < tile_size; y++)
        setPixel(start_x + x,start_y + y, pixels[ x + start_x + (y + start_y)*width]);
}

void Screen::begin_tile(int start_x, int start_y, int tile_size)
{
    
    for (int x = 0; x < tile_size; x++)
    {
        for (int y = 0; y < tile_size; y++)
        {
            if (x ==0 || x == tile_size-1) m_img.setPixel((start_x + x), start_y + y, transform(v3f(0.0,0.6,1.0)));
            if (y ==0 || y == tile_size-1) m_img.setPixel((start_x + x), start_y + y,transform(v3f(0.0, 0.6,1.0)));
        }
        
        
    }
}

sf::Color Screen::transform(v3f pixel)
{
    sf::Color colour = sf::Color(powf(std::min(pixel.x, 1.0f), 1./2.2)*255.0,
                                 powf(std::min(pixel.y, 1.0f), 1./2.2)*255.0,
                                 powf(std::min(pixel.z, 1.0f), 1./2.2)*255.0);
    return colour;
}

void Screen::setPixel(int x, int y, v3f colour)
{
    m_pixelBuffer[y + height * x] = avg(m_pixelBuffer[y + height * x], colour);
    v3f avg_col = m_pixelBuffer[y + height * x];
    m_img.setPixel(x, y, transform(avg_col));
}