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

using namespace std;
using namespace glm;

class Mesa {
public:
	Mesa();
	void Draw(vec3 position, vec3 orientation);
	void print_gl_info(void);
	GLuint Send(void);
	void display(void);
	void print_error(int error, const char* description);
	vec3 ka, kd, ks;
	GLfloat ns;

	float accumulatedRotationY = 0.0f;
	float ZOOM = 15.0f;
private:
	
	mat4 Model, View, Projection;
	GLuint VAO;
	GLuint Buffer;
	GLuint programa;
	GLfloat angle = 0.0f;
	mat4 mesa;
	GLfloat vertices[NumVertices * 3] = {
        20.5f, -1.0f,  10.5f,
        20.5f, -1.0f, -10.5f,
        20.5f,  1.0f,  10.5f,
        // Segundo tri�ngulo
        // Posi��es
        20.5f,  1.0f,  10.5f,
        20.5f, -1.0f, -10.5f,
        20.5f,  1.0f, -10.5f,

        // Primeiro tri�ngulo
        // Posi��es
        -20.5f, -1.0f, -10.5f,
        -20.5f, -1.0f, 10.5f,
        -20.5f,  1.0f, -10.5f,
        // Segundo tri�ngulo
        // Posi��es
        -20.5f,  1.0f, -10.5f,
        -20.5f, -1.0f,  10.5f,
        -20.5f,  1.0f,  10.5f,

        // Primeiro tri�ngulo
        // Posi��es
        -20.5f,  1.0f,  10.5f,
         20.5f,  1.0f,  10.5f,
        -20.5f,  1.0f, -10.5f,
        // Segundo tri�ngulo
        // Posi��es
        -20.5f,  1.0f, -10.5f,
         20.5f,  1.0f,  10.5f,
         20.5f,  1.0f, -10.5f,
         // ************************************************
         //                       Y- (face #3)
         // ************************************************
         // Primeiro tri�ngulo
         // Posi��es
         -20.5f, -1.0f, -10.5f,
          20.5f, -1.0f, -10.5f,
         -20.5f, -1.0f,  10.5f,
         // Segundo tri�ngulo
         // Posi��es
         -20.5f, -1.0f,  10.5f,
          20.5f, -1.0f, -10.5f,
          20.5f, -1.0f,  10.5f,

          // Primeiro tri�ngulo
          // Posi��es
          -20.5f, -1.0f, 10.5f,
           20.5f, -1.0f, 10.5f,
          -20.5f,  1.0f, 10.5f,
          // Segundo tri�ngulo
          // Posi��es
         -20.5f,  1.0f, 10.5f,
          20.5f, -1.0f, 10.5f,
          20.5f,  1.0f, 10.5f,

          // Primeiro tri�ngulo
          // Posi��es
          20.5f, -1.0f, -10.5f,
         -20.5f, -1.0f, -10.5f,
          20.5f,  1.0f, -10.5f,
          // Segundo tri�ngulo
          // Posi��es
           20.5f,  1.0f, -10.5f,
          -20.5f, -1.0f, -10.5f,
          -20.5f,  1.0f, -10.5f
	};
};
inline Mesa::Mesa() {
	Projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	View = lookAt(
		vec3(0.0f, 0.0f, 5.0f),	// eye (posi��o da c�mara).
		vec3(0.0f, 0.0f, 0.0f),	// center (para onde est� a "olhar")
		vec3(0.0f, 1.0f, 0.0f)		// up
	);
	Model = rotate(mat4(1.0f), angle, vec3(0.0f, 1.0f, 0.0f));
	mat4 ModelViewProjection = Projection * View * Model;
}

