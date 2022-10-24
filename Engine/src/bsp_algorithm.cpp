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

	if (!_planeModel.empty()) {
		for (auto* planeM : _planeModel) {
			if (planeM != NULL) {
				delete planeM;
				planeM = NULL;
			}
		}
		_planeModel.clear();
	}

	if (_aabb != NULL) {
		delete _aabb;
		_aabb = NULL;
	}
}

void BSPAlgorithm::BSP() {
	for (int i = 0; i < _nodes.size(); i++) {
		CheckBSP(_nodes[i]);
		//std::cout << "vector models get meshes: " << _models[i]->GetMeshes().size() << std::endl;
	}
}

void BSPAlgorithm::CheckBSP(Node* node) {
	bool checkPassed = true;
	//if (_aabb->IsOnBSP(_planes, mesh)) {
	//	std::cout << "La malla esta del mismo lado del los tres planos del BSP!" << std::endl;
	//	mesh->SetCanDraw(true);
	//}
	//else {
	//	std::cout << "La malla NO esta del mismo lado del BSP" << std::endl;
	//	mesh->SetCanDraw(false);
	//}
	//node->SetCanDraw(true);

	if (!node->GetChildrens().empty()) {

		for (int i = 0; i < _planes.size(); i++) {

			//if (node->GetVolume() != NULL) {
			//	if (node->GetVolume()->IsOnOrForwardPlan(_planes[i]) != _planes[i]->GetSide(_camera->transform.position)) {
			//		//std::cout << "Esta del mismo lado del plano y de la camara!" << std::endl;
			//		//node->SetCanDraw(false);
			//		checkPassed = false;
			//		break;
			//	}
			//}

			if (node->GetVolume() != NULL) {
				if (node->GetVolume()->GetGlobalAABBWithMatrix(node->getModel()).IsOnOrForwardPlan(_planes[i]) != _planes[i]->GetSide(_camera->transform.position)) {
					//std::cout << "Esta del mismo lado del plano y de la camara!" << std::endl;
					//node->SetCanDraw(false);
					checkPassed = false;
					break;
				}
			}
		}

		if (!checkPassed) {
			node->SetCanDraw(false);
			node->StopDrawNodeAndChildrens(node);
			//llamar al chequeo que si tiene hijos, tambien pare el dibujado de los mismos
			return;
		}
	}

	for (int i = 0; i < _planes.size(); i++) {
		if (node->GetVolume() != NULL) {
			if (node->GetVolume()->GetGlobalAABBWithMatrix(node->getModel()).IsOnOrForwardPlan(_planes[i]) != _planes[i]->GetSide(_camera->transform.position)) {
				//std::cout << "Esta del mismo lado del plano y de la camara!" << std::endl;
				//node->SetCanDraw(false);
				checkPassed = false;
				break;
			}
		}
	}

	if (!checkPassed) {
		node->SetCanDraw(false);
	}
	else {
		node->SetCanDraw(true);
	}
	
	for (int j = 0; j < node->GetChildrens().size(); j++) {
		CheckBSP(node->GetChildrens()[j]);
	}

	//Agregar chequeo de nodos hijos al BSP, llamar recursivamente a la funcion

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

void BSPAlgorithm::CheckCameraWithPlanes() {
	for (int i = 0; i < _planes.size(); i++) {
		if (!_planes[i]->GetSide(_camera->transform.position)) //Esto tiene que ir separado del calculo del algoritmo
			_planes[i]->Flip();
	}
}

void BSPAlgorithm::AddPlane(Node* plane) {
	_planeModel.push_back(plane);
	for (int i = 0; i < _planeModel.size(); i++) {
		glm::vec3 planeNormal = glm::normalize(_planeModel[i]->getForwardConst());
		Plane* bspPlane = new Plane(_planeModel[i]->getPos(), planeNormal);
		_planes.push_back(bspPlane);
	}
}

void BSPAlgorithm::SetUpPlaneRenderer(Renderer* renderer) {
	for (int i = 0; i < _planeModel.size(); i++) {
		_planeModel[i]->SetRenderer(renderer);
	}
}

void BSPAlgorithm::AddNode(Node* node) {
	_nodes.push_back(node);
	if (node->GetParent() != NULL) {
		_nodes.push_back(node->GetParent());
		//std::vector<Node*> childrens;
	}
	for (int i = 0; i < node->GetChildrens().size(); i++) {
		_nodes.push_back(node->GetChildrens()[i]);
	}
	//_nodes.push_back(node);
	//Desde el game llamar a AddNode y que el nodo padre se agregue a la lista junto con sus hijos para hacer el chequeo del BSP.
}

void BSPAlgorithm::AddCamera(Camera* camera) {
	_camera = camera;
}