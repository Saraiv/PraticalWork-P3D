#include"Balls.h"

void Balls::Read(std::string& filename){
	std::fstream arq(filename);
	std::string line = "";

	if (!arq.is_open()) {
		std::cout << "ERRO::Nao foi possivel abrir o arquivo " << filename << std::endl;
	}

	while (getline(arq, line)) {
		if (line.find("v ") != std::string::npos) {
			float x, y, z;
			sscanf_s(line.c_str(), "v %f %f %f", &x, &y, &z);
			glm::vec3 result(x, y, z);
			vertices.push_back(result);
		}
		else if (line.find("vn ") != std::string::npos) {
			float x, y, z;
			sscanf_s(line.c_str(), "vn %f %f %f", &x, &y, &z);
			glm::vec3 result(x, y, z);
			normals.push_back(result);
		}
		else if (line.find("f ") != std::string::npos) {
			int v1, v2, v3, v4, f;
			sscanf_s(line.c_str(), "f %d//%d %d//%d %d//%d %d//%d", &v1, &f, &v2, &f, &v3, &f, &v4, &f);
			face result(v1, v2, v3, v4, f);
			faces.push_back(result);
		}
	}

	arq.close();
}

void Balls::Load(){
	
}

void Balls::Send() {
	//Model
	model = poolTableWindow.Model(accumulatedRotationY);
	//Projection
	projection = poolTableWindow.Projection();
	//View
	view = poolTableWindow.View(ZOOM);

	mvp = projection * view * model;
}