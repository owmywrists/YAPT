#pragma once

struct Colour {
    int r;
    int g;
    int b;

    Colour(int x = 0, int y = 0, int z = 0):
        r(x),
        g(y),
        b(z){}
};