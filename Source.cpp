#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")
#include"PoolTable.h"

PoolTable poolTable;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		poolTable.mouse_button_state = GLFW_MOUSE_BUTTON_LEFT;
	}
	else {
		poolTable.mouse_button_state = -1;
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
	if (poolTable.mouse_button_state == GLFW_MOUSE_BUTTON_LEFT) {
		if (poolTable.lastMouseX == 0.0) {
			poolTable.lastMouseX = xpos;
			poolTable.initialRotationY = poolTable.accumulatedRotationY;
		}

		double deltaX = xpos - poolTable.lastMouseX;
		poolTable.lastMouseX = xpos;

		float sensitivity = 0.1f;
		poolTable.accumulatedRotationY += poolTable.initialRotationY + static_cast<float>(deltaX) * sensitivity;
	}
}

int main() {
	//Objeto
	poolTable = PoolTable();
	GLFWwindow* window;

	if (!glfwInit()) return -1;

	window = glfwCreateWindow(WIDTH, HEIGHT, "Pratical Work", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	// Projection
	poolTable.Projection();

	while (!glfwWindowShouldClose(window)) {
		// View
		poolTable.View();

		// Model & Projection & View & Object & Pool Table Colors
		poolTable.Init();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}