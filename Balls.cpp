#include"Balls.h"
#define STB_IMAGE_IMPLEMENTATION
#include <glm/gtc/matrix_transform.hpp> 
#include "stb_image.h"
#include "LoadShaders.h"
#include "Camera.h"

using namespace glm;
using namespace std;

void Balls::Read(const string objFilepath) {
	//Vertex Variables
	vector<fvec3> vertexPosition;
	vector<fvec2> vertexTexturesCoord;
	vector<fvec3> vertexNormal;

	//Vectors Variables para faces
	vector<GLint> vertexPositionIndicies;
	vector<GLint> vertexTextureCoordIndicies;
	vector<GLint> vertexNormalIndicies;

	//File Variables
	stringstream ss;
	ifstream in_file(objFilepath);
	string line = "";
	string prefix = "";

	//Vectores Auxiliares Temporarios - utilizado para obter os todos indices 1 por 1
	vec3 vec3_aux; //Vectores Auxiliares Temporarios
	vec2 vec2_aux; //Vectores Auxiliares Temporarios
	string nextFile; //Next file


	//Ver se pode abrir o file
	try {
		if (!in_file.is_open())
			throw runtime_error("Error opening the material file");
		// File opened successfully, continue processing
	}
	catch (const exception& e) {
		// Handle the exception
		cout << "Exception occurred: " << e.what() << endl;
	}

	while (getline(in_file, line)) { //read 1 line at time
		ss.str(line);
		ss >> prefix;
		if (prefix == "mtllib")
		{
			ss >> nextFile;
			Load(nextFile);
		}

		if (prefix == "v" || prefix == "vt" || prefix == "vn" || prefix == "f") {

			if (prefix == "v") { // Posição dos vertices

				ss >> vec3_aux.x >> vec3_aux.y >> vec3_aux.z; //Por em memória nas variaveis auxiliares
				vertexPosition.push_back(vec3_aux); //Guardar no vetor de posições de vertices
			}
			else if (prefix == "vt") { // Posição dos vertices das coordenadas

				ss >> vec2_aux.x >> vec2_aux.y; //Por em memória nas variaveis auxiliares
				vertexTexturesCoord.push_back(vec2_aux); //Guardar no vetor de posições de vertices das coordenadas
			}
			else if (prefix == "vn") {
				ss >> vec3_aux.x >> vec3_aux.y >> vec3_aux.z; //Por em memória nas variaveis auxiliares
				vertexNormal.push_back(vec3_aux); //Guardar no vetor de posições de vertices das normais
			}
			else if (prefix == "f") {
				for (int a = 0; a < 3; a++)
				{
					string data;
					ss >> data;
					istringstream dss(data);

					string index;
					getline(dss, index, '/');
					int pindex = stoi(index) - 1; //Por em memória nas variaveis auxiliares referente a vertices

					getline(dss, index, '/');
					int tcindex = stoi(index) - 1; //Por em memória nas variaveis auxiliares referente a texturas

					getline(dss, index, '/');
					int nindex = stoi(index) - 1; //Por em memória nas variaveis auxiliares referente a normais


					vertex_positions.push_back(vertexPosition[pindex]); //Guardar no vetor de posições de vertices
					vertex_textures_coords.push_back(vertexTexturesCoord[tcindex]); //Guardar no vetor de posições de vertices das texturas
					vertex_normals.push_back(vertexNormal[nindex]); //Guardar no vetor de posições de vertices das normais
				}
			}
		}
		ss.clear();
	}

	// Questões de debugs
	cout << vertexPosition.size() << endl;
	cout << vertexTexturesCoord.size() << endl;
	cout << vertexNormal.size() << endl;

	cout << vertex_positions.size() << endl;
	cout << vertex_textures_coords.size() << endl;
	cout << vertex_normals.size() << endl;
	in_file.close();
}

