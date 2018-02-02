#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "surface.h"
#include "float3.h"
#include <algorithm>

using std::string;
using std::vector;


void load_obj(string filename, 
              vector<Vertex> &vertices, vector<float3> &vertex_ptr, vector<float3> &normals,  vector<float3> &normal_ptr,
              vector<UV> &uvs,      vector<float3> &uv_ptr);