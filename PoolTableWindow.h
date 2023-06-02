#pragma once
#include <vector>

#include <GL/glew.h>
#include <Windows.h>
#include <gl\GL.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...
#include <glm/gtc/type_ptr.hpp> // value_ptr

#define WIDTH 1280
#define HEIGHT 720

class PoolTableWindow {
	public:
		glm::mat4 View(float ZOOM);
		glm::mat4 Projection();
		glm::mat4 Model(float accumulatedRotationY);

		int mouse_button_state = -1;
		double lastMouseX = 0.0f;

};