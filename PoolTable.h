#pragma once
#include <vector>

#include <GL/glew.h>
#include <Windows.h>
#include <gl\GL.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...
#include <glm/gtc/type_ptr.hpp> // value_ptr

#include"PoolTableWindow.h"

#define WIDTH 1280
#define HEIGHT 720

class PoolTable {
	public:
		void Send();
		void Load();

		float accumulatedRotationY = 0.0f;
		float ZOOM = 15.0f;
	private:
		PoolTableWindow poolTableWindow;
		std::vector<glm::vec3> poolTable;
		glm::mat4 mvp, model, projection, view;
};
