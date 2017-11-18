#include <iostream>
#include "window.h"
#include "float3.h"
#include "renderer.h"
#include "scene.h"

int main(){
    printf("Hello");
    Window *win = new Window("YAPT", 500, 500);

    while (win->isRunning()){
        win->update();
        render(win->getScreenPtr());
    }

}