void Balls::Load(string fileName) {
	//Ler o ficheiro (material) : Variaveis
	stringstream ss;
	string fileNameTemp = "PoolBalls/" + fileName;
	ifstream in_file(fileNameTemp);
	string line = "";
	string prefix = "";
	vec3 vec3_aux;
	float ns;
	string nextFile;

	//Ver se pode abrir o file
	try
	{
		if (!in_file.is_open())
		{
			throw runtime_error("Error opening the material file");
		}
		// File opened successfully, continue processing
	}
	catch (const exception& e)
	{
		// Handle the exception
		cout << "Exception occurred: " << e.what() << endl;
	}

	while (getline(in_file, line))
	{
		ss.str(line);
		ss >> prefix;

		//Verificar se a linha é relevante ou nao conforme o prefixo 
		if (prefix == "Ns" || prefix == "Ka" || prefix == "Kd" || prefix == "Ks" || prefix == "map_Kd")
		{
			if (prefix == "map_Kd") //Verifica o nome do ficheiro da textura
			{
				ss >> nextFile;
				Texture(nextFile); //Aplica e vai com o ficheiro da textura
			}
			else if (prefix == "Ns") // Expoente especular
			{
				ss >> ns;
				Ns = ns; //Guardar o valor do brilho na variavel de brilho
			}
			else if (prefix == "Ka") //Ambiente
			{
				ss >> vec3_aux.x >> vec3_aux.y >> vec3_aux.z; //Por em memória nas variaveis auxiliares referente a vertices
				ka = vec3_aux; //Guardar no vetor da luz ambiente para a bola
			}
			else if (prefix == "Kd") //Difusa
			{
				ss >> vec3_aux.x >> vec3_aux.y >> vec3_aux.z; //Por em memória nas variaveis auxiliares referente a vertices
				kd = vec3_aux; //Guardar no vetor da luz difusa para a bola
			}
			else if (prefix == "Ks") //Especular
			{
				ss >> vec3_aux.x >> vec3_aux.y >> vec3_aux.z; //Por em memória nas variaveis auxiliares referente a vertices
				ks = vec3_aux; //Guardar no vetor da luz especular para a bola
			}
		}
		ss.clear();
	}

	in_file.close();


}

void  Balls::Texture(const string textureFile)
{
	///--------   Textura    ---------
	GLuint textureName = 0;
	string file = textureFile;
	string fileTemp = "PoolBalls/" + file;
	// Gera um nome de textura
	glGenTextures(1, &textureName); //Gera um nome para a textura.

	// Ativa a Unidade de Textura #0
	// A Unidade de Textura 0 está ativa por defeito.
	// Só uma Unidade de Textura pode estar ativa.
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, textureName); //Dá bind da textura que foi criada e ativada para uma textura 2D

	// Define os parâmetros de filtragem (wrapping e ajuste de tamanho)
	// para a textura que está vinculada ao target GL_TEXTURE_CUBE_MAP da Unidade de Textura ativa.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Ativa a inversão vertical da imagem, aquando da sua leitura para memória.
	stbi_set_flip_vertically_on_load(true);

	// Leitura/descompressão do ficheiro com imagem de textura
	int width, height, nChannels;
	unsigned char* imageData = stbi_load(fileTemp.c_str(), &width, &height, &nChannels, 0);
	if (imageData) {
		// Carrega os dados da imagem para o Objeto de Textura vinculado ao target da face
		glTexImage2D(GL_TEXTURE_2D,
			0,					// Nível do Mipmap
			GL_RGB,				// Formato interno do OpenGL
			width, height,		// width, height
			0,					// border
			nChannels == 4 ? GL_RGBA : GL_RGB,	// Formato da imagem
			GL_UNSIGNED_BYTE,	// Tipos dos dados da imagem
			imageData);			// Apontador para os dados da imagem de textura

		// Gera o Mipmap para essa textura
		glGenerateMipmap(GL_TEXTURE_2D);

		// Liberta a imagem da memória do CPU
		stbi_image_free(imageData);
	}
	else {
		cout << "Error loading texture!" << endl;
	}

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		cout << "OpenGL Error: " << error << endl;
	}
}

