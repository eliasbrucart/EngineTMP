#include "modelimp.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
using namespace Engine;

//Pasar todo el codigo a una clase que se llame Model Loader y dejar esta para importar el modelo

ModelImp::ModelImp() {
	_path = "";
	_directory = "";
}

ModelImp::ModelImp(string path, const char* modelTexture, Shader& shader, Renderer* renderer) {
	_modelTexture = modelTexture;
	LoadModel(path);
	//_directory = directory;
	//_shader.SetTypeOfshape("type", 2);
	_shader = shader;
	_renderer = renderer;
	//_texImporter = new TextureImporter(modelTexture);
	//LoadTexture();
}

ModelImp::ModelImp(string path, Shader& shader, Renderer* renderer) {
	LoadModel(path);
	_shader = shader;
	_renderer = renderer;
	_texImporter = new TextureImporter();
}

ModelImp::~ModelImp() {
	if (_texImporter != NULL) {
		delete _texImporter;
		_texImporter = NULL;
	}
	if (!_meshes.empty()) {
		//for (auto mesh : _meshes) {
		//    if (mesh != NULL) {
		//        delete mesh;
		//        mesh = NULL;
		//    }
		//}
		_meshes.clear();
	}
}

void ModelImp::MoveModel(glm::vec3 direction) {
	for (int i = 0; i < _meshes.size(); i++) {
		_meshes[i].Translate(direction.x, direction.y, direction.z);
	}
}

void ModelImp::ScaleModel(float x, float y, float z) {
	for (int i = 0; i < _meshes.size(); i++) {
		if (x < 0 || y < 0 || z < 0) {
			x = 0; y = 0; z = 0;
		}
		_meshes[i].Scale(x, y, z);
	}

}

void ModelImp::RotateModelX(float x) {
	for (int i = 0; i < 1; i++) {
		_meshes[i].RotateX(x);
	}
}

void ModelImp::RotateModelY(float y) {
	for (int i = 0; i < _meshes.size(); i++) {
		_meshes[i].RotateY(y);
	}
}

void ModelImp::RotateModelZ(float z) {
	for (int i = 0; i < _meshes.size(); i++) {
		_meshes[i].RotateZ(z);
	}
}

Node* ModelImp::GetSceneNode() {
	return sceneNode;
}

void ModelImp::LoadModel(string path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
		return;
	}
	_directory = path.substr(0, path.find_last_of('/'));

	//crear el scene node
	//En el metodo ProcessNode pasarle el padre de tipo Node (nueva clase) y una matriz normalizada que luego sera traducida a la de la escena y asi poder setearsela.
	sceneNode = new Node();
	ProcessNode(scene->mRootNode, scene, sceneNode, glm::mat4(1.f));
	sceneNode->SetParent(NULL);

	//if(scene)
	//    ProcessNode(scene->mRootNode, scene, nullptr, nullptr);
}

