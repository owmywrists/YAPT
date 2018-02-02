#include "obj_parser.h"

void load_obj(string filename, 
              vector<Vertex> &vertices, vector<float3> &vertex_ptr, vector<float3> &normals,  vector<float3> &normal_ptr,
              vector<UV> &uvs,      vector<float3> &uv_ptr)
{
    std::ifstream obj;
    string line;
    string word;
    obj.open(filename);
    vector<float3> f_ptr;
    vector<Vertex> v_temp;
    vector<float3> n_ptr_temp;
    vector<float3> n_temp;
    vector<float3> uv_ptr_temp;
    vector<UV> uv_temp;
    
    float3 f;
    v3<int> fi;
    float3 uv;
    v3<int> uvi;
    float3 n;
    v3<int> ni;
    while (std::getline(obj, line))
    {
        if (line.substr(0, 2) == "v ")
        {
            Vertex v;
            std::istringstream ss(line.substr(2));
            float3 p;
            ss >> p;
            v.pos = p;
            v_temp.push_back(v);
        }
        else if (line.substr(0,3) == "vt ")
        {
            UV temp;
            std::istringstream ss(line.substr(3));
            ss >> temp.x >> temp.y;
            //float3 uv_t(tx,ty,0);
            uv_temp.push_back(temp);
        }
        else if (line.substr(0,3) == "vn ")
        {
            std::istringstream ss(line.substr(3));
            float3 vn;
            ss >> vn;
            n_temp.push_back(vn);
        }
        else if (line.substr(0, 2) == "f ")
        { 
            
            std::string str_list = line.substr(2);
            std::replace(str_list.begin(), str_list.end(), '/', ' ');
            const char* line_char = str_list.c_str();
            
            sscanf(line_char, " %d %d %d %d %d %d %d %d %d",
                   &fi.x, &uvi.x, &ni.x,
                   &fi.y, &uvi.y, &ni.y,
                   &fi.z, &uvi.z, &ni.z);
            f = float3(fi.x, fi.y, fi.z);
            
            uv = float3(uvi.x, uvi.y, uvi.z);
            n = float3(ni.x, ni.y, ni.z);
            f_ptr.push_back(f);
            uv_ptr_temp.push_back(uv);
            n_ptr_temp.push_back(n);
        }
    }
    /*
    std::ofstream out;
    
    out.open("out.obj");
    for (int i = 0; i < v_temp.size(); i++)
    {
        out <<"v " <<  v_temp[i].pos << std::endl;
    }
    for (int i = 0; i < uv_temp.size(); i++)
    {
        out << "vt " << uv_temp[i] << std::endl;
    }
    for (int i =0; i < n_temp.size(); i++)
    {
        out << "vn " << n_temp[i] << std::endl;
    }
    out << "s off" << std::endl;
    printf("%d", f_ptr.size());
    for (int i = 0; i < f_ptr.size(); i++)
    {
        out << "f " << 
            f_ptr[i].x << "/" 
            << uv_ptr_temp[i].x << "/" 
            << n_ptr_temp[i].x << " " <<
            f_ptr[i].y << "/" 
            << uv_ptr_temp[i].y << "/" 
            << n_ptr_temp[i].y << " " <<
            f_ptr[i].z << "/" 
            << uv_ptr_temp[i].z << "/" 
            << n_ptr_temp[i].z
            << std::endl;
    }
    out.close();
    */
    printf("I am done\n");
    vertices = v_temp;
    vertex_ptr = f_ptr;
    normals = n_temp;
    uvs = uv_temp;
    uv_ptr = uv_ptr_temp;
    normal_ptr = n_ptr_temp;
    obj.close();
}