GLuint Balls::Send(void) {
	GLfloat BindPos[24192 * 3]; //Criação de variavel para a posição dos vetores de posição  4034 * 3 * 2 * 3
	GLfloat BindN[24192 * 3]; //Criação de variavel para a posição dos vetores de posição das normais  4034 * 3 * 2 * 3
	GLfloat BindTex[24192 * 2]; //Criação de variavel para a posição dos vetores de posição das texturas  4034 * 3 * 2 * 3

	for (int i = 0; i < vertex_positions.size(); i++) {

		//Vertices
		BindPos[i * 3] = vertex_positions[i].x;
		BindPos[i * 3 + 1] = vertex_positions[i].y;
		BindPos[i * 3 + 2] = vertex_positions[i].z;
		
		//Normais
		BindN[i * 3] = vertex_normals[i].x;
		BindN[i * 3 + 1] = vertex_normals[i].y;
		BindN[i * 3 + 2] = vertex_normals[i].z;

		//Coordenadas de Texture
		BindTex[i * 2] = vertex_textures_coords[i].x;
		BindTex[i * 2 + 1] = vertex_textures_coords[i].y;

		//cout << "Current position: " << currentPosition << endl;
	}

	glGenVertexArrays(1, &VAO);// Gerar nomes para VAOs.
	glBindVertexArray(VAO);// Faz bind do VAO

	//Guardar a informação no buffer
	glGenBuffers(3, Buffers);// Gera 'NumBuffers' nomes para VBOs.

	for (int i = 0; i < 3 ; i++) {
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[i]);
		if (i == 0)
			glBufferStorage(GL_ARRAY_BUFFER, sizeof(BindPos), BindPos, 0);  //Info dos vertices - Inicializa o VBO (que está ativo) com dados imutáveis.
		if (i == 1)
			glBufferStorage(GL_ARRAY_BUFFER, sizeof(BindTex), BindTex, 0); //Info das posições das texturas - Inicializa o VBO (que está ativo) com dados imutáveis.
		if (i == 2)
			glBufferStorage(GL_ARRAY_BUFFER, sizeof(BindN), BindN, 0); //Info das normais - Inicializa o VBO (que está ativo) com dados imutáveis.
	}



	ShaderInfo shaders[] = { 
		{ GL_VERTEX_SHADER,"Balls.vert" },
		{ GL_FRAGMENT_SHADER, "Balls.frag" },
		{ GL_NONE, NULL } 
	};  //GL_None marca o final da lista de shader info
	
	programa = LoadShaders(shaders);  //Load destes shaders que foram carregados, Balls.vert e Balls.frag
	this->programa = programa;
	glUseProgram(programa);

	//Posição no shader (ponteiro da variavel do shader)
	GLuint coordsid = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "vPosition");      // obtém a localização do atributo 'vposition' no 'programa'.
	GLuint texid = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "vTexture");          // obtém a localização do atributo 'vtexture' no 'programa'.
	GLuint normalid = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "vNormal"); // obtém a localização do atributo 'vnormal' no 'programa'.

	// Questões de debug
	cout << coordsid << endl << texid << endl << normalid << endl;

	//Fixa um buffer e atribui as coordenadas das posições dos vertices do shader
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glVertexAttribPointer(coordsid, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//Fixa um buffer e atribui as coordenadas das posições dos vertices da textura do shader
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
	glVertexAttribPointer(texid, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	//Fixa um buffer e atribui as coordenadas das posições dos vertices das normais do shader
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[2]);
	glVertexAttribPointer(normalid, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//Verifica se tem erro ou não
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		cout << "OpenGL Error: " << error << endl;                           // da bind no 1º mas n da nem no 2 nem no 3
	}
	
	//habitita o atributo com localização 'coordsid', 'textid', normalid para o vao ativo.
	glEnableVertexAttribArray(coordsid);
	glEnableVertexAttribArray(texid);
	glEnableVertexAttribArray(normalid);

	GLint textureid = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "texSampler");
	glProgramUniform1i(programa, textureid, 0);

	return programa;
}

void Balls::Draw(vec3 position, vec3 orientation) {
	
	Camera::GetInstance()->Update(); //Dá update á camera e aos valores da camera

	mat4 tempball = ball;
	tempball = translate(tempball, position);

	//Orientation é o pitch, yaw, roll em graus
	tempball = rotate(tempball, radians(orientation.x), vec3(1, 0, 0)); //pitch
	tempball = rotate(tempball, radians(orientation.y), vec3(0, 1, 0)); //yaw
	tempball = rotate(tempball, radians(orientation.z), vec3(0, 0, 1)); //roll

	//Fixa um buffer e atribui ao shader o valor do model
	GLint modelId = glGetProgramResourceLocation(programa, GL_UNIFORM, "Model");
	glProgramUniformMatrix4fv(programa, modelId, 1, GL_FALSE, value_ptr(tempball));


	//Fixa um buffer e atribui ao shader o valor do model view (view * model)
	mat4 modelView = Camera::GetInstance()->view * tempball;
	GLint modelViewId = glGetProgramResourceLocation(programa, GL_UNIFORM, "ModelView");
	glProgramUniformMatrix4fv(programa, modelViewId, 1, GL_FALSE, value_ptr(modelView));

	//Fixa um buffer e atribui ao shader o valor da matriz normal da model view
	mat3 normalMatrix = inverseTranspose(mat3(modelView));
	GLint normalMatrixId = glGetProgramResourceLocation(programa, GL_UNIFORM, "NormalMatrix");
	glProgramUniformMatrix4fv(programa, normalMatrixId, 1, GL_FALSE, value_ptr(normalMatrix));

	//Fixa um buffer e atribui ao shader o valor da view
	GLint viewID = glGetProgramResourceLocation(programa, GL_UNIFORM, "View");
	glProgramUniformMatrix4fv(programa, viewID, 1, GL_FALSE, value_ptr(Camera::GetInstance()->view));

	//Fixa um buffer e atribui ao shader o valor da projection
	GLint projectionId = glGetProgramResourceLocation(programa, GL_UNIFORM, "Projection");
	glProgramUniformMatrix4fv(programa, projectionId, 1, GL_FALSE, value_ptr(Camera::GetInstance()->projection));

	//Dá bind do vertex array object
	glBindVertexArray(VAO);

	// Envia comando para desenho de primitivas GL_TRIANGLES, que utilizará os dados do VAO vinculado.
	glDrawArrays(GL_TRIANGLES, 0, vertex_positions.size());
	// glDrawElements(GL_TRIANGLES, NumIndices, GL_UNSIGNED_INT, (void*)0); 
}

