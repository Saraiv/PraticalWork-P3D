#include"Objects.h"

Objects::Objects(){}

bool Objects::LoadObject(const char* filename, std::vector<GLfloat>& vertices){
	std::ifstream file(filename);
	if(!file.is_open()){
		std::cerr << "Erro a abrir o ficheiro: " << filename << std::endl;
		return false;
	}

	while(!file.eof()){
		char line[256];
		file.getline(line, 256);

		if(line[0] == 'v' && line[1] == ' '){
			GLfloat x, y, z;
			sscanf_s(line, "v %f %f %f", &x, &y, &z);
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

		}
	}

	file.close();
	return true;
}

void Objects::RenderObject(const std::vector<GLfloat>& vertices){
	glBegin(GL_POLYGON);

	for(int i = 0; i < vertices.size(); i += 3){
		glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
	}

	glEnd();
}

void Objects::Render(const char* filename, GLFWwindow* window){
	glClear(GL_COLOR_BUFFER_BIT);

	std::vector<GLfloat> vertices;
	if(LoadObject(filename, vertices)){
		RenderObject(vertices);
	} else return;

	glfwSwapBuffers(window);
}

Objects::~Objects(){}
