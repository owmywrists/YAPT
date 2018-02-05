#pragma once
#include "surface.h"
#include "obj_parser.h"
#include <SFML/Graphics.hpp>
#include "kd_tree.h"

class Mesh {
    public:
    Mesh() {}
    
    void load(std::string filename, std::string atlas_name)
    {
        std::vector<float3> face_ptr, normal_ptr, uv_ptr;
        vertices.clear(); faces.clear(); tris.clear(); normals.clear();
        
        uvs.clear();
        load_obj(filename, 
                 vertices, face_ptr,
                 normals,  normal_ptr, 
                 uvs, uv_ptr);
        std::shared_ptr<Material> m;
        texture.loadFromFile(atlas_name);
        auto m1 = std::make_shared<Lambertian>(texture);
        auto m2 = std::make_shared<Mirror>(float3(0.9), 0.1);
        auto m3 = std::make_shared<Glass>(float3(0.9), 0.5);
        auto m4 = std::make_shared<Emissive>(float3(1.0));
        m = std::make_shared
            <Mix>(m1, m2, 1.9f);
        
        for (int i = 0; i < face_ptr.size(); i++)
        {
            float3 f = face_ptr[i];
            
            float3 n = normal_ptr[i];
            float3 uv = uv_ptr[i];
            
            tris.push_back(Triangle(&vertices[f.x - 1].pos,
                                    &vertices[f.y - 1].pos,
                                    &vertices[f.z - 1].pos,
                                    
                                    &normals[n.x-1],
                                    &normals[n.y-1],
                                    &normals[n.z-1],
                                    
                                    &uvs[uv.x-1],
                                    &uvs[uv.y-1],
                                    &uvs[uv.z-1],
                                    m1));
            
            faces.push_back(new 
                            Triangle(&vertices[f.x - 1].pos,
                                     &vertices[f.y - 1].pos,
                                     &vertices[f.z - 1].pos,
                                     
                                     &normals[n.x-1],
                                     &normals[n.y-1],
                                     &normals[n.z-1],
                                     
                                     &uvs[uv.x-1],
                                     &uvs[uv.y-1],
                                     &uvs[uv.z-1],
                                     m));
        }
        printf("Finished making mesh\n");
        root = KDNode().build(faces, 0);
        printf("Finished building kdtree");
        
    }
    void calculate_normals() 
    {
        
#pragma omp parallel for
        for (int v = 0; v < vertices.size(); v++) 
        {
            float3 normal = float3();
            for (int i = 0; i < tris.size(); i++) 
            {
                //if (tris[i].contains_vertex(&vertices[v])) {
                //normal = normal + tris[i].getNormal();
                //}
            }
            //vertices[v].normal = unit(normal);
        }
        
    }
    
    bool intersect(Ray &ray, HitInfo &hit) 
    {
        return root->intersect(root, ray, hit);
    }
    bool light_intersect(Ray &ray, HitInfo &hit)
    {
        return root->closestIntersection(ray, hit, faces);
    }
    
    int size()const{ return faces.size(); }
    
    KDNode *root;
    std::vector<Surface*> faces;
    sf::Image texture;
    private:
    std::vector<Vertex> vertices;
    
    std::vector<Triangle> tris;
    std::vector<float3> normals;
    std::vector<UV> uvs;
    
};