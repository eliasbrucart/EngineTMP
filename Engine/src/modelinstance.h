#ifndef MODELINSTANCE_H
#define MODELINSTANCE_H
#include "export.h"
#include "modelimp.h"
#include "shader.h"
#include "renderer.h"
#include "node.h"

namespace Engine {
	class ENGINE_API ModelInstance {
	private:
		std::string _path;
		Shader _shader;
		Renderer* _renderer;
		ModelImp* _model;
		Node* _rootNode;
	public:
		ModelInstance(std::string path, Shader& shader, Renderer* renderer);
		~ModelInstance();
		Node* GetRootNode();
	};
}

#endif