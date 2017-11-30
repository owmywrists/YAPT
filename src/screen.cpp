#include "screen.h"

Screen::~Screen(){
    m_img.~Image();
    m_tex.~Texture();
    m_mtx.~mutex();
    m_pixelBuffer.~vector();
}
void Screen::drawUI(){
    ImGui::StyleColorsDark();
    ImGui::Begin("HELLO");
    if(ImGui::ColorPicker3("Test", m_color)){
        should_reset = true;
    }
    if(ImGui::BeginMainMenuBar()){
            if(ImGui::BeginMenu("File")){
                if(ImGui::MenuItem("Save")){
                    m_win_states.save = true;
                }
                if(ImGui::MenuItem("Reset")){
                    should_reset = true;
                }  

                ImGui::EndMenu();
            }
            if(m_win_states.save){
                ImGui::Begin("Save settings");
                ImGui::InputText("filename", m_img_name, sizeof(m_img_name), ImGuiInputTextFlags_EnterReturnsTrue);
                if(ImGui::Button("Save to file")){
                    std::lock_guard<std::mutex> lk(m_mtx); //reserves screen while saving
                    m_img.saveToFile(m_img_name);
                    m_win_states.save = false;
                }
                ImGui::End();
            }
        }
        ImGui::EndMainMenuBar();
    ImGui::End();
}

void Screen::reset(){
    std::fill(m_pixelBuffer.begin(), m_pixelBuffer.end(), float3(0.0,0.0,0.0));
    sample = 1;
    should_reset = false;
}

sf::Sprite Screen::getDrawableView(){
    m_tex.loadFromImage(m_img);
    sf::Sprite sprite;
    sprite.setTexture(m_tex, true);
    return sprite;
}



void Screen::blit(){
    sample++;
    std::cout << sample << std::endl;
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
    std::lock_guard<std::mutex> lk(m_mtx);
    m_pixelBuffer[y + m_height*x] = avg(m_pixelBuffer[y + m_height*x], colour);
    float3 avg_col = m_pixelBuffer[y + m_height*x];
    m_img.setPixel(x,y,transform(avg_col));
}