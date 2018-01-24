#pragma once
#include "surface.h"
#include "obj_parser.h"
#include "kd_tree.h"

class Mesh {
public:
	Mesh() {}
	void load(std::string filename)
	{
		std::vector<float3> face_ptr;
		load_obj(filename, vertices, face_ptr);
		
		std::shared_ptr<Material> m;

		auto m1 = std::make_shared<Lambertian>(float3(0.7));
		auto m2 = std::make_shared<Mirror>(float3(0.9), 0.1);

		m = std::make_shared<Mix>(m1, m2, 1.9f);

		for (int i = 0; i < face_ptr.size(); i++)
		{
			float3 f = face_ptr[i];
			tris.push_back(Triangle(&vertices[f.x - 1], &vertices[f.y - 1], &vertices[f.z - 1], m1));
			faces.push_back(new Triangle(&vertices[f.x - 1], &vertices[f.y - 1], &vertices[f.z - 1], m));
		}
	}
	void calculate_normals() 
	{
#pragma omp parallel for schedule(dynamic, 1)
		for (int v = 0; v < vertices.size(); v++) 
		{ // for(auto v: vertices) copies data, not what i want
			float3 normal = float3();
			for (int i = 0; i < tris.size(); i++) 
			{
				if (tris[i].contains_vertex(&vertices[v])) {
					normal = normal + tris[i].getFaceNormal();
				}
			}
			vertices[v].normal = unit(normal);
		}
		root = KDNode().build(faces, 0);
	}
	bool intersect(Ray &ray, HitInfo &hit) 
	{
		return root->intersect(root, ray, hit);
	}
	int size()const{ return faces.size(); }

	KDNode *root;
private:
	std::vector<Vertex> vertices;
	std::vector<Surface*> faces;
	std::vector<Triangle> tris; 

};