#include "node.h"

using namespace Engine;

Node::Node() {
	_canDraw = true;
}

Node::~Node() {
	if (_localBoundingVolume != NULL) {
		delete _localBoundingVolume;
		_localBoundingVolume = NULL;
	}

	if (_volume != NULL) {
		delete _volume;
		_volume = NULL;
	}
}

void Node::SetChildren(Node* children) {
	_children.push_back(children);
}

void Node::SetChildren(std::vector<Node*> children) {
	_children = children;
}

void Node::SetParent(Node* parent) {
	_parent = parent;
}

void Node::SetMeshes(std::vector<Mesh> meshes) {
	_meshes = meshes;
}

void Node::SetLocalBoundingVolume(AABB* localBoundingVolume) {
	_localBoundingVolume = localBoundingVolume;
}

void Node::SetVolume(AABB* volume) {
	_volume = volume;
}

void Node::SetName(string name) {
	this->_nameNode = name;
}

void Node::UpdateNode() {
	if (_meshes.size() > 0) {
		_volume->UpdateAABB(_localBoundingVolume->min, _localBoundingVolume->max);
	}

	for (int i = 0; i < _children.size(); i++) {
		_children[i]->setWorldModelWithParentModel(worldModel);
		_children[i]->UpdateNode();

		UpdateAABBchildren(_children[i]);
	}
}

std::vector<Node*> Node::GetChildrens() {
	return _children;
}

Node* Node::GetParent() {
	return _parent;
}

string Node::GetName() {
	return _nameNode;
}

AABB* Node::GetLocalBoundingVolume() {
	return _localBoundingVolume;
}

AABB* Node::GetVolume() {
	return _volume;
}

void Node::SetRenderer(Renderer* renderer) {
	_renderer = renderer;
	UseLocalMatrix();
	for (int i = 0; i < _children.size(); i++) {
		_children[i]->SetRenderer(renderer);
	}

	GenerateAABB();
}

Node* Node::GetChildrenWithName(string name) {
	if (this->_nameNode == name) {
		return this;
	}

	for (int i = 0; i < _children.size(); i++) {
		if (_children[i]->GetName() == name) {
			if (_children[i] != NULL)
				return _children[i];
		}
	}

	for (int i = 0; i < _children.size(); i++) {
		Node* node = _children[i]->GetChildrenWithName(name);

		if (node != NULL) {
			return node;
		}
	}

	return NULL;
}

void Node::GenerateAABB() {
	if (_meshes.size() > 0) {

		std::cout << "Entro en Generate AABB en Node" << std::endl;

		glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
		glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());

		for (int i = 0; i < _meshes.size(); i++) {
			Mesh mesh = _meshes[i];

			for (int j = 0; j < mesh.vertices.size(); j++) {

				std::cout << "llego a entrar en el sgundo for! mesh vertrices: " << mesh.vertices.size() << std::endl;

				Vertex vertex = mesh.vertices[j];

				minAABB.x = glm::min(minAABB.x, vertex.Position.x);
				minAABB.y = glm::min(minAABB.y, vertex.Position.y);
				minAABB.z = glm::min(minAABB.z, vertex.Position.z);

				maxAABB.x = glm::max(maxAABB.x, vertex.Position.x);
				maxAABB.y = glm::max(maxAABB.y, vertex.Position.y);
				maxAABB.z = glm::max(maxAABB.z, vertex.Position.z);
			}
		}
		_localBoundingVolume = new AABB(minAABB, maxAABB);
		_volume = new AABB(minAABB, maxAABB);
	}
}

void Node::UpdateAABBchildren(Node* child) {
	if (child->GetVolume() != NULL) {

		AABB* childVolume = child->GetVolume();

		glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
		glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());

		if (_volume != NULL) {
			minAABB.x = glm::min(_volume->min.x, childVolume->min.x);
			minAABB.y = glm::min(_volume->min.y, childVolume->min.y);
			minAABB.z = glm::min(_volume->min.z, childVolume->min.z);

			maxAABB.x = glm::max(_volume->max.x, childVolume->max.x);
			maxAABB.y = glm::max(_volume->max.y, childVolume->max.y);
			maxAABB.z = glm::max(_volume->max.z, childVolume->max.z);

			childVolume->UpdateAABB(minAABB, maxAABB);
		}
		else {
			_volume = new AABB(childVolume->min, childVolume->max);
		}

	}
}

void Node::Draw(Shader& shader, Frustum& frustum) {
	if (_meshes.size() > 0 && _canDraw) {
		//shader.Use(worldModel);
		for (int i = 0; i < _meshes.size(); i++) {
			_renderer->DrawMesh(shader, _meshes[i]._vao, _meshes[i]._vbo, _meshes[i].vertices.size() * sizeof(Vertex), &_meshes[i].vertices[0], _meshes[i].indices.size(), sizeof(Vertex), 0, offsetof(Vertex, Normal), offsetof(Vertex, TexCoords), worldModel);
			//_meshes[i].Draw(shader, frustum);
		}
	}

	for (int i = 0; i < _children.size(); i++) {
		//_children[i]->setWorldModelWithParentModel(worldModel);
		_children[i]->Draw(shader, frustum);
	}
}

void Node::DrawPlane(Shader& shader) {
	if (_meshes.size() > 0 || !_meshes.empty()) {
		shader.Use(worldModel);
		for (int i = 0; i < _meshes.size(); i++) {
			_renderer->DrawMesh(shader, _meshes[i]._vao, _meshes[i]._vbo, _meshes[i].vertices.size() * sizeof(Vertex), &_meshes[i].vertices[0], _meshes[i].indices.size(), sizeof(Vertex), 0, offsetof(Vertex, Normal), offsetof(Vertex, TexCoords), worldModel);
			//_meshes[i].Draw(shader, frustum);
		}
	}

	for (int i = 0; i < _children.size(); i++) {
		//_children[i]->setWorldModelWithParentModel(worldModel);
		_children[i]->DrawPlane(shader);
	}
}

void Node::SetCanDraw(bool value) {
	_canDraw = value;
}

bool Node::GetCanDraw() {
	return _canDraw;
}

void Node::StopDrawNodeAndChildrens(Node* node) {
	node->SetCanDraw(false);
	if (!node->GetChildrens().empty()) {
		for (int i = 0; i < node->GetChildrens().size(); i++) {
			StopDrawNodeAndChildrens(node->GetChildrens()[i]);
		}
	}
}

void Node::BSP(vector<Plane*> planes, Camera* camera) {
	_canDraw = true;

	if (_volume == NULL) {
		for (int i = 0; i < _children.size(); i++) {
			UpdateAABBchildren(_children[i]);
		}
	}

	for (int i = 0; i < planes.size(); i++) {
		if (_volume->GetGlobalAABBWithMatrix(worldModel).IsOnOrForwardPlan(planes[i]) != planes[i]->GetSide(camera->transform.position)) {
			_canDraw = false;
			break;
		}
	}

	for (int j = 0; j < _children.size(); j++) {
		_children[j]->BSP(planes, camera);
	}
}