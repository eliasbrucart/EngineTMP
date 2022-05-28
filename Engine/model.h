#ifndef MODELIMP_H
#define MODELIMP_H
#include "shader.h"
#include <vector>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "mesh.h"
#include "stb_image.h"
#include "export.h"
using namespace std;

namespace Engine {
	class ENGINE_API ModelImp {
	private:
		vector<Texture> _textures_loaded;
		vector<Mesh> _meshes;
		string directory;
		void LoadModel(string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
		unsigned int TextureFromFile(const char* path, const string& directory);
	public:
		ModelImp(string path);
		~ModelImp();
		void Draw(Shader& shader);
	};
}

#endif