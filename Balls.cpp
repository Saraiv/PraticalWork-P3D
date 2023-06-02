#include"Balls.h"

void Balls::Read(std::string& filename){
	std::fstream arq(filename);
	std::string line = "";

	if (!arq.is_open()) {
		std::cout << "ERRO: Nao foi possivel abrir o arquivo " << filename << std::endl;
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

	for (auto i : vertices)
		ball.push_back(i);
}

void Balls::Load(){
	float* vertex_stream = static_cast<float*>(glm::value_ptr(ball.front()));

	glBegin(GL_QUADS);
		for (const face& face : faces) {
			glColor3f(1.0f, 0.4f, 0.4f);

			for (int i = 0; i < 4; i++){
				glm::vec4 vertex = glm::vec4(vertex_stream[i + i], vertex_stream[i + 1], vertex_stream[i + 2], 1.0f);
				glm::vec4 transformed_vertex = mvp * vertex;
				glm::vec4 normalized_vertex = transformed_vertex / transformed_vertex.w;
				glVertex3f(normalized_vertex.x, normalized_vertex.y, normalized_vertex.z);
			}
		}
	glEnd();
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