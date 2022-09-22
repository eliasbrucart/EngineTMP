#include "plane.h"

using namespace Engine;

Plane::Plane() {
	_normal = glm::vec3(0.0f, 1.0f, 0.0f);
	_distance = 0.0f;
}

Plane::Plane(glm::vec3 normal, float distance) : Entity2D() {
	_normal = normal;
	_distance = distance;
}

Plane::Plane(const glm::vec3& p1, const glm::vec3& normal) : Entity2D() {
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

void Plane::SetAngleA(glm::vec3 angle) {
	_angleA = angle;
}

void Plane::SetAngleB(glm::vec3 angle) {
	_angleB = angle;
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

bool Plane::SameSide(glm::vec3 a, glm::vec3 b) {
	bool positiveSide = (GetSignedDistanceToPlane(a) >= 0) && (GetSignedDistanceToPlane(b) >= 0);
	bool negativeSide = (GetSignedDistanceToPlane(a) <= 0) && (GetSignedDistanceToPlane(b) <= 0);
	return positiveSide || negativeSide;
}

glm::vec3 Plane::GetAngleA() {
	return _angleA;
}

glm::vec3 Plane::GetAngleB() {
	return _angleB;
}