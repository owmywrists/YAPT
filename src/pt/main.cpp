#include <iostream>
#include "../app/window/window.h"
#include "../utility/float3.h"

int main(){
    printf("Hello");

    Window *win = new Window("YAPT", 500, 500);
    float3 a(2.0, -3.0, 1.0);
    float3 b(0.0, 4.0, -1.0);
    while (win->isRunning()){
        win->update();
    }
    std::cout << a << std::endl;
    printf("%f", a.dot(b));

}