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
#include "stb_image.h"
#include "LoadShaders.h"

#define WIDTH 1280
#define HEIGHT 720

#define NumVertices 36

class Mesa {
public:
	Mesa();
	void Draw(glm::vec3 position, glm::vec3 orientation);
	void print_gl_info(void);
	GLuint Send(void);
	void display(void);
	void print_error(int error, const char* description);
	glm::vec3 ka, kd, ks;
	GLfloat ns;

	float accumulatedRotationY = 0.0f;
	float ZOOM = 15.0f;
private:
	
	glm::mat4 Model, View, Projection;
	GLuint VAO;
	GLuint Buffer;
	GLuint programa;
	GLfloat angle = 0.0f;
	glm::mat4 mesa;
	GLfloat vertices[NumVertices * 3] = {
        20.5f, -1.0f,  10.5f,
        20.5f, -1.0f, -10.5f,
        20.5f,  1.0f,  10.5f,
        // Segundo triângulo
        // Posições
        20.5f,  1.0f,  10.5f,
        20.5f, -1.0f, -10.5f,
        20.5f,  1.0f, -10.5f,

        // Primeiro triângulo
        // Posições
        -20.5f, -1.0f, -10.5f,
        -20.5f, -1.0f, 10.5f,
        -20.5f,  1.0f, -10.5f,
        // Segundo triângulo
        // Posições
        -20.5f,  1.0f, -10.5f,
        -20.5f, -1.0f,  10.5f,
        -20.5f,  1.0f,  10.5f,

        // Primeiro triângulo
        // Posições
        -20.5f,  1.0f,  10.5f,
         20.5f,  1.0f,  10.5f,
        -20.5f,  1.0f, -10.5f,
        // Segundo triângulo
        // Posições
        -20.5f,  1.0f, -10.5f,
         20.5f,  1.0f,  10.5f,
         20.5f,  1.0f, -10.5f,
         // ************************************************
         //                       Y- (face #3)
         // ************************************************
         // Primeiro triângulo
         // Posições
         -20.5f, -1.0f, -10.5f,
          20.5f, -1.0f, -10.5f,
         -20.5f, -1.0f,  10.5f,
         // Segundo triângulo
         // Posições
         -20.5f, -1.0f,  10.5f,
          20.5f, -1.0f, -10.5f,
          20.5f, -1.0f,  10.5f,

          // Primeiro triângulo
          // Posições
          -20.5f, -1.0f, 10.5f,
           20.5f, -1.0f, 10.5f,
          -20.5f,  1.0f, 10.5f,
          // Segundo triângulo
          // Posições
         -20.5f,  1.0f, 10.5f,
          20.5f, -1.0f, 10.5f,
          20.5f,  1.0f, 10.5f,

          // Primeiro triângulo
          // Posições
          20.5f, -1.0f, -10.5f,
         -20.5f, -1.0f, -10.5f,
          20.5f,  1.0f, -10.5f,
          // Segundo triângulo
          // Posições
           20.5f,  1.0f, -10.5f,
          -20.5f, -1.0f, -10.5f,
          -20.5f,  1.0f, -10.5f
	};
};
inline Mesa::Mesa() {
	Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	View = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 5.0f),	// eye (posição da câmara).
		glm::vec3(0.0f, 0.0f, 0.0f),	// center (para onde está a "olhar")
		glm::vec3(0.0f, 1.0f, 0.0f)		// up
	);
	Model = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 ModelViewProjection = Projection * View * Model;
}

