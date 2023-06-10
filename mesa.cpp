//#include"mesa.h"
//
//#define WIDTH 1280
//#define HEIGTH 720
//
//using namespace std;
//GLuint VAO;
//GLuint Buffer;
//const GLuint NumVertices = 6 * 2 * 3; // 6 faces * 2 triângulos/face * 3 vértices/triângulo
//
//GLuint programa;
//
//glm::mat4 Model, View, Projection;
//GLfloat angle = 0.0f;
//
//void print_gl_info(void) {
//	GLint major, minor;
//	glGetIntegerv(GL_MAJOR_VERSION, &major);
//	glGetIntegerv(GL_MINOR_VERSION, &minor);
//	cout << "\nOpenGL version " << major << '.' << minor << endl;
//
//	const GLubyte* glversion = glGetString(GL_VERSION);
//	const GLubyte* glvendor = glGetString(GL_VENDOR);
//	const GLubyte* glrenderer = glGetString(GL_RENDERER);
//	cout << "\nVersion:  " << glversion << endl <<
//		"Vendor:   " << glvendor << endl <<
//		"Renderer: " << glrenderer << endl;
//
//	cout << "\nSupported GLSL versions:\n";
//	const GLubyte* glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);
//	cout << "Higher supported version:\n\t" << glslversion << endl;
//	GLint numglslversions;
//	cout << "Other supported versions:\n";
//	glGetIntegerv(GL_NUM_SHADING_LANGUAGE_VERSIONS, &numglslversions);
//	for (int n = 0; n < numglslversions; n++) {
//		cout << '\t' << glGetStringi(GL_SHADING_LANGUAGE_VERSION, n) << endl;
//	}
//}
//
//void print_error(int error, const char* description) {
//	cout << description << endl;
//}
//
//void Mesa::Draw() {
//	GLfloat vertices[NumVertices * 3] = {
//		//*************************************************
//		//                       X+ (face #0)
//		// ************************************************
//		// Primeiro triângulo
//		// Posições
//		0.5f, -0.5f,  0.5f,
//		0.5f, -0.5f, -0.5f,
//		0.5f,  0.5f,  0.5f,
//		// Segundo triângulo
//		// Posições
//		0.5f,  0.5f,  0.5f,
//		0.5f, -0.5f, -0.5f,
//		0.5f,  0.5f, -0.5f,
//		// ************************************************
//		//                       X- (face #1)
//		// ************************************************
//		// Primeiro triângulo
//		// Posições
//		-0.5f, -0.5f, -0.5f,
//		-0.5f, -0.5f,  0.5f,
//		-0.5f,  0.5f, -0.5f,
//		// Segundo triângulo
//		// Posições
//		-0.5f,  0.5f, -0.5f,
//		-0.5f, -0.5f,  0.5f,
//		-0.5f,  0.5f,  0.5f,
//		// ************************************************
//		//                       Y+ (face #2)
//		// ************************************************
//		// Primeiro triângulo
//		// Posições
//		-0.5f,  0.5f,  0.5f,
//		 0.5f,  0.5f,  0.5f,
//		-0.5f,  0.5f, -0.5f,
//		// Segundo triângulo
//		// Posições
//		-0.5f,  0.5f, -0.5f,
//		 0.5f,  0.5f,  0.5f,
//		 0.5f,  0.5f, -0.5f,
//		 // ************************************************
//		 //                       Y- (face #3)
//		 // ************************************************
//		 // Primeiro triângulo
//		 // Posições
//		 -0.5f, -0.5f, -0.5f,
//		  0.5f, -0.5f, -0.5f,
//		 -0.5f, -0.5f,  0.5f,
//		 // Segundo triângulo
//		 // Posições
//		 -0.5f, -0.5f,  0.5f,
//		  0.5f, -0.5f, -0.5f,
//		  0.5f, -0.5f,  0.5f,
//		  // ************************************************
//		  //                       Z+ (face #4)
//		  // ************************************************
//		  // Primeiro triângulo
//		  // Posições
//		  -0.5f, -0.5f, 0.5f,
//		  0.5f, -0.5f, 0.5f,
//		  -0.5f,  0.5f, 0.5f,
//		  // Segundo triângulo
//		  // Posições
//		  -0.5f,  0.5f, 0.5f,
//		  0.5f, -0.5f, 0.5f,
//		  0.5f,  0.5f, 0.5f,
//		  // ************************************************
//		  //                       Z- (face #5)
//		  // ************************************************
//		  // Primeiro triângulo
//		  // Posições
//		  0.5f, -0.5f, -0.5f,
//		  -0.5f, -0.5f, -0.5f,
//		  0.5f,  0.5f, -0.5f,
//		  // Segundo triângulo
//		  // Posições
//		  0.5f,  0.5f, -0.5f,
//		  -0.5f, -0.5f, -0.5f,
//		  -0.5f,  0.5f, -0.5f
//	};
//
//	Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
//	View = glm::lookAt(
//		glm::vec3(0.0f, 0.0f, 5.0f),	// eye (posição da câmara).
//		glm::vec3(0.0f, 0.0f, 0.0f),	// center (para onde está a "olhar")
//		glm::vec3(0.0f, 1.0f, 0.0f)		// up
//	);
//	Model = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
//	glm::mat4 ModelViewProjection = Projection * View * Model;
//	};
//
//void display(void) {
//	static const GLfloat black[] = {
//		0.0f, 0.0f, 0.0f, 0.0f
//	};
//	// Limpa o buffer de cor
//	glClearBufferfv(GL_COLOR, 0, black);
//
//	glClear(GL_DEPTH_BUFFER_BIT);
//
//	// Atualiza os dados do Uniform
//	Model = glm::rotate(glm::mat4(1.0f), angle += 0.0002f, glm::vec3(1.0f, 1.0f, 0.0f));
//	glm::mat4 ModelViewProjection = Projection * View * Model;
//	GLint mvpId = glGetProgramResourceLocation(programa, GL_UNIFORM, "MVP");
//	glProgramUniformMatrix4fv(programa, mvpId, 1, GL_FALSE, glm::value_ptr(ModelViewProjection));
//
//	// Vincula (torna ativo) o VAO
//	glBindVertexArray(VAO);
//	// Envia comando para desenho de primitivas GL_TRIANGLES, que utilizará os dados do VAO vinculado.
//	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
//}