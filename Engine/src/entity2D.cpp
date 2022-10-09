#include "entity2D.h"
#include "glm.hpp"
#include "vec3.hpp"
#include "mat4x4.hpp"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "ext/scalar_constants.hpp"
#include "gtc/type_ptr.hpp"

using namespace Engine;

void Engine::Entity2D::UpdateMatrices() {
	model.translate = glm::translate(glm::mat4(1.0f), transform.position);
	model.scale = glm::scale(glm::mat4(1.0f), transform.scale);

	UpdateModel();
}

void Entity2D::UpdateModel() {
	if (_hasParent) {
		model.trs = model.translate * model.rotation.x * model.rotation.y * model.rotation.z * model.scale;
		worldModel.trs = parentModel.trs * model.trs;
	}
	else{
		model.trs = model.translate * model.rotation.x * model.rotation.y * model.rotation.z * model.scale;
	}

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

	//Matrices necesarias para la jerarquia
	parentModel.trs = glm::mat4(1.0f);
	worldModel.trs = glm::mat4(1.0f);
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

void Entity2D::setHasParent(bool value) {
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
	//return model.trs;
	if (_hasParent)
		return worldModel.trs;
	else {
		return model.trs;
	}
}

void Entity2D::SetWorldModel(glm::mat4 matrix) {
	parentModel.trs = matrix;

	UpdateModel();
}

void Entity2D::SetMatrix(glm::mat4 matrix) {
	SetPos(GetPos(matrix));
	SetRotationRadians(GetRotation(matrix));
	SetScale(GetScale(matrix));
}

void Entity2D::SetPos(glm::vec3 position) {
	vlocalPosition = position;
	worldModel.translate = glm::translate(glm::mat4(1.0), vlocalPosition);

	UpdateModel();
}

glm::vec3 Entity2D::GetPos(glm::mat4 matrix) {
	return glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]);
}

glm::vec3 Entity2D::GetPos() {
	return vlocalPosition;
}

void Entity2D::SetRotationRadians(glm::vec3 rotation) {
	RotateX(glm::radians(rotation.x));
	RotateY(glm::radians(rotation.y));
	RotateZ(glm::radians(rotation.z));

	UpdateModel();
}

glm::vec3 Entity2D::GetRotation(glm::mat4 matrix) {
	return ToEulerRad(GetRotationInMatrix(matrix));
}

glm::vec3 Entity2D::GetRotation() {
	return vlocalRotation;
}

void Entity2D::SetScale(glm::vec3 localScale) {
	vlocalScale = localScale;
	model.scale = glm::scale(glm::mat4(1.0f), vlocalScale);

	UpdateModel();
}

glm::vec3 Entity2D::GetScale(glm::mat4 matrix) {
	glm::vec4 m0 = glm::vec4(matrix[0].x, matrix[0].y, matrix[0].z, matrix[0].w);
	glm::vec4 m1 = glm::vec4(matrix[1].x, matrix[1].y, matrix[1].z, matrix[1].w);
	glm::vec4 m2 = glm::vec4(matrix[2].x, matrix[2].y, matrix[2].z, matrix[2].w);

	return glm::vec3(glm::length(m0), glm::length(m1), glm::length(m2));
}

glm::vec3 Entity2D::GetScale() {
	return vlocalScale;
}

glm::vec3 Entity2D::ToEulerRad(glm::quat rotation) {
	float sqw = rotation.w * rotation.w;
	float sqx = rotation.x * rotation.x;
	float sqy = rotation.y * rotation.y;
	float sqz = rotation.z * rotation.z;
	float unit = sqx + sqy + sqz + sqw;
	float test = rotation.x * rotation.w - rotation.y * rotation.z;

	glm::vec3 vec = glm::vec3();

	if (test > 0.4995f * unit)
	{
		vec.y = 2.f * atan2(rotation.y, rotation.x);
		vec.x = glm::pi<float>() / 2.f;
		vec.z = 0.f;

		return NormalizeAngles(vec * 57.29578f);
	}
	if (test < -0.4995f * unit)
	{
		vec.y = -2.f * atan2(rotation.y, rotation.x);
		vec.x = -glm::pi<float>() / 2.f;
		vec.z = 0.f;

		return NormalizeAngles(vec * 57.29578f);
	}

	glm::vec4 quaternion = glm::vec4(rotation.w, rotation.z, rotation.x, rotation.y);
	vec.y = atan2(2.f * quaternion.x * quaternion.w + 2.f * quaternion.y * quaternion.z, 1.f - 2.f * (quaternion.z * quaternion.z + quaternion.w * quaternion.w));
	vec.x = asin(2.f * (quaternion.x * quaternion.z - quaternion.w * quaternion.y));
	vec.z = atan2(2.f * quaternion.x * quaternion.y + 2.f * quaternion.z * quaternion.w, 1.f - 2.f * (quaternion.y * quaternion.y + quaternion.z * quaternion.z));

	return NormalizeAngles(vec * 57.29578f);
}

glm::quat Entity2D::GetRotationInMatrix(glm::mat4 matrix) {
	glm::vec3 scale = GetScale(matrix);

	float m00 = matrix[0].x / scale.x;
	float m01 = matrix[0].y / scale.y;
	float m02 = matrix[0].z / scale.z;
	float m10 = matrix[1].x / scale.x;
	float m11 = matrix[1].y / scale.y;
	float m12 = matrix[1].z / scale.z;
	float m20 = matrix[2].x / scale.x;
	float m21 = matrix[2].y / scale.y;
	float m22 = matrix[2].z / scale.z;

	glm::quat quat = glm::quat();
	quat.w = glm::sqrt(glm::max(0.f, 1.f + m00 + m11 + m22)) / 2.f;
	quat.x = glm::sqrt(glm::max(0.f, 1.f + m00 - m11 - m22)) / 2.f;
	quat.y = glm::sqrt(glm::max(0.f, 1.f - m00 + m11 - m22)) / 2.f;
	quat.z = glm::sqrt(glm::max(0.f, 1.f - m00 - m11 + m22)) / 2.f;
	quat.x *= glm::sign(quat.x * (m21 - m12));
	quat.y *= glm::sign(quat.y * (m02 - m20));
	quat.z *= glm::sign(quat.z * (m10 - m01));

	float qMagnitude = glm::sqrt(quat.w * quat.w + quat.x * quat.x + quat.y * quat.y + quat.z * quat.z);
	quat.w /= qMagnitude;
	quat.x /= qMagnitude;
	quat.y /= qMagnitude;
	quat.z /= qMagnitude;

	return quat;
}

glm::vec3 Entity2D::NormalizeAngles(glm::vec3 angles) {
	angles.x = NormalizeAngle(angles.x);
	angles.y = NormalizeAngle(angles.y);
	angles.z = NormalizeAngle(angles.z);

	return angles;
}

float Entity2D::NormalizeAngle(float angle) {
	while (angle > 360.f)
		angle -= 360.f;
	while (angle < 0.f)
		angle += 360.f;

	return angle;
}

//En Game ordenar la posicion, rotacion y escala de cada objeto que venga en la escena para que queden bien posicionados