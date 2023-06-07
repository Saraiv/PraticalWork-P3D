#include"Balls.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void Balls::Read(const std::string objFilepath){
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

	GLint glint_aux = 0; //Vectores Auxiliares Temporarios - utilizado para obter os todos indices 1 por 1
	glm::vec3 vec3_aux; //Vectores Auxiliares Temporarios
	glm::vec2 vec3_aux_v2; //Vectores Auxiliares Temporarios
	std::string nextFile; //Next file


	//Ver se pode abrir o file
	try{
		if (!in_file.is_open())
			throw std::runtime_error("Error opening the material file");
		// File opened successfully, continue processing
	}
	catch (const std::exception& e){
		// Handle the exception
		std::cout << "Exception occurred: " << e.what() << std::endl;
	}

	while (getline(in_file, line)){ //read 1 line at time
		ss.str(line);
		ss >> prefix;
		if (prefix == "mtllib")
			ss >> nextFile;
		if (prefix == "v" || prefix == "vt" || prefix == "vn" || prefix == "f"){
			
			if (prefix == "v"){ // vertex position
			
				ss >> vec3_aux.x >> vec3_aux.y >> vec3_aux.z; //put in temporary variable
				vertexPosition.push_back(vec3_aux); //store on vertexPosition array
			}
			else if (prefix == "vt"){
			
				ss >> vec3_aux_v2.x >> vec3_aux_v2.y;
				vertexTexturesCoord.push_back(glm::vec3(vec3_aux_v2, 0.0f));
			}
			else if (prefix == "vn"){
				ss >> vec3_aux.x >> vec3_aux.y >> vec3_aux.z;
				vertexNormal.push_back(vec3_aux);
			}
			else if (prefix == "f"){
				int counter = 0;

				while (ss >> glint_aux)
				{
					if (counter == 0) //push indices to correct arrays
						vertexPositionIndicies.push_back(glint_aux);
					else if (counter == 1)
						vertexTextureCoordIndicies.push_back(glint_aux);
					else if (counter == 2)
						vertexNormalIndicies.push_back(glint_aux);

					if (ss.peek() == '/'){ //verificar se e este caracter, se for ignorar
					
						++counter;
						ss.ignore(1, '/');
					}
					else if (ss.peek() == ' '){
						++counter;
						ss.ignore(1, ' ');
					}

					if (counter > 2) //reset the counter
						counter = 0;
				}
			}
		}
		ss.clear();
	}

	in_file.close();

	//load all indices
	for (size_t i = 0; i < vertexPositionIndicies.size(); ++i)
	{
		vertex_positions.push_back(vertexPosition[vertexPositionIndicies[i] - 1]); // -1 pq e array e comeca no 0... senao deforma td
		vertex_textures_coords.push_back(vertexTexturesCoord[vertexTextureCoordIndicies[i] - 1]);
		vertex_normals.push_back(vertexNormal[vertexNormalIndicies[i] - 1]);
	}

	Load(nextFile);
}

void Balls::Load(std::string fileName){
	//Ler o ficheiro (material) : Variaveis
	std::stringstream ss;
	std::string fileNameTemp = "poolBalls/" + fileName;
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
		if (prefix == "Ns" || prefix == "Ka" || prefix == "Kd" || prefix ==  "Ks" || prefix == "map_Kd")
		{
			if (prefix == "map_Kd")
				ss >> nextFile;
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

	///--------   Textura    ---------
	GLuint textureName = 0;
	std::string file = nextFile.c_str();
	std::string fileTemp = "poolBalls/" + file;
	// Gera um nome de textura
	glGenTextures(1, &textureName);

	// Ativa a Unidade de Textura #0
	// A Unidade de Textura 0 está ativa por defeito.
	// Só uma Unidade de Textura pode estar ativa.
	glActiveTexture(GL_TEXTURE0);

	// Vincula esse nome de textura ao target GL_TEXTURE_CUBE_MAP da Unidade de Textura ativa.
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureName);

	// Define os parâmetros de filtragem (wrapping e ajuste de tamanho)
	// para a textura que está vinculada ao target GL_TEXTURE_CUBE_MAP da Unidade de Textura ativa.
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

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
}

