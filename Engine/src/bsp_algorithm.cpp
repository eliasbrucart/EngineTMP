#include "bsp_algorithm.h"

using namespace Engine;

BSPAlgorithm::BSPAlgorithm() {
	_isSameSign = false;
}

BSPAlgorithm::~BSPAlgorithm() {
	if (!_planes.empty()) {
		for (auto* plane : _planes) {
			if (plane != NULL) {
				delete plane;
				plane = NULL;
			}
		}
		_planes.clear();
	}

	if (!_nodes.empty()) {
		for (auto* model : _nodes) {
			if (model != NULL) {
				delete model;
				model = NULL;
			}
		}
		_nodes.clear();
	}

	if (_aabb != NULL) {
		delete _aabb;
		_aabb = NULL;
	}
}

void BSPAlgorithm::BSP(Camera* camera) {
	for (int i = 0; i < _nodes.size(); i++) {
		//_aabb = _models[i]->GetMeshes()[i]->GetMeshAABB();
		//CheckBSP(camera, _models[i]->GetMeshes()[0]);
		//std::cout << "vector models get meshes: " << _models[i]->GetMeshes().size() << std::endl;
	}
}

void BSPAlgorithm::CheckBSP(Camera* camera, Mesh* mesh) {
	//_aabb = mesh->GetMeshAABB(); //Aca un getter del aabb de nuestra malla.


	//if (_aabb->IsOnBSP(_planes, mesh)) {
	//	std::cout << "La malla esta del mismo lado del los tres planos del BSP!" << std::endl;
	//	mesh->SetCanDraw(true);
	//}
	//else {
	//	std::cout << "La malla NO esta del mismo lado del BSP" << std::endl;
	//	mesh->SetCanDraw(false);
	//}

	for (int i = 0; i < _planes.size(); i++) {
		//if (mesh->GetMeshAABB().IsOnOrForwardPlan(camera->GetNear())) {
		//	std::cout << "La malla esta del mismo lado del plano near de la camara!" << std::endl;
		//}
		//if (_aabb->IsOnOrForwardPlan(_planes[i])) {
		//	std::cout << "La malla esta del mismo lado del los tres planos del BSP!" << std::endl;
		//	mesh->SetCanDraw(true);
		//}
		//else {
		//	mesh->SetCanDraw(false);
		//}
	
		if(_planes[0]->SameSideA(_aabb->GetCenter(), camera->transform.position)/* &&
			_planes[1]->SameSide(_aabb->GetCenter(), camera->transform.position) &&
			_planes[2]->SameSide(_aabb->GetCenter(), camera->transform.position)*/){
			std::cout << "La malla esta del mismo lado del plano!" << std::endl;
			mesh->SetCanDraw(true);
		}
		else {
			mesh->SetCanDraw(false);
		}
	}

	//for (int i = 0; i < _planes.size(); i++) {
	//	glm::vec3 directionA = glm::normalize(_aabb.GetCenter() - _planes[i]->transform.position);
	//	float dotDirectionA = glm::dot(directionA, _planes[i]->transform.position);
	//
	//	if (dotDirectionA < 0.0f)
	//		std::cout << "No esta del lado correcto del plano" << std::endl;
	//}
	//recursividad
	//CheckBSP(camera, _models[0]->GetMeshes()[0]);
	//for (int i = 0; i < _models.size(); i++) {
	//	if (_models[i]->GetMeshes()[i]->_parent != NULL) {
	//		for(int k = 0; k < _models[i]->GetMeshes().size(); k++)
	//			CheckBSP(camera, _models[i]->GetMeshes()[k]);
	//	}
	//}

	//for (int i = 0; i < mesh->_meshes.size(); i++) {
	//	if(mesh->_meshes[i]->GetHasParent())
	//		CheckBSP(camera, mesh->_meshes[i]);
	//
	//	//if(mesh->_meshes[i]->GetChildrenNodePtr() != nullptr)
	//	//	CheckBSP(camera, mesh->_meshes[i]);
	//}
}

void BSPAlgorithm::AddPlane(Plane* plane) {
	glm::vec3 planeNormal = glm::normalize(plane->getForwardConst());
	Plane* bspPlane = new Plane(planeNormal, plane->getPos());
	_planes.push_back(bspPlane);
}

void SetUpPlane(Plane* plane) {
	glm::vec3 planeNormal = glm::normalize(plane->getForwardConst());
}

void BSPAlgorithm::AddNode(Node* node) {
	_nodes.push_back(node);
}