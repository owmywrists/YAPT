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
		printf("%d\n", face_ptr.size());

		auto m1 = std::make_shared<Lambertian>(float3(0.2, 0.3, 1.0));
		auto m2 = std::make_shared<Mirror>(float3(1.0, 1.0, 1.0), 0.0);

		m = std::make_shared<Mix>(m1, m2, 1.9f);

		for (int i = 0; i < face_ptr.size(); i++)
		{
			float3 f = face_ptr[i];
			faces.push_back(new Triangle(vertices[f.x - 1], vertices[f.y - 1], vertices[f.z - 1], m));
		}
		//std::cout << faces[0]->getNormal(float3()) << std::endl;
		
		printf("%d", faces.size());
		root = KDNode().build(faces, 0);
	}

	bool intersect(Ray &ray, HitInfo &hit) 
	{
		return root->intersect(root, ray, hit);
	}
	int size()const{ return faces.size(); }

	KDNode *root;
private:
	std::vector<float3> vertices;
	std::vector<Surface*> faces;

};