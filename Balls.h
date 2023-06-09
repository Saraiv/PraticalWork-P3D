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

#include"PoolTableWindow.h"

#define WIDTH 1280
#define HEIGHT 720
#define GLEW_STATIC
#define NumeroDeVAOs 1 //1 VAO
#define NumBuffers 3 // Vértices, Coordenadas texturas, normais

class Balls{
	public:
		void Read(const std::string objFilepath);
		GLuint Send();
		void Load(std::string fileName);
		void Draw(glm::vec3 position, glm::vec3 orientation);

		void getDirectionalLightActive();
		void getDirectionalLightInactive();
		void getPontualLightActive();
		void getPontualLightInactive();
		void getSpotLightActive();
		void getSpotLightInactive();
		void Texture(const std::string textureFile);

		float accumulatedRotationY = 0.0f;
		float ZOOM = 15.0f;

		bool lightMode1 = true;
		bool lightMode2 = true;
		bool lightMode3 = true;
		bool lightMode4 = true;
		float deformeffect = 0;

	private:
		//Vertex Pos
		std::vector<glm::vec3> vertex_positions;
		std::vector<glm::vec2> vertex_textures_coords;
		std::vector<glm::vec3> vertex_normals;

		PoolTableWindow poolTableWindow;
		std::vector<glm::vec3> poolTable;
		glm::mat4 mvp = poolTableWindow.Model(accumulatedRotationY),
				  model = poolTableWindow.Projection(),
				  projection = poolTableWindow.View(ZOOM),
				  view = projection * view * model;
		glm::mat3 normalMatrix;
		GLuint VAO;
		GLuint Buffers[NumBuffers];
		GLuint programa;

		const GLuint NumVertices = 4034;

		// Luzes Coeficientes:
		glm::vec3 ka; // Da Luz Ambiente
		glm::vec3 kd; // Da Luz Difusa
		glm::vec3 ks; // Da Luz Luz especular

		

		float Ns; // Expoente especular
		float angle = 0.0f;
};
