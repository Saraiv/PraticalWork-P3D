#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")
#include"PoolTable.h"
#include"PoolTableWindow.h"
#include"Balls.h"
#include "Lights.h"
#include "Camera.h"
#include "mesa.h"

#define WIDTH 1280
#define HEIGTH 720

PoolTableWindow poolTableWindow;
PoolTable poolTable;
//Balls balls[15];

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		poolTableWindow.mouse_button_state = GLFW_MOUSE_BUTTON_LEFT;
	}
	else {
		poolTableWindow.mouse_button_state = -1;
	}
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	if (yoffset == -1) {
		poolTable.ZOOM += fabs(poolTable.ZOOM) * 0.1f;
	}
	else if (yoffset == 1) {
		poolTable.ZOOM -= fabs(poolTable.ZOOM) * 0.1f;
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	static double lastX = xpos;
	static bool firstMouse = true;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (firstMouse) {
			lastX = xpos;
			firstMouse = false;
		}

		float sensitivity = 0.1f;
		float deltaX = static_cast<float>(xpos - lastX);
		lastX = xpos;
		poolTable.accumulatedRotationY += deltaX * sensitivity;
	}
	else {
		firstMouse = true;
	}
}

void init() {
	glClearColor(0.02f, 0.0f, 0.2f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
}

int main() {
	GLFWwindow* window;
	Camera* camera;
	camera = camera->GetInstance();
	camera->InicializeCamera(45.0f, WIDTH, HEIGHT, glm::vec3(15.0f, 2.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	if (!glfwInit()) return -1;

	window = glfwCreateWindow(WIDTH, HEIGHT, "Pratical Work", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	//Inicia o gestor de extensões GLEW
	glewExperimental = GL_TRUE;
	init();
	glewInit();

	Balls ball5 = Balls("Poolballs/Ball5.obj");
	Mesa mesa = Mesa();
	lights::Lights(&ball5);
	//lights::Lights(mesa);

	while (!glfwWindowShouldClose(window)) {
		
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		//Draw into screen
		//poolTable.Draw();
		//balls[0].Draw(glm::vec3(-5.0f, 2.0f, -8.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		//mesa.display();
		//mesa.Draw(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
		ball5.Draw(glm::vec3(-1.1, 0, 0), glm::vec3(0, 95, 0));
		ball5.Draw(glm::vec3(1, 0, 0), glm::vec3(0, 95, 0));
		ball5.Draw(glm::vec3(-1.1, 0, 3), glm::vec3(0, 95, 0));
		ball5.Draw(glm::vec3(1, 0, 3), glm::vec3(0, 95, 0));
		ball5.Draw(glm::vec3(-1.1, 0, -3), glm::vec3(0, 95, 0));
		ball5.Draw(glm::vec3(1, 0, -3), glm::vec3(0, 95, 0));
		ball5.Draw(glm::vec3(-1.1, 0, 6), glm::vec3(0, 95, 0));
		ball5.Draw(glm::vec3(1, 0, 6), glm::vec3(0, 95, 0));
		ball5.Draw(glm::vec3(-1.1, 0, -6), glm::vec3(0, 95, 0));
		ball5.Draw(glm::vec3(1, 0, -6), glm::vec3(0, 95, 0));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
