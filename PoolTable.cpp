#include"PoolTable.h"

void PoolTable::Send(){
	//Model
	model = poolTableWindow.Model(accumulatedRotationY);
	//Projection
	projection = poolTableWindow.Projection();
	//View
	view = poolTableWindow.View(ZOOM);

	mvp = projection * view * model;
}

void PoolTable::Load(){
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

	for (auto i : point)
		poolTable.push_back(i);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float* vertex_stream = static_cast<float*>(glm::value_ptr(poolTable.front()));

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