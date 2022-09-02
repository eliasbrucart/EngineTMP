#include "entity2D.h"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "ext/scalar_constants.hpp"

using namespace Engine;

void Engine::Entity2D::UpdateMatrices() {
	model.translate = glm::translate(glm::mat4(1.0f), transform.position);
	model.scale = glm::scale(glm::mat4(1.0f), transform.scale);

	UpdateModel();
}

void Entity2D::UpdateModel() {
	model.trs = model.translate * model.rotation.x * model.rotation.y * model.rotation.z * model.scale;
}

Entity2D::Entity2D() {
	model.translate = glm::mat4(1.0);
	model.rotation.x = glm::mat4(1.0);
	model.rotation.y = glm::mat4(1.0);
	model.rotation.z = glm::mat4(1.0);
	model.scale = glm::mat4(1.0);

	Translate(1.0f, 1.0f, 1.0f);
	RotateX(0.0f);
	RotateY(0.0f);
	RotateZ(0.0f);
	Scale(1.0f, 1.0f, 1.0f);
}

Entity2D::~Entity2D() {

}

void Entity2D::UpdateForward() {
	transform.forward.x = glm::cos(glm::radians(transform.rotation.y)) * glm::cos(glm::radians(transform.rotation.x));
	transform.forward.y = glm::sin(glm::radians(transform.rotation.x));
	transform.forward.z = glm::sin(glm::radians(transform.rotation.y)) * glm::cos(glm::radians(transform.rotation.x));
	transform.forward = glm::normalize(transform.forward);
}

void Entity2D::UpdateUp() {
	transform.up = glm::normalize(glm::cross(transform.right, transform.forward));
}

void Entity2D::UpdateRight() {
	transform.right = glm::normalize(glm::cross(transform.forward, glm::vec3(0, 1, 0)));
}

void Entity2D::AddChild(Entity2D* entity) {
	children.emplace_back(entity); //Agregamos una entidad nueva a nuestro vector de entidades hijas
	children.back()->_parent = this; //Agregamos la entidad actual como padre de la nueva entidad agregada
	_hasParent = true;
}

//Obtenemos la matriz modelo local de la entidad actual
glm::mat4 Entity2D::GetLocalModelMatrix() {
	const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	const glm::mat4 rotationMatrix = transformX * transformY * transformZ;

	return glm::translate(glm::mat4(1.0f), transform.position) * rotationMatrix * glm::scale(glm::mat4(1.0f), transform.scale);
}

//Actualizamos la matriz modelo de esta entidad actual, si hay padre, multiplicamos la matriz modelo de la entidad con la del hijo
//Si no hay hijo tambien actualizamos la matriz modelo
void Entity2D::UpdateSelfAndChild() {
	//if (!m_isDirty)
	//	return;

	ForceUpdateSelfAndChild();

	//if (parent) {
	//	model.trs = parent->model.trs * GetLocalModelMatrix();
	//}
	//else {
	//	model.trs = GetLocalModelMatrix();
	//}
	//
	//for (auto&& child : children)
	//	child->UpdateSelfAndChild();
}

//AABB Entity2D::GenerateAABB(std::vector<Mesh*> meshes, std::vector<Vertex> vertices) {
//	glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
//	glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());
//	for (auto&& mesh : meshes) {
//		for (auto&& vertex : vertices) {
//			minAABB.x = std::min(minAABB.x, vertex.Position.x);
//			minAABB.y = std::min(minAABB.y, vertex.Position.y);
//			minAABB.z = std::min(minAABB.z, vertex.Position.z);
//
//			maxAABB.x = std::max(maxAABB.x, vertex.Position.x);
//			maxAABB.y = std::max(maxAABB.y, vertex.Position.y);
//			maxAABB.z = std::max(maxAABB.z, vertex.Position.z);
//		}
//	}
//	return AABB(minAABB, maxAABB);
//}

void Entity2D::ComputeModelMatrix() {
	model.trs = GetLocalModelMatrix();
}

void Entity2D::ComputeModelMatrix(const glm::mat4& parentGlobalModelMatrix) {
	model.trs = parentGlobalModelMatrix * GetLocalModelMatrix();
}

void Entity2D::SetLocalPosition(const glm::vec3& newPosition) {
	transform.position = newPosition;
}

const glm::mat4& Entity2D::GetModelMatrix() {
	return model.trs;
}

bool Entity2D::IsDirty() {
	return m_isDirty;
}

void Entity2D::ForceUpdateSelfAndChild() {
	if (_parent) {
		ComputeModelMatrix(_parent->GetModelMatrix());
	}
	else {
		ComputeModelMatrix();
	}

	for (auto&& child : children)
		child->ForceUpdateSelfAndChild();
}

inline void Entity2D::SetParent(Entity2D* parent) {
	_parent = parent;
	_hasParent = true;
}

inline bool Entity2D::GetHasParent() {
	return _hasParent;
}

void Engine::Entity2D::RotateX(float angle) {
	transform.rotation.x = angle;
	glm::vec3 axis = glm::vec3(1.0);
	axis[0] = 1.0f;
	axis[1] = 0.0f;
	axis[2] = 0.0f;
	model.rotation.x = glm::rotate(glm::mat4(1.0), angle, axis);
	UpdateModel();
}

void Engine::Entity2D::RotateY(float angle) {
	transform.rotation.y = angle;
	glm::vec3 axis = glm::vec3(1.0);
	axis[0] = 0.0f;
	axis[1] = 1.0f;
	axis[2] = 0.0f;
	model.rotation.y = glm::rotate(glm::mat4(1.0), angle, axis);
	UpdateModel();
}

void Engine::Entity2D::RotateZ(float angle) {
	transform.rotation.z = angle;
	glm::vec3 axis = glm::vec3(1.0);
	axis[0] = 0.0f;
	axis[1] = 0.0f;
	axis[2] = 1.0f;
	model.rotation.z = glm::rotate(glm::mat4(1.0), angle, axis);
	UpdateModel();
}



void Entity2D::Translate(float x, float y, float z) {
	transform.position.x = x;
	transform.position.y = y;
	transform.position.z = z;

	model.translate = glm::translate(glm::mat4(1.0), transform.position);
	UpdateModel();
}

glm::vec2 Entity2D::Lerp(glm::vec2 a, glm::vec2 b, float t){
	glm::vec2 auxVec = glm::vec2(1.0);

	if (t < 1)
		auxVec = glm::vec2((b - a) * t + a);
	else
		t = 1;
	return auxVec;

}

void Entity2D::Scale(float x, float y, float z) {
	transform.scale.x = x;
	transform.scale.y = y;
	transform.scale.z = z;

	model.scale = glm::scale(glm::mat4(1.0), transform.scale);
	UpdateModel();
}

void Entity2D::UpdateVectors() {
	UpdateForward();
	UpdateUp();
	UpdateRight();
}

glm::mat4 Entity2D::GetModel() {
	if (_hasParent)
		return _parent->model.trs * model.trs;
	return model.trs;
}


