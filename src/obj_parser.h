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



class Obj {
public:
	Obj(string filename);
	vector<Surface*> getScene();
private:
	vector<float3> m_faces;
	vector<float3> m_vertices;
	vector<float3> m_normals;
	vector<float> m_normalIndices;
	string m_filename;
	std::ifstream m_obj;
private:
	void parse_faces();
	float3 face(int i);
};