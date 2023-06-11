#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <random>

#include <GL/glew.h>
#include <Windows.h>
#include <gl\GL.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...
#include <glm/gtc/type_ptr.hpp> // value_ptr

#define WIDTH 1280
#define HEIGHT 720
#define GLEW_STATIC
#define NumeroDeVAOs 1 //1 VAO
#define NumBuffers 3 // Vértices, Coordenadas texturas, normais

using namespace std;
using namespace glm;

class Balls{
	public:
		void Read(const string objFilepath);
		GLuint Send(void);
		void Load(string fileName);
		void Draw(vec3 position, vec3 orientation);
		void Texture(const string textureFile);
		mat4 ball;
		Balls(const char* filename);
		float accumulatedRotationY = 0.0f;
		float ZOOM = 15.0f;
		//Balls(const char* filename);
		vec3 ka, kd, ks;
		GLfloat ns;

	private:
		//Vertex Pos
		vector<vec3> vertex_positions;
		vector<vec2> vertex_textures_coords;
		vector<vec3> vertex_normals;

		GLuint VAO;
		GLuint Buffers[NumBuffers];
		GLuint programa;

		const GLuint NumVertices = 4034;

		float Ns; // Expoente especular
		float angle = 0.0f;
};
inline Balls::Balls (const char* filename) {
	ball= mat4(1.0f);
	Read(filename);
}


