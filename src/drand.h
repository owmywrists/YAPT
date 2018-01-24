#pragma once
#include <random>

inline double drand48() {
	return (rand() / (RAND_MAX + 1.0));
	//needed to replace drand which is not available on windows
}

