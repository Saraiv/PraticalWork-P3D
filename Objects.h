#pragma once

#include <vector>

#include <GL/glew.h>
#include <Windows.h>
#include <gl\GL.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...
#include <glm/gtc/type_ptr.hpp> // value_ptr

#include <iostream>
#include <fstream>

class Objects{
	public:
		Objects();
		bool LoadObject(const char* filename, std::vector<GLfloat>& vertices);
		void RenderObject(const std::vector<GLfloat>& vertices);
		void Render(const char* filename, GLFWwindow* window);
		~Objects();
};
