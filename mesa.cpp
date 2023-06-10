#include"mesa.h"

#define WIDTH 1280
#define HEIGTH 720

using namespace std;
GLuint VAO;
GLuint Buffer;

GLuint programa;

glm::mat4 Model, View, Projection;
GLfloat angle = 0.0f;

void print_gl_info(void) {
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	cout << "\nOpenGL version " << major << '.' << minor << endl;

	const GLubyte* glversion = glGetString(GL_VERSION);
	const GLubyte* glvendor = glGetString(GL_VENDOR);
	const GLubyte* glrenderer = glGetString(GL_RENDERER);
	cout << "\nVersion:  " << glversion << endl <<
		"Vendor:   " << glvendor << endl <<
		"Renderer: " << glrenderer << endl;

	cout << "\nSupported GLSL versions:\n";
	const GLubyte* glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	cout << "Higher supported version:\n\t" << glslversion << endl;
	GLint numglslversions;
	cout << "Other supported versions:\n";
	glGetIntegerv(GL_NUM_SHADING_LANGUAGE_VERSIONS, &numglslversions);
	for (int n = 0; n < numglslversions; n++) {
		cout << '\t' << glGetStringi(GL_SHADING_LANGUAGE_VERSION, n) << endl;
	}
}

void print_error(int error, const char* description) {
	cout << description << endl;
}

GLuint Mesa::Send(void) {
	GLfloat BindPos[NumVertices * 4];

	for (int i = 0; i < NumVertices * 3; i++) {
		//Vertices
		BindPos[i] = vertices[i];
		BindPos[i + 1] = vertices[i];
		BindPos[i + 2] = vertices[i];
	}

	glGenVertexArrays(1, &VAO);// Gerar nomes para VAOs.
	glBindVertexArray(VAO);// Faz bind do VAO

	//Guardar a informação no buffer
	glGenBuffers(1, &Buffer);// Gera 'NumBuffers' nomes para VBOs.

	glBindBuffer(GL_ARRAY_BUFFER, Buffer);
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(BindPos), BindPos, 0);  //Info dos vertices - Inicializa o VBO (que está ativo) com dados imutáveis.

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER,"Balls.vert" },
		{ GL_FRAGMENT_SHADER, "Balls.frag" },
		{ GL_NONE, NULL }
	};  //GL_None marca o final da lista de shader info

	programa = LoadShaders(shaders);
	this->programa = programa;
	glUseProgram(programa);

	//Posição no shader (ponteiro da variavel do shader)
	GLuint coordsid = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "vPosition");      // obtém a localização do atributo 'vposition' no 'programa'.
	
	glBindBuffer(GL_ARRAY_BUFFER, Buffer);
	glVertexAttribPointer(coordsid, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cout << "OpenGL Error: " << error << std::endl;                           // da bind no 1º mas n da nem no 2 nem no 3
	}

	//habitita o atributo com localização 'coordsid', 'textid', normalid para o vao ativo.
	glEnableVertexAttribArray(coordsid);

	GLint textureid = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "texSampler");
	glProgramUniform1i(programa, textureid, 0);

	return programa;
}

void Mesa::Draw(glm::vec3 position, glm::vec3 orientation) {
	Camera::GetInstance()->Update();

	glm::mat4 tempmesa = mesa;
	tempmesa = glm::translate(tempmesa, position);

	//Orientation é o pitch, yaw, roll em graus
	tempmesa = rotate(tempmesa, glm::radians(orientation.x), glm::vec3(1, 0, 0)); //pitch
	tempmesa = rotate(tempmesa, glm::radians(orientation.y), glm::vec3(0, 1, 0)); //yaw
	tempmesa = rotate(tempmesa, glm::radians(orientation.z), glm::vec3(0, 0, 1)); //roll

	GLint modelId = glGetProgramResourceLocation(programa, GL_UNIFORM, "Model");
	glProgramUniformMatrix4fv(programa, modelId, 1, GL_FALSE, glm::value_ptr(Model));

	glm::mat4 modelView = Camera::GetInstance()->view * Model;
	GLint modelViewId = glGetProgramResourceLocation(programa, GL_UNIFORM, "ModelView");
	glProgramUniformMatrix4fv(programa, modelViewId, 1, GL_FALSE, glm::value_ptr(modelView));

	glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(modelView));
	GLint normalMatrixId = glGetProgramResourceLocation(programa, GL_UNIFORM, "NormalMatrix");
	glProgramUniformMatrix4fv(programa, normalMatrixId, 1, GL_FALSE, glm::value_ptr(normalMatrix));

	GLint viewID = glGetProgramResourceLocation(programa, GL_UNIFORM, "View");
	glProgramUniformMatrix4fv(programa, viewID, 1, GL_FALSE, glm::value_ptr(Camera::GetInstance()->view));
	GLint projectionId = glGetProgramResourceLocation(programa, GL_UNIFORM, "Projection");
	glProgramUniformMatrix4fv(programa, projectionId, 1, GL_FALSE, glm::value_ptr(Camera::GetInstance()->projection));

	glBindVertexArray(VAO);

	// Envia comando para desenho de primitivas GL_TRIANGLES, que utilizará os dados do VAO vinculado.
	glDrawArrays(GL_TRIANGLES, 0, NumVertices * 3);
	// glDrawElements(GL_TRIANGLES, NumIndices, GL_UNSIGNED_INT, (void*)0); 
};