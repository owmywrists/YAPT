#include "obj_parser.h"

void Obj::parse_faces()
{
	string line;
	string word;
	m_obj.open(m_filename);
	while (std::getline(m_obj, line))
	{

		if (line.substr(0, 2) == "v ")
		{
			std::istringstream ss(line.substr(2));
			float3 v;
			ss >> v;
			m_vertices.push_back(v);
		}
		else if (line.substr(0, 2) == "f ")
		{
			std::istringstream ss(line.substr(2));
			float3 f;
			ss >> f;
			m_faces.push_back(f);
		}
	}
	m_obj.close();
}

Obj::Obj(string filename)
{
	m_filename = filename;

	parse_faces();
}

float3 Obj::face(int i)
{
	return m_faces[i];
}

vector<Surface *> Obj::getScene()
{
	vector<Surface *> m_scene;
	std::vector<std::shared_ptr<Material>> m;
	m.push_back(MaterialFactory::createMaterial(MaterialFactory::Diffuse, float3(1.0, 0.0, 0.0)));
	m.push_back(MaterialFactory::createMaterial(MaterialFactory::Diffuse, float3(1.0, 1.0, 1.0)));
	for (int i = 0; i < m_faces.size(); i++)
	{
		float3 f = face(i);
		float3 v0 = m_vertices[f.x() - 1];
		float3 v1 = m_vertices[f.y() - 1];
		float3 v2 = m_vertices[f.z() - 1];
		m_scene.push_back(new Triangle(v0, v1, v2,
									   m,
									   float3()));
	}
	return m_scene;
}