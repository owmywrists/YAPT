#include "obj_parser.h"

void Obj::parse_faces() {
	string line;
	string word;
	m_obj.open(m_filename);
	while (std::getline(m_obj, line)) {

		if (line.substr(0,2) == "v ") {
			std::istringstream ss(line.substr(2));
			//while (getline(ss, line, ' ')) {
				float3 v;
				//printf("%f\n", v.x());
				ss >> v;
				std::cout << v << "\n";
				//printf("%f", v.x());
				m_vertices.push_back(v);
			//} 
	}
		else if (line.substr(0, 2) == "f ") {
			std::istringstream ss(line.substr(2));
			//while (getline(ss, line, ' ')) {
				float3 f;
				ss >> f;
				std::cout << f << "\n";
				//printf("%d\n", f.x());
				m_faces.push_back(f);
			//}
	}
	}
	m_obj.close();
	}


Obj::Obj(string filename) {
	m_filename = filename;

	parse_faces();

}

float3 Obj::face(int i){
	return m_faces[i];
}

vector<Surface*> Obj::getScene(){
	vector<Surface*> m_scene;
	for (int i = 0; i < m_faces.size(); i++){
		float3 f = face(i);
		//for (int j = 0; j < 3; j++){
			float3 v0 = m_vertices[f.x()-1];
			float3 v1 = m_vertices[f.y()-1];
			float3 v2 = m_vertices[f.z()-1];
			std::cout << "FACE IS: " << f << std::endl;
			std::cout << "TRIANGLE IS: " <<v0 << " " << v1 << " " << v2 << std::endl;
			m_scene.push_back(new Triangle(v0, v1, v2,
			MaterialFactory::Diffuse, float3(0.5,0.0,0.0)));
		//}
	}
	return m_scene;
}