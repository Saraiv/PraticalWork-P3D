#pragma once

#include <vector>
#include <string>

#include <GL/glew.h>
#include <Windows.h>
#include <gl\GL.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...
#include <glm/gtc/type_ptr.hpp> // value_ptr

#include <iostream>
#include <fstream>

#define WIDTH 1280
#define HEIGHT 720

struct face {
	int index;
	int vertice[4];
	face(int a, int b, int c, int d, int e) {
		vertice[0] = a; vertice[1] = b; vertice[2] = c; vertice[3] = d; index = e;
	}
};

class Objects{
	public:
		std::vector<glm::vec3> Load3DModel();
		glm::vec3 GetVertice(std::string s);
		glm::vec3 GetNormal(std::string s);
		face GetFace(std::string s);
		void ColorBall();
		void Read(std::string filePath);
		void Send();
};
