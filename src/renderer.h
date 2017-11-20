#include "screen.h"
#include "hitlist.h"
#include <SDL2/SDL.h>
#include "camera.h"

void render(Hitlist scene, Screen *screen);
float3 trace(Ray &ray, Hitlist scene,HitInfo &hit, int depth);