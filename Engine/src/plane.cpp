#include "plane.h"

using namespace Engine;

Plane::Plane() {
	_normal = glm::vec3(0.0f, 1.0f, 0.0f);
	_distance = 0.0f;
}

Plane::Plane(glm::vec3 normal, float distance) {
	_normal = normal;
	_distance = distance;
}

Plane::Plane(const glm::vec3& p1, const glm::vec3& normal) {
	_normal = glm::normalize(normal);
	_distance = glm::dot(_normal, p1);
}

Plane::~Plane() {

}

void Plane::SetNormal(glm::vec3 normal) {
	_normal = normal;
}

void Plane::SetDistance(float distance) {
	_distance = distance;
}

glm::vec3 Plane::GetNormal() {
	return _normal;
}

float Plane::GetDistance() {
	return _distance;
}

float Plane::GetSignedDistanceToPlane(const glm::vec3& point) {
	return glm::dot(_normal, point) - _distance;
}