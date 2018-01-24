#include "obj_parser.h"

void load_obj(string filename, vector<Vertex> &vertices, vector<float3> &faces)
{
	std::ifstream obj;
	string line;
	string word;
	obj.open(filename);
	vector<float3> temp_f;
	vector<Vertex> temp_v;
	while (std::getline(obj, line))
	{

		if (line.substr(0, 2) == "v ")
		{
			std::istringstream ss(line.substr(2));
			float3 p;
			Vertex v;
			ss >> p;
			v.pos = p;
			v.normal = float3();
			temp_v.push_back(v);
		}
		else if (line.substr(0, 2) == "f ")
		{
			std::istringstream ss(line.substr(2));
			float3 f;
            v3<std::string> string;
			ss >> f;
			temp_f.push_back(f);
		}
	}
	vertices = temp_v;
	faces = temp_f;
	obj.close();
}
