#pragma once
#include "Camera.h"

using namespace std;
using namespace glm;


void Camera::InicializeCamera(float fovDegrees, float WindowWidth, float WindowHeight, vec3 pos, vec3 target) {
	zoom = 5.0f;
	this->position = pos;
	this->position.z = zoom;
	this->target = target;
	//Frente da camera
	vec3 cameraFront = position - target;
	//Parte direita da camera
	vec3 cameraRight = cross(cameraFront, vec3(0.0f, 1.0f, 0.0f));
	//Parde de cima do mundo
	vec3 worldUp = -cross(cameraFront, cameraRight);
	//Projeçao do mundo
	projection = perspective(radians(fovDegrees), WindowWidth / WindowHeight, 0.1f, 100.f);
	//Posiçao da camera no mundo
	view = lookAt(this->position, target, worldUp);
}
void Camera::Update() {
	view = lookAt(vec3(position.x, position.y, position.z), target, vec3(0.0f, 1.0f, 0.0f)); // Update a nossa posição do mundo
}
void Camera::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	// assume os primeiros valores de x y 
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	// calcular o offset do x e do y e guardar os valores mais recentes de x e y
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	// multiplicar os offsets pela sensibilidade do rato
	float sensitivity = 0.5f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	// calcular o yaw e o pitch
	yaw += xoffset;
	pitch += yoffset;

	//    // definir os valores limites do pitch 
	if (pitch > 90.0f)
		pitch = 90.0f;
	if (pitch < -90.0f)
		pitch = -90.0f;

	// alterar os valores da camera
	position.x = cos(radians(yaw)) * cos(radians(pitch)) * zoom;
	position.y = -sin(radians(pitch)) * zoom;
	position.z = sin(radians(yaw)) * cos(radians(pitch)) * zoom;
	//position.x = position.x * cos(radians(xoffset));
   // position.z = position.z * -sin(radians(xoffset));




}
void Camera::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	// Se faz zoom in
	if (yoffset == 1) {
		// Incremento no zoom, varia com a distância da câmara
		zoom -= fabs(zoom) * 0.1f;
	}
	// Senão, se faz zoom out
	else if (yoffset == -1) {
		// Incremento no zoom, varia com a distância da câmara
		zoom += fabs(zoom) * 0.1f;
	}


	position.x = cos(radians(yaw)) * cos(radians(pitch)) * zoom;
	position.y = -sin(radians(pitch)) * zoom;
	position.z = sin(radians(yaw)) * cos(radians(pitch)) * zoom;



	cout << "ZOOM = " << zoom << endl;
}

//construtor para alocar memoria
Camera* Camera::instance = nullptr;

//construtor para inicializar a camera
Camera* Camera::GetInstance() {
	return (!instance) ?
		instance = new Camera :
		instance;
}