void ModelImp::ProcessNode(aiNode* node, const aiScene* scene, Node* parent, glm::mat4 identMatrix) {
	Node* actualNode = new Node();
	string nameNode = node->mName.C_Str();

	//Importador que tiene en cuenta el pivote de rotacion de cada objeto en la escena
	if (nameNode.find("$AssimpFbx$") == -1 && node->mNumMeshes == 0 && identMatrix == glm::mat4(1.f)) {
		if (nameNode.find("RotationPivot") != -1 && nameNode.find("Inverse") == -1) {
			//Obtenemos la matriz del nodo raiz de la escena y la colocamos en nuestra matriz para luego setearla
			aiMatrix4x4 newMatrix = node->mTransformation;
	
			identMatrix[0][0] = (float)newMatrix.a1;
			identMatrix[0][1] = (float)newMatrix.b1;
			identMatrix[0][2] = (float)newMatrix.c1;
			identMatrix[0][3] = (float)newMatrix.d1;
			identMatrix[1][0] = (float)newMatrix.a2;
			identMatrix[1][1] = (float)newMatrix.b2;
			identMatrix[1][2] = (float)newMatrix.c2;
			identMatrix[1][3] = (float)newMatrix.d2;
			identMatrix[2][0] = (float)newMatrix.a3;
			identMatrix[2][1] = (float)newMatrix.b3;
			identMatrix[2][2] = (float)newMatrix.c3;
			identMatrix[2][3] = (float)newMatrix.d3;
			identMatrix[3][0] = (float)newMatrix.a4;
			identMatrix[3][1] = (float)newMatrix.b4;
			identMatrix[3][2] = (float)newMatrix.c4;
			identMatrix[3][3] = (float)newMatrix.d4;
	
		}
		if (nameNode.find("Pivot") == std::string::npos) {
			glm::mat4 m;
			aiMatrix4x4 newMatrix = node->mTransformation;

			//Si encontramos un nodo con el nombre Pivot, obtenemos su matriz y la multiplicamos por la matriz identidad que viene por defecto
			//Esto es para freezar las posiciones ya que es una escena y tenemos mas de un objeto
	
			m[0][0] = (float)newMatrix.a1;
			m[0][1] = (float)newMatrix.b1;
			m[0][2] = (float)newMatrix.c1;
			m[0][3] = (float)newMatrix.d1;
			m[1][0] = (float)newMatrix.a2;
			m[1][1] = (float)newMatrix.b2;
			m[1][2] = (float)newMatrix.c2;
			m[1][3] = (float)newMatrix.d2;
			m[2][0] = (float)newMatrix.a3;
			m[2][1] = (float)newMatrix.b3;
			m[2][2] = (float)newMatrix.c3;
			m[2][3] = (float)newMatrix.d3;
			m[3][0] = (float)newMatrix.a4;
			m[3][1] = (float)newMatrix.b4;
			m[3][2] = (float)newMatrix.c4;
			m[3][3] = (float)newMatrix.d4;
	
			identMatrix *= m;
		}
	
		actualNode->setMatrix(identMatrix); //modificar esto para hacer el correcto seteo de la matriz
	}
	else {
	
		//if (node->mNumMeshes > 0) {
		//	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		//		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		//		_meshes.push_back(ProcessMesh(mesh, scene)); //pusehar la ultima mesh encontrada
		//	}
		//}
	
		//Si ya se proceso el nodo y tiene mallas para procesar, las procesamos.
		if (node->mNumMeshes > 0) {
		    std::vector<Mesh> nodeMeshes;
		
		    for (int i = 0; i < node->mNumMeshes; i++) {
		        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		        nodeMeshes.push_back(ProcessMesh(mesh, scene));
		    }
			//Agregamos la malla al vector de mallas para ese nodo.
		    actualNode->SetMeshes(nodeMeshes);
		
		}
	}

	//if (nameNode.find("bspPlane") != -1) {
	//    //Crear un vector de node* para setear los planos;
	//}

	//std::vector<Node*> childrens;

	//Recorremos los hijos del nodo que estamos procesando
	for (int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene, actualNode, identMatrix);
	}

	//Creamos la jerarquia por nodos para cada uno de ellos.
	parent->SetChildren(actualNode);
	actualNode->SetName(nameNode);
	actualNode->SetParent(parent);


	//Entity2D* actualNode = nullptr;
	//Mesh* actualMesh = nullptr;
	//
	//if (parent == nullptr) { //Si no hay padre procesamos el nodo actual y agregamos como child una entity normalizada
	//    _rootNode = new Entity2D();
	//    actualNode = _rootNode;
	//
	//    //_rootNodeMesh = new Mesh();
	//    //actualMesh = actualNode;
	//
	//    std::cout << "No hay padre, agregando nodo raiz" << std::endl;
	//    //SetParent(_rootNode);
	//    AddChild(_rootNode);
	//    //actualMesh->AddChildMesh(_rootNodeMesh);
	//}
	//if(parent) { //Si hay padre hacemos el nodo actual hijo del padre.
	//    actualNode = new Entity2D();
	//    //actualMesh = new Mesh();
	//
	//    parent->AddChild(actualNode);
	//    //parentMesh->AddChildMesh(actualMesh);
	//    std::cout << "Hay padre, nodo actual hijo del padre" << std::endl;
	//    _rootNodeChildren.push_back(actualNode);
	//    //_rootNodeChildrenMesh.push_back(actualMesh);
	//}
	//
	//if (node->mNumMeshes > 0) {
	//    for (int i = 0; i < node->mNumMeshes; i++) {
	//        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
	//        if (parent == nullptr) {
	//            Mesh* nMesh = ProcessMesh(mesh, scene, _rootNode, actualNode);
	//            actualNode->AddChild(nMesh);
	//            //actualMesh->AddChild(nMesh);
	//            _rootNodeChildrenMesh.push_back(nMesh);
	//            _meshes.push_back(nMesh);
	//        }
	//        else {
	//            Mesh* nMesh = ProcessMesh(mesh, scene, parent, actualNode);
	//            actualNode->AddChild(nMesh);
	//            //actualMesh->AddChild(nMesh);
	//            //actualMesh->AddChild(nMesh);
	//            _rootNodeChildrenMesh.push_back(actualMesh);
	//            _meshes.push_back(nMesh);
	//        }
	//    }
	//}
	//
	//
	//std::cout << "Entro en ProcessNode!!!" << std::endl;
	////for (unsigned int i = 0; i < node->mNumMeshes; i++) {
	////    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
	////    _meshes.push_back(ProcessMesh(mesh, scene)); //pusehar la ultima mesh encontrada
	////}
	////
	//////procesar nodos para que se agrupen por jerarquia
	////
	//for (unsigned int i = 0; i < node->mNumChildren; i++) {
	//    ProcessNode(node->mChildren[i], scene, actualNode, actualMesh);
	//}
}

