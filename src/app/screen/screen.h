#include <SDL2/SDL.h>
#include <vector>
#include "../../pt/colour.h"

class Screen{
public:
    Screen(int width, int height);
    ~Screen();

    void blit(SDL_Renderer *renderer, int x, int y, Colour colour);
private:
    std::vector<int> m_pixelBuffer;
    int m_width;
    int m_height;
};