#include"Objects.h"

glm::vec3 Objects::GetVertice(std::string s){
	float x, y, z;
	sscanf_s(s.c_str(), "v %f %f %f", &x, &y, &z);
	glm::vec3 result(x, y, z);
	return result;
}

glm::vec3 Objects::GetNormal(std::string s){
	float x, y, z;
	sscanf_s(s.c_str(), "vn %f %f %f", &x, &y, &z);
	glm::vec3 result(x, y, z);
	return result;
}

face Objects::GetFace(std::string s){
	int v1, v2, v3, v4, f;
	sscanf_s(s.c_str(), "f %d//%d %d//%d %d//%d %d//%d", &v1, &f, &v2, &f, &v3, &f, &v4, &f);
	face result(v1, v2, v3, v4, f);
	return result;
}

void Objects::Read(std::string filename){
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<face> faces;
	
	std::fstream arq(filename);
	std::string line = "";

	if(!arq.is_open()){
		std::cout << "ERRO::Nao foi possivel abrir o arquivo " << filename << std::endl;
	}
	
	while(getline(arq, line)){
		if(line.find("v ") != std::string::npos){
			glm::vec3 tempVertice = GetVertice(line);
			vertices.push_back(tempVertice);
		} else if(line.find("vn ") != std::string::npos){
			glm::vec3 tempNormal = GetNormal(line);
			normals.push_back(tempNormal);
		} else if(line.find("f ") != std::string::npos){
			face tempFace = GetFace(line);
			faces.push_back(tempFace);
		}
	}

	std::cout << "V: " << vertices.size() << std::endl;
	std::cout << "N: " << normals.size() << std::endl;
	std::cout << "F: " << faces.size() << std::endl;
}

void Objects::ColorBall(){

}

void Objects::Send() {
	//Model
	glm::mat4 model = glm::mat4(1.0f);

	//Projection
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(WIDTH) / float(HEIGHT), 0.1f, 100.f);

	ColorBall();
}