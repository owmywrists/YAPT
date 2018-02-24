
void load_obj(std::string filename, 
              std::vector<v3f> &positions, std::vector<v3i> &vertex_ptr, std::vector<v3f> &normals,  std::vector<v3i> &normal_ptr,
              std::vector<v2f> &uvs,      std::vector<v3i> &uv_ptr)
{
    std::ifstream obj;
    std::string line;
    std::string word;
    obj.open(filename);
    std::vector<v3i> f_ptr;
    std::vector<v3f> v_temp;
    std::vector<v3i> n_ptr_temp;
    std::vector<v3f> n_temp;
    std::vector<v3i> uv_ptr_temp;
    std::vector<v2f> uv_temp;
    
    v3i f;
    v3i fi;
    v3i uv;
    v3i uvi;
    v3i n;
    v3i ni;
    while (std::getline(obj, line))
    {
        if (line.substr(0, 2) == "v ")
        {
            v3f pos;
            std::stringstream ss(line.substr(2));
            ss >> pos;
            v_temp.push_back(pos);
        }
        else if (line.substr(0,3) == "vt ")
        {
            v2f temp;
            std::stringstream ss(line.substr(3));
            ss >> temp.x >> temp.y;
            uv_temp.push_back(temp);
        }
        else if (line.substr(0,3) == "vn ")
        {
            std::stringstream ss(line.substr(3));
            v3f vn;
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
            
            f = v3i(fi.x, fi.y, fi.z);
            uv = v3i(uvi.x, uvi.y, uvi.z);
            n = v3i(ni.x, ni.y, ni.z);
            
            f_ptr.push_back(f);
            uv_ptr_temp.push_back(uv);
            n_ptr_temp.push_back(n);
        }
    }
    printf("Loaded obj\n");
    positions = v_temp;
    vertex_ptr = f_ptr;
    normals = n_temp;
    uvs = uv_temp;
    uv_ptr = uv_ptr_temp;
    normal_ptr = n_ptr_temp;
    obj.close();
}
