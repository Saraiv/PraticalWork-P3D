#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

#include"Balls.h"
#include "Lights.h"
#include "Camera.h"
#include "mesa.h"

#define WIDTH 1280
#define HEIGTH 720

using namespace std;
using namespace glm;

void init() {
	glClearColor(0.02f, 0.0f, 0.2f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
}

int main() {
	GLFWwindow* window;
	// Criação da camera e a sua instancia na main
	Camera* camera;
	camera = camera->GetInstance();
	// Inicialização da camera e posição da mesma no mundo
	camera->InicializeCamera(45.0f, WIDTH, HEIGHT, vec3(15.0f, 2.5f, 0.0f), vec3(0.0f, 0.0f, 0.0f));

	// Inicializaçao das funçoes glfw
	if (!glfwInit()) return -1;

	window = glfwCreateWindow(WIDTH, HEIGHT, "Pratical Work", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//Inicia o gestor de extensões GLEW
	glewExperimental = GL_TRUE;
	init();
	glewInit();

	//Criaçao das bolas
	Balls ball5 = Balls("Poolballs/Ball5.obj");

	//Criaçao da mesa
	Mesa mesa = Mesa();

	//Aplicar os shaders e luzes as bolas e a mesa
	lights::Lights(&ball5);
	//lights::Lights(mesa);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Desenhar as bolas e a mesa
		ball5.Draw(vec3(-1.1, 0, 0), vec3(0, 95, 0));
		ball5.Draw(vec3(1, 0, 0), vec3(0, 95, 0));
		ball5.Draw(vec3(-1.1, 0, 3), vec3(0, 95, 0));
		ball5.Draw(vec3(1, 0, 3), vec3(0, 95, 0));
		ball5.Draw(vec3(-1.1, 0, -3), vec3(0, 95, 0));
		ball5.Draw(vec3(1, 0, -3), vec3(0, 95, 0));
		ball5.Draw(vec3(-1.1, 0, 6), vec3(0, 95, 0));
		ball5.Draw(vec3(1, 0, 6), vec3(0, 95, 0));
		ball5.Draw(vec3(-1.1, 0, -6), vec3(0, 95, 0));
		ball5.Draw(vec3(1, 0, -6), vec3(0, 95, 0));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
