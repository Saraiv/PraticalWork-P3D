#pragma once
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <Windows.h>
#include <gl\GL.h>
#define GLFW_USE_DWM_SWAP_INTERVAL
#include <GLFW\glfw3.h>

#include <iostream>
#include <string>
#include <vector>

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...
#include <glm/gtc/type_ptr.hpp> // value_ptr
#include"Camera.h"
#include "Balls.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WIDTH 1280
#define HEIGHT 720

class Mesa {
public:
	void Draw();
	void print_gl_info(void);
	void display(void);
	void print_error(int error, const char* description);

	float accumulatedRotationY = 0.0f;
	float ZOOM = 15.0f;
private:
	
	glm::mat4 Model, View, Projection;
	GLuint VAO;
	GLuint Buffer;
	GLuint programa;
	GLfloat angle = 0.0f;
};

