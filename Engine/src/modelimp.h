#ifndef MODELIMP_H
#define MODELIMP_H

#include <glm.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shader.h"
#include "mesh.h"
#include "entity2D.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "texture_importer.h"

using namespace std;

namespace Engine {
	class ENGINE_API ModelImp : public Entity2D{
	private:
		vector<Texture> _textures_loaded;
		vector<Mesh> _meshes;
		string _directory;
		//const string* _modelTexture;
		void LoadModel(string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

		//TextureImporter* _texImporter;

		Shader _shader;

		unsigned int TextureFromFile(const char* path, const string &directory,bool gamma);
	public:
		ModelImp(string path);
		~ModelImp();
		void Draw(Shader& shader);
	};
}

#endif