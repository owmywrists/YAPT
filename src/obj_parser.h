#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "surface.h"
#include "float3.h"

using std::string;
using std::vector;


void load_obj(string filename, vector<float3> &vertices, vector<float3> &faces);

