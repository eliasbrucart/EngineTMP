#ifndef MODELIMP_H
#define MODELIMP_H

#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shader.h"
#include "mesh.h"
#include "entity2D.h"

#include <string>
#include <iostream>
#include <vector>
#include "mat4x4.hpp"

#include "texture_importer.h"
#include "node.h"

using namespace std;

namespace Engine {
	class ENGINE_API ModelImp{
	private:
		int _width = 0;
		int _height = 0;
		bool _transparency;
		vector<Texture> _textures_loaded;
		//vector<Mesh*> _meshes;
		string _path;
		const char* _modelTexture;
		string _directory;

		//std::vector<Entity2D*> _rootNodeChildren;
		//Entity2D* _rootNode; //Atributo para setear el nodo actual.

		//const string* _modelTexture;
		void LoadModel(string path);
		void ProcessNode(aiNode* node, const aiScene* scene, Node* parent, glm::mat4 identMatrix);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

		TextureImporter* _texImporter = NULL;

		Shader _shader;
		Renderer* _renderer;

		unsigned int TextureFromFile(const char* path, const string &directory,bool gamma);
		void LoadTexture();
		unsigned int TextureModel(const char* texture);

		std::vector<Mesh> _meshes;
		std::vector<Node*> _bspPlanes;

		Node* sceneNode;
	public:
		ModelImp();
		ModelImp(string path, const char* modelTexture, Shader& shader, Renderer* renderer);
		ModelImp(string path, Shader& shader, Renderer* renderer);
		~ModelImp();
		//void MoveModel(glm::vec3 direction);
		//void ScaleModel(float x, float y, float z);
		//void RotateModelX(float x);
		//void RotateModelY(float y);
		//void RotateModelZ(float z);
		Mesh* _rootNodeMesh;
		Node* GetSceneNode();
		std::vector<Node*> GetPlanesLoaded();
		//void SetModelPath(string path);
		//void SetTexturePath(const char* texturePath);
		void Draw(Shader& shader, Frustum frustum);
	};
}

#endif