Mesh ModelImp::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		//Procesar las posiciones, normales y uvs de los vertices de cada una de la mesh
		//Necesitmaos un vector temporal para los datos de Assimp, eso se hace ya que Assimp tiene sus propios tipos de datos para vectores, matrices, etc.
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		//Aca hacemos lo mismo que en el paso anterior solo que con los datos de los vectores normales
		if (mesh->HasNormals())
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	//Procesar los indices que apuntan a cada mesh
	//Cada mesh contiene una matriz de caras, cada cara contiene vertices, que estos se refieren con sus indices
	//los indices indican en que orden dibujar los vertices para cada primitiva.
	//Y eso termina siendo una cara, una primitiva.

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}



	//Procesar material de la mesh
	//if (mesh->mMaterialIndex >= 0) {
	//    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	//    vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	//
	//    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	//    vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	//
	//    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	//}

	//_boundingVolume = GenerateAABB(_meshes, vertices);

	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuseM");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. specular maps
		vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "specularM");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		// 3. normal maps
		std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		// 4. height maps
		std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
	}

	std::cout << "Entro en ProcessMesh!!!" << std::endl;

	return Mesh(vertices, indices, textures, _shader, _renderer);

	//Hacer new de mesh para pasarle los datos de shader correctamente.
	//Averiguar por que el shader no se pasa bien al mesh para el dibujado.
	//delete newMesh;
}

vector<Texture> ModelImp::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) {
	vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < _textures_loaded.size(); j++) {
			if (std::strcmp(_textures_loaded[j].path.data(), str.C_Str()) == 0) {
				textures.push_back(_textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip) {
			Texture texture;
			//texture.id = TextureFromFile(str.C_Str(), this->_directory, false);
			texture.id = _texImporter->TextureFromFile(str.C_Str(), this->_directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			//texture.path = _modelTexture;
			textures.push_back(texture);
			_textures_loaded.push_back(texture);
		}
	}

	std::cout << "Entro en LoadMaterialTextures!!!" << std::endl;

	return textures;
}

//void ModelImp::SetModelPath(string path) {
//    _path = path;
//}
//
//void ModelImp::SetTexturePath(const char* texturePath) {
//    _directory = texturePath;
//}

void ModelImp::Draw(Shader& shader, Frustum frustum) {
	sceneNode->Draw(shader, frustum);
	//UpdateSelfAndChild();
	//UpdateModel();
	//UpdateVectors();
	//for (unsigned int i = 0; i < _meshes.size(); i++)
	//	_meshes[i].Draw(shader, frustum);
	//std::cout << "_meshes size: " << _meshes.size() << std::endl;
	//if (!_meshes.empty()) {
	//    for (auto mesh : _meshes) {
	//        //if (mesh != NULL)
	//        //{
	//            //if(_boundingVolume->IsOnFrustum(frustum, mesh))
	//                mesh.Draw(shader, frustum);
	//        //}
	//    }
	//}
}

unsigned int ModelImp::TextureFromFile(const char* path, string const& directory, bool gamma) {
	string filename = string(path);
	filename = directory + '/' + path;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void ModelImp::LoadTexture() {
	if (_texImporter) {
		_texImporter->LoadImage(_width, _height, _transparency);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texImporter->GetTexture());

		unsigned int textureDiffuseLoc = glGetUniformLocation(_shader.GetID(), "texture_diffuse1");
		glUniform1i(textureDiffuseLoc, _texImporter->GetTexture());

		glDisable(GL_TEXTURE_2D);
	}
}

unsigned int ModelImp::TextureModel(const char* texture) {
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(texture, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << texture << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}