void Balls::Send() {
	glGenVertexArrays(NumeroDeVAOs, VAO);// Gerar nomes para VAOs.
	glBindVertexArray(VAO[0]);// Faz bind do VAO

	//Guardar a informação no buffer
	glGenBuffers(NumBuffers, Buffers);// Gera 'NumBuffers' nomes para VBOs.
	for (int i = 0; i < NumBuffers; i++) {
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[i]);
		if (i == 0)
			glBufferStorage(GL_ARRAY_BUFFER, vertex_positions.size() * sizeof(glm::vec3), vertex_positions.data(), 0);  //Info dos vertices - Inicializa o VBO (que está ativo) com dados imutáveis.
		if (i == 1)
			glBufferStorage(GL_ARRAY_BUFFER, vertex_textures_coords.size() * sizeof(glm::vec2), vertex_textures_coords.data(), 0); //Info das posições das texturas - Inicializa o VBO (que está ativo) com dados imutáveis.
		if (i == 2)
			glBufferStorage(GL_ARRAY_BUFFER, vertex_normals.size() * sizeof(glm::vec3), vertex_normals.data(), 0); //Info das normais - Inicializa o VBO (que está ativo) com dados imutáveis.
	}

	// Shaders - Criar/Indicar os shaders que serão utilizados
	//ShaderInfo  shaders[] = {
	//	{ GL_VERTEX_SHADER,   "shaders/iron_man.vert" },
	//	{ GL_FRAGMENT_SHADER, "shaders/iron_man.frag" },
	//	{ GL_NONE, NULL }
	//};

	//programa = LoadShaders(shaders); //Carregar Shaders
	//if (!programa) exit(EXIT_FAILURE);
	//glUseProgram(programa);
	// 
	// Ligar Atributos aos Shaders
	//GLint coordsId = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "vPosition");      // Obtém a localização do atributo 'vPosition' no 'programa'.
	//GLint texId = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "vTexture");          // Obtém a localização do atributo 'vTexture' no 'programa'.
	//GLint normalId = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "vNormal");        // Obtém a localização do atributo 'vNormal' no 'programa'.

	//for (int i = 0; i < NumBuffers; i++) {
	//	glBindBuffer(GL_ARRAY_BUFFER, Buffers[i]);// Ativa o VBO 'Buffer'.
	//	if (i == 0)
	//		glVertexAttribPointer(coordsId, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);				//Especifica como é que a informação do atributo 'coordsId' deve ser interpretada
	//	if (i == 1)
	//		glVertexAttribPointer(texId, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);					//Especifica como é que a informação do atributo 'coordsId' deve ser interpretada
	//	if (i == 2)
	//		glVertexAttribPointer(normalId, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);				//Especifica como é que a informação do atributo 'coordsId' deve ser interpretada
	//}

	//Habitita o atributo com localização 'coordsId', 'textId', normalId para o VAO ativo.
	//glEnableVertexAttribArray(coordsId);
	//glEnableVertexAttribArray(texId);
	//glEnableVertexAttribArray(normalId);

	//Definit a View Port
	glViewport(0, 0, WIDTH, HEIGHT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Balls::Draw(glm::vec3 position, glm::vec3 orientation) {
	//Verificar se a luz ambiente esta on e atribuir valores
	lightMode1 == true ? glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "ambientLight.ambient"), 1, glm::value_ptr(glm::vec3(2.1, 2.1, 2.1))) :
		glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "ambientLight.ambient"), 1, glm::value_ptr(glm::vec3(0, 0, 0)));
	lightMode2 == true ? getDirectionalLightActive() : getDirectionalLightInactive(); //Ver se a luz direcional esta on e atribuir valores
	lightMode3 == true ? getPontualLightActive() : getPontualLightInactive(); //Ver se a luz pontual esta on e atribuir valores
	lightMode4 == true ? getSpotLightActive() : getSpotLightInactive(); //Ver se a luz conica esta on e atribuir valores

	//Propriedades material
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.emissive"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0))); //esta a mais,apagar
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.ambient"), 1, glm::value_ptr(ka));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.diffuse"), 1, glm::value_ptr(kd));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.specular"), 1, glm::value_ptr(ks));
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.shininess"), Ns);

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

	//Ativar e desativar o efeito no modelo
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "effectModel"), deformeffect);

	//Sent time to .vert
	float time = float(glfwGetTime());
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "time"), time); //coloca deformacao a ser efetuada atraves do tempo

	// Vincula (torna ativo) o VAO
	glBindVertexArray(VAO[0]);

	//Envia comando para desenho de primitivas GL_TRIANGLES, que utilizará os dados do VAO vinculado.
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

//lights functions
void Balls::getDirectionalLightActive()
{
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "directionalLight.direction"), 1, glm::value_ptr(glm::vec3(1.0, 0.0, 0.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "directionalLight.ambient"), 1, glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "directionalLight.diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "directionalLight.specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
}

void Balls::getDirectionalLightInactive()
{
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "directionalLight.direction"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "directionalLight.ambient"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "directionalLight.diffuse"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "directionalLight.specular"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
}

void Balls::getPontualLightActive()
{
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight.position"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 5.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight.ambient"), 1, glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight.diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight.specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight.constant"), 1.0f);
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight.linear"), 0.06f);
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight.quadratic"), 0.02f);
}

void Balls::getPontualLightInactive()
{
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight.position"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight.ambient"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight.diffuse"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight.specular"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight.constant"), 0.0f);
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight.linear"), 0.00f);
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight.quadratic"), 0.00f);
}

void Balls::getSpotLightActive()
{
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.position"), 1, glm::value_ptr(glm::vec3(0, 10.0, 12.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.ambient"), 1, glm::value_ptr(glm::vec3(2.0, 2.0, 2.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.diffuse"), 1, glm::value_ptr(glm::vec3(15.0, 15.0, 15.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.specular"), 1, glm::value_ptr(glm::vec3(15.0, 15.0, 15.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.spotDirection"), 1, glm::value_ptr(glm::vec3(0.0, 3.0, 0.0)));
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.spotCutoff"), 0.5f);
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.spotExponent"), 0.5f);
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.constant"), 1.0f);
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.linear"), 0.06f);
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.quadratic"), 0.02f);
}

void Balls::getSpotLightInactive()
{
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.position"), 1, glm::value_ptr(glm::vec3(0, 0, 0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.ambient"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.diffuse"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.specular"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.spotDirection"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
}
