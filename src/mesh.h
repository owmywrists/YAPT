
class Mesh {
    public:
    Mesh() {}
    
    void load(std::string filename, std::string atlas_name)
    {
        std::vector<v3i> face_ptr, normal_ptr, uv_ptr;
        positions.clear(); faces.clear(); tris.clear(); normals.clear();
        
        uvs.clear();
        load_obj(filename, 
                 positions, face_ptr,
                 normals,  normal_ptr, 
                 uvs, uv_ptr);
        std::shared_ptr<Material> m;
        texture.loadFromFile(atlas_name);
        auto m1 = std::make_shared<Lambertian>(texture);
        auto m2 = std::make_shared<Mirror>(v3f(0.9), 0.1);
        auto m3 = std::make_shared<Glass>(v3f(0.9), 0.5);
        auto m4 = std::make_shared<Emissive>(v3f(1.2));
        m = std::make_shared
            <Mix>(m1, m2, 1.2f);
        
        for (int i = 0; i < face_ptr.size(); i++)
        {
            v3i f = face_ptr[i];
            
            v3i n = normal_ptr[i];
            v3i uv = uv_ptr[i];
            
            tris.push_back(Triangle(&positions[f.x - 1],
                                    &positions[f.y - 1],
                                    &positions[f.z - 1],
                                    
                                    &normals[n.x-1],
                                    &normals[n.y-1],
                                    &normals[n.z-1],
                                    
                                    &uvs[uv.x-1],
                                    &uvs[uv.y-1],
                                    &uvs[uv.z-1],
                                    m1));
            
            faces.push_back(new 
                            Triangle(&positions[f.x - 1],
                                     &positions[f.y - 1],
                                     &positions[f.z - 1],
                                     
                                     &normals[n.x-1],
                                     &normals[n.y-1],
                                     &normals[n.z-1],
                                     
                                     &uvs[uv.x-1],
                                     &uvs[uv.y-1],
                                     &uvs[uv.z-1],
                                     m1));
            
        }
        //faces.push_back(new Sphere(v3f(2.0, 3.0, 0.0), 0.5, m4));
        printf("Finished making mesh\n");
        
        
    }
    
    void generate_kdtree()
    {
        root = KDNode().build(faces,0);
        printf("Finished building kdtree");
    }
    void calculate_normals() 
    {
        
#pragma omp parallel for
        for (int v = 0; v < positions.size(); v++) 
        {
            v3f normal = v3f();
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
    std::vector<v3f> positions;
    
    std::vector<Triangle> tris;
    std::vector<v3f> normals;
    std::vector<v2f> uvs;
    
};