#include "obj_parser.h"

void load_obj(string filename, vector<float3> &vertices, vector<float3> &faces)
{
	std::ifstream obj;
	string line;
	string word;
	obj.open(filename);
	vector<float3> temp_v, temp_f;
	while (std::getline(obj, line))
	{

		if (line.substr(0, 2) == "v ")
		{
			std::istringstream ss(line.substr(2));
			float3 v;
			ss >> v;
			temp_v.push_back(v);
		}
		else if (line.substr(0, 2) == "f ")
		{
			std::istringstream ss(line.substr(2));
			float3 f;
			ss >> f;
			temp_f.push_back(f);
		}
	}
	vertices = temp_v;
	faces = temp_f;
	obj.close();
}