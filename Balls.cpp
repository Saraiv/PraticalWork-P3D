#include"Balls.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "LoadShaders.h"




void Balls::Read(const std::string objFilepath) {
	//Vertex Variables
	std::vector<glm::fvec3> vertexPosition;
	std::vector<glm::fvec2> vertexTexturesCoord;
	std::vector<glm::fvec3> vertexNormal;

	//Vectors Variables para faces
	std::vector<GLint> vertexPositionIndicies;
	std::vector<GLint> vertexTextureCoordIndicies;
	std::vector<GLint> vertexNormalIndicies;

	//File Variables
	std::stringstream ss;
	std::ifstream in_file(objFilepath);
	std::string line = "";
	std::string prefix = "";

	//Vectores Auxiliares Temporarios - utilizado para obter os todos indices 1 por 1
	glm::vec3 vec3_aux; //Vectores Auxiliares Temporarios
	glm::vec2 vec2_aux; //Vectores Auxiliares Temporarios
	std::string nextFile; //Next file


	//Ver se pode abrir o file
	try {
		if (!in_file.is_open())
			throw std::runtime_error("Error opening the material file");
		// File opened successfully, continue processing
	}
	catch (const std::exception& e) {
		// Handle the exception
		std::cout << "Exception occurred: " << e.what() << std::endl;
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

			if (prefix == "v") { // vertex position

				ss >> vec3_aux.x >> vec3_aux.y >> vec3_aux.z; //put in temporary variable
				vertexPosition.push_back(vec3_aux); //store on vertexPosition array
			}
			else if (prefix == "vt") {

				ss >> vec2_aux.x >> vec2_aux.y;
				vertexTexturesCoord.push_back(vec2_aux);
			}
			else if (prefix == "vn") {
				ss >> vec3_aux.x >> vec3_aux.y >> vec3_aux.z;
				vertexNormal.push_back(vec3_aux);
			}
			else if (prefix == "f") {
				for (int a = 0; a < 3; a++)
				{
					std::string data;
					ss >> data;
					std::istringstream dss(data);

					std::string index;
					getline(dss, index, '/');
					int pindex = std::stoi(index) - 1;

					getline(dss, index, '/');
					int tcindex = std::stoi(index) - 1;

					getline(dss, index, '/');
					int nindex = std::stoi(index) - 1;


					vertex_positions.push_back(vertexPosition[pindex]);
					vertex_textures_coords.push_back(vertexTexturesCoord[tcindex]);
					vertex_normals.push_back(vertexNormal[nindex]);
				}
			}
		}
		ss.clear();
	}
	std::cout << vertexPosition.size() << std::endl;
	std::cout << vertexTexturesCoord.size() << std::endl;
	std::cout << vertexNormal.size() << std::endl;

	std::cout << vertex_positions.size() << std::endl;
	std::cout << vertex_textures_coords.size() << std::endl;
	std::cout << vertex_normals.size() << std::endl;
	in_file.close();
}

void Balls::Load(std::string fileName) {
	//Ler o ficheiro (material) : Variaveis
	std::stringstream ss;
	std::string fileNameTemp = "PoolBalls/" + fileName;
	std::ifstream in_file(fileNameTemp);
	std::string line = "";
	std::string prefix = "";
	glm::vec3 vec3_aux;
	float ns;
	std::string nextFile;

	//Ver se pode abrir o file
	try
	{
		if (!in_file.is_open())
		{
			throw std::runtime_error("Error opening the material file");
		}
		// File opened successfully, continue processing
	}
	catch (const std::exception& e)
	{
		// Handle the exception
		std::cout << "Exception occurred: " << e.what() << std::endl;
	}

	while (std::getline(in_file, line))
	{

		ss.str(line);
		ss >> prefix;

		//Verificar se a linha é relevante ou nao conforme o prefixo 
		if (prefix == "Ns" || prefix == "Ka" || prefix == "Kd" || prefix == "Ks" || prefix == "map_Kd")
		{
			if (prefix == "map_Kd")
			{
				ss >> nextFile;
				Texture(nextFile);
			}
			else if (prefix == "Ns")
			{
				ss >> ns;
				Ns = ns;
			}
			else if (prefix == "Ka")
			{
				ss >> vec3_aux.x >> vec3_aux.y >> vec3_aux.z;
				ka = vec3_aux;
			}
			else if (prefix == "Kd")
			{
				ss >> vec3_aux.x >> vec3_aux.y >> vec3_aux.z;
				kd = vec3_aux;
			}
			else if (prefix == "Ks")
			{
				ss >> vec3_aux.x >> vec3_aux.y >> vec3_aux.z;
				ks = vec3_aux;
			}
		}
		ss.clear();
	}

	in_file.close();


}

void  Balls::Texture(const std::string textureFile)
{
	///--------   Textura    ---------
	GLuint textureName = 0;
	std::string file = textureFile;
	std::string fileTemp = "PoolBalls/" + file;
	// Gera um nome de textura
	glGenTextures(1, &textureName);

	// Ativa a Unidade de Textura #0
	// A Unidade de Textura 0 está ativa por defeito.
	// Só uma Unidade de Textura pode estar ativa.
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, textureName);

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
		std::cout << "Error loading texture!" << std::endl;
	}

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cout << "OpenGL Error: " << error << std::endl;
	}
}

GLuint Balls::Send() {

	GLfloat BindPos[24192 * 3];
	GLfloat BindN[24192 * 3];
	GLfloat BindTex[24192 * 2];

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

		//std::cout << "Current position: " << currentPosition << std::endl;
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
	
	programa = LoadShaders(shaders); 
	//if (!programa) exit(EXIT_FAILURE);
	glUseProgram(programa);

	//Posição no shader (ponteiro da variavel do shader)
	GLuint coordsid = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "vPosition");      // obtém a localização do atributo 'vposition' no 'programa'.
	GLuint texid = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "vTexture");          // obtém a localização do atributo 'vtexture' no 'programa'.
	GLuint normalid = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "vNormal"); // obtém a localização do atributo 'vnormal' no 'programa'.

	std::cout << coordsid << std::endl << texid << std::endl << normalid << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glVertexAttribPointer(coordsid, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
	glVertexAttribPointer(texid, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[2]);
	glVertexAttribPointer(normalid, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	
	//habitita o atributo com localização 'coordsid', 'textid', normalid para o vao ativo.
	glEnableVertexAttribArray(coordsid);
	glEnableVertexAttribArray(texid);
	glEnableVertexAttribArray(normalid);

	GLint textureid = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "texSampler");
	glProgramUniform1i(programa, textureid, 0);

	
	
	return programa;
}

void Balls::Draw(glm::vec3 position, glm::vec3 orientation) {
	////Verificar se a luz ambiente esta on e atribuir valores
	//lightMode1 == true ? glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "ambientLight.ambient"), 1, glm::value_ptr(glm::vec3(2.1, 2.1, 2.1))) :
	//	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "ambientLight.ambient"), 1, glm::value_ptr(glm::vec3(0, 0, 0)));
	//lightMode2 == true ? getDirectionalLightActive() : getDirectionalLightInactive(); //Ver se a luz direcional esta on e atribuir valores
	//lightMode3 == true ? getPontualLightActive() : getPontualLightInactive(); //Ver se a luz pontual esta on e atribuir valores
	//lightMode4 == true ? getSpotLightActive() : getSpotLightInactive(); //Ver se a luz conica esta on e atribuir valores

	////Propriedades material
	//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.emissive"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0))); //esta a mais,apagar
	//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.ambient"), 1, glm::value_ptr(ka));
	//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.diffuse"), 1, glm::value_ptr(kd));
	//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.specular"), 1, glm::value_ptr(ks));
	//glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.shininess"), Ns);

	//Atualiza camera
	mvp = poolTableWindow.Model(accumulatedRotationY);
	model = poolTableWindow.Projection(),
		projection = poolTableWindow.View(ZOOM),
		view = projection * view * model;

	GLint modelId = glGetProgramResourceLocation(programa, GL_UNIFORM, "Model");                //Atribui valor ao uniform Model
	glProgramUniformMatrix4fv(programa, modelId, 1, GL_FALSE, glm::value_ptr(model));

	GLint viewId = glGetProgramResourceLocation(programa, GL_UNIFORM, "View");        //Atribui valor ao uniform ModelView
	glProgramUniformMatrix4fv(programa, viewId, 1, GL_FALSE, glm::value_ptr(view));

	GLint projectionId = glGetProgramResourceLocation(programa, GL_UNIFORM, "Projection");      //Atribui valor ao uniform Projection
	glProgramUniformMatrix4fv(programa, projectionId, 1, GL_FALSE, glm::value_ptr(projection));

	GLint normalViewId = glGetProgramResourceLocation(programa, GL_UNIFORM, "NormalMatrix");    //Atribui valor ao uniform NormalMatrix
	glProgramUniformMatrix3fv(programa, normalViewId, 1, GL_FALSE, glm::value_ptr(normalMatrix));

	GLint texSamplerId = glGetProgramResourceLocation(programa, GL_UNIFORM, "texSampler");      //Atribui valor ao uniform textSamples
	glProgramUniform1i(programa, texSamplerId, 0);

	//Ativar e desativar o efeito no modelo
	//glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "effectModel"), deformeffect);

	//Sent time to .vert
	//float time = float(glfwGetTime());
	//glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "time"), time); //coloca deformacao a ser efetuada atraves do tempo

	// Vincula (torna ativo) o VAO
	glBindVertexArray(VAO);

	//Envia comando para desenho de primitivas GL_TRIANGLES, que utilizará os dados do VAO vinculado.
	glDrawArrays(GL_TRIANGLES, 0, vertex_positions.size());
}

