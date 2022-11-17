#include "modelinstance.h"

using namespace Engine;

ModelInstance::ModelInstance(std::string path, Shader& shader, Renderer* renderer) {
	_path = path;
	_shader = shader;
	_renderer = renderer;
	_model = new ModelImp(path, shader, renderer);
}

ModelInstance::~ModelInstance() {

}

Node* ModelInstance::GetRootNode() {
	_rootNode = _model->GetSceneNode();

	return _rootNode;
}

std::vector<Node*> ModelInstance::GetPlanesLoaded() {
	return _model->GetPlanesLoaded();
}