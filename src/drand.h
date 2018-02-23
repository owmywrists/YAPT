#pragma once
#include <random>
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> generator(0,1);

inline double drand48() {
    return generator(gen);
}

