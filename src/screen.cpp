#include "screen.h"

Screen::~Screen()
{
    m_img.~Image();
    m_tex.~Texture();
    m_pixelBuffer.~vector();
}
void Screen::drawUI()
{
    ImGui::StyleColorsDark();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save"))
            {
                m_win_states.save = true;
            }
            if (ImGui::MenuItem("Reset"))
            {
                should_reset = true;
            }

            ImGui::EndMenu();
        }
		if (ImGui::BeginMenu("Windows"))
		{
			if (ImGui::MenuItem("Colour")) m_win_states.colour = !m_win_states.colour;

			ImGui::EndMenu();
		}


        if (m_win_states.save)
        {
            ImGui::Begin("Save settings");
            ImGui::InputText("filename", m_img_name, sizeof(m_img_name), ImGuiInputTextFlags_EnterReturnsTrue);
            if (ImGui::Button("Save to file"))
            {
                m_img.saveToFile(m_img_name);
                m_win_states.save = false;
            }
            ImGui::End();
        }

		if (m_win_states.colour)
		{
			ImGui::Begin("Colour");
			if (ImGui::ColorPicker3("Test", m_color))
			{
				should_reset = true;
			}
			ImGui::End();
		}
    }
    ImGui::EndMainMenuBar();
}

void Screen::reset()
{
    std::fill(m_pixelBuffer.begin(), m_pixelBuffer.end(), float3(0.0, 0.0, 0.0));
    sample = 1;
    should_reset = false;
}

sf::Sprite Screen::getDrawableView()
{
    m_tex.loadFromImage(m_img);
    sf::Sprite sprite;
    sprite.setTexture(m_tex, true);
    return sprite;
}


float3 Screen::avg(float3 current_avg, float3 new_colour)
{
    return current_avg + ((new_colour - current_avg) / float(sample));
}

void Screen::loadImage(std::vector<float3> img)
{
    sf::Image temp;
    temp.create(m_width, m_height, sf::Color::Black);
    for (int x = 0; x < m_width; x++)
    {
        for (int y = 0; y < m_height; y++)
        {
            float3 col = img[x + y * m_width];
            m_pixelBuffer[x + m_width * y] = avg(m_pixelBuffer[x + m_width * y], col);
            float3 avg_col = m_pixelBuffer[x + y * m_width];
            temp.setPixel(x, y, transform(avg_col));
        }
    }
    temp.flipVertically();
    m_img = temp;
}

sf::Color Screen::transform(float3 pixel)
{

    sf::Color colour = sf::Color(std::min(pixel.x, 1.0f) * 255.0,
                                 std::min(pixel.y, 1.0f) * 255.0,
                                 std::min(pixel.z, 1.0f) * 255.0);
    return colour;
}

void Screen::setPixel(int x, int y, float3 colour)
{
    m_pixelBuffer[y + m_height * x] = avg(m_pixelBuffer[y + m_height * x], colour);
    float3 avg_col = m_pixelBuffer[y + m_height * x];
    m_img.setPixel(x, y, transform(avg_col));
}