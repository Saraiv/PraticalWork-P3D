#include"PoolTable.h"

PoolTable::PoolTable() {
	PoolTable::Load3DModel();
}

void PoolTable::Init() {
	//Model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(accumulatedRotationY), glm::vec3(0.0f, 1.0f, 0.0f));
	//Projection
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(WIDTH) / float(HEIGHT), 0.1f, 100.f);
	//View
	glm::mat4 view = PoolTable::View();
	//Object
	std::vector<glm::vec3> obj = PoolTable::Load3DModel();

	glm::mat4 mvp = projection * view * model;

	PoolTable::ColorRectangle(obj, mvp);
}

glm::mat4 PoolTable::Projection() {
	return glm::perspective(glm::radians(45.0f), float(WIDTH) / float(HEIGHT), 0.1f, 100.f);;
}

std::vector<glm::vec3> PoolTable::Load3DModel() {
	glm::vec3 point[6 * 4] = {
		// Frente
		glm::vec3(-5.0f, 0.5f, -8.0f),
		glm::vec3(5.0f, 0.5f, -8.0f),
		glm::vec3(5.0f, -0.5f, -8.0f),
		glm::vec3(-5.0f, -0.5f, -8.0f),

		// Trás
		glm::vec3(-5.0f, -0.5f, 8.0f),
		glm::vec3(5.0f, -0.5f, 8.0f),
		glm::vec3(5.0f, 0.5f, 8.0f),
		glm::vec3(-5.0f, 0.5f, 8.0f),

		// Direita
		glm::vec3(5.0f, -0.5f, -8.0f),
		glm::vec3(5.0f, 0.5f, -8.0f),
		glm::vec3(5.0f, 0.5f, 8.0f),
		glm::vec3(5.0f, -0.5f, 8.0f),

		// Esquerda
		glm::vec3(-5.0f, -0.5f, 8.0f),
		glm::vec3(-5.0f, 0.5f, 8.0f),
		glm::vec3(-5.0f, 0.5f, -8.0f),
		glm::vec3(-5.0f, -0.5f, -8.0f),

		// Cima
		glm::vec3(-5.0f, 0.5f, 8.0f),
		glm::vec3(5.0f, 0.5f, 8.0f),
		glm::vec3(5.0f, 0.5f, -8.0f),
		glm::vec3(-5.0f, 0.5f, -8.0f),

		// Baixo
		glm::vec3(-5.0f, -0.5f, -8.0f),
		glm::vec3(5.0f, -0.5f, -8.0f),
		glm::vec3(5.0f, -0.5f, 8.0f),
		glm::vec3(-5.0f, -0.5f, 8.0f)
	};

	std::vector<glm::vec3> ret;
	for (auto i : point)
		ret.push_back(i);

	return ret;
}

void PoolTable::ColorRectangle(std::vector<glm::vec3> obj, glm::mat4 mvp) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float* vertex_stream = static_cast<float*>(glm::value_ptr(obj.front()));

	glBegin(GL_QUADS);

	for (int nv = 0; nv < 6 * 4 * 3; nv += 12) {
		if (nv < 12) {
			glColor3f(.4f, .8f, .4f);
		}
		else {
			glColor3f(0.4f, 1.0f, 0.4f);
		}

		for (int i = 0; i < 12; i += 3) {
			glm::vec4 vertex = glm::vec4(vertex_stream[nv + i], vertex_stream[nv + i + 1], vertex_stream[nv + i + 2], 1.0f);
			glm::vec4 transformed_vertex = mvp * vertex;
			glm::vec4 normalized_vertex = transformed_vertex / transformed_vertex.w;
			glVertex3f(normalized_vertex.x, normalized_vertex.y, normalized_vertex.z);
		}
	}

	glEnd();
}

glm::mat4 PoolTable::View() {
	glm::mat4 view = glm::lookAt(
		glm::vec3(10.0f, 5.0f, -ZOOM),	// Posicao da camara no mundo
		glm::vec3(0.0f, 0.5f, 0.0f),	// Direcao para a qual a camara esta apontada
		glm::vec3(0.0f, 1.0f, 0.0f)		// Vector vertical
	);

	return view;
}