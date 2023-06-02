#include"PoolTableWindow.h"

glm::mat4 PoolTableWindow::View(float ZOOM) {
	glm::mat4 view = glm::lookAt(
		glm::vec3(10.0f, 5.0f, -ZOOM),	// Posicao da camara no mundo
		glm::vec3(0.0f, 0.5f, 0.0f),	// Direcao para a qual a camara esta apontada
		glm::vec3(0.0f, 1.0f, 0.0f)		// Vector vertical
	);

	return view;
}

glm::mat4 PoolTableWindow::Projection() {
	return glm::perspective(glm::radians(45.0f), float(WIDTH) / float(HEIGHT), 0.1f, 100.f);
}

glm::mat4 PoolTableWindow::Model(float accumulatedRotationY) {
	return glm::rotate(glm::mat4(1.0f), glm::radians(accumulatedRotationY), glm::vec3(0.0f, 1.0f, 0.0f));
}