#pragma once
#include <vector>

#include <GL/glew.h>
#include <Windows.h>
#include <gl\GL.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...

#define WIDTH 1280
#define HEIGHT 720

class PoolTable {
	public:
		PoolTable();
		void Init();
		static std::vector<glm::vec3> Load3DModel();
		static void ColorRectangle(std::vector<glm::vec3> obj, glm::mat4 mvp);
		glm::mat4 View();
		static glm::mat4 Projection();
		int mouse_button_state = -1;
		float accumulatedRotationY = 0.0f, initialRotationY = 0.0f;
		float ZOOM = 15.0f;
		double lastMouseX = 0.0f;

	private:
		static glm::mat4 projection;
};
