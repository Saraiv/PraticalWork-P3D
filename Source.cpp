#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <Windows.h>
#include <gl\GL.h>

#include <windows.h>

#include <GLFW\glfw3.h>

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...
#include <glm/gtc/type_ptr.hpp> // value_ptr

void init(void);

#define WIDTH 1280
#define HEIGHT 720

GLfloat ZOOM = 15.0f;

float initialRotationY = 0.0f;
float accumulatedRotationY = 0.0f;
double lastMouseX = 0.0;


int mouse_button_state = -1;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		mouse_button_state = GLFW_MOUSE_BUTTON_LEFT;
	}
	else {
		mouse_button_state = -1;
	}
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	if (yoffset == -1) {
		ZOOM += fabs(ZOOM) * 0.1f;
	}
	else if (yoffset == 1) {
		ZOOM -= fabs(ZOOM) * 0.1f;
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	if (mouse_button_state == GLFW_MOUSE_BUTTON_LEFT) {
		if (lastMouseX == 0.0) {
			lastMouseX = xpos;
			initialRotationY = accumulatedRotationY;
		}

		double deltaX = xpos - lastMouseX;
		lastMouseX = xpos;

		float sensitivity = 0.1f;
		accumulatedRotationY += initialRotationY + static_cast<float>(deltaX) * sensitivity;
	}
}

std::vector<glm::vec3> Load3DModel(void) {
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

void display(std::vector<glm::vec3> obj, glm::mat4 mvp) {
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

int main(void) {
	std::vector<glm::vec3> obj = Load3DModel();

	GLFWwindow* window;

	if (!glfwInit()) return -1;

	window = glfwCreateWindow(WIDTH, HEIGHT, "Pratical Work", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	init();

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	// Projection
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(WIDTH) / float(HEIGHT), 0.1f, 100.f);

	while (!glfwWindowShouldClose(window)) {
		// View
		glm::mat4 view = glm::lookAt(
			glm::vec3(10.0f, 5.0f, -ZOOM),	// Posicao da camara no mundo
			glm::vec3(0.0f, 0.5f, 0.0f),	// Direcao para a qual a camara esta apontada
			glm::vec3(0.0f, 1.0f, 0.0f)		// Vector vertical
		);

		// Model
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(accumulatedRotationY), glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 mvp = projection * view * model;

		display(obj, mvp);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	// Descomentar para ativar o Face Culling
	glEnable(GL_CULL_FACE);
}