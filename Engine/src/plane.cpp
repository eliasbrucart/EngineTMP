#include "plane.h"

using namespace Engine;

Plane::Plane() {
	_normal = glm::vec3(0.0f, 1.0f, 0.0f);
	_distance = 0.0f;
}

Plane::Plane(glm::vec3 normal, float distance) : Entity() {
	_normal = normal;
	_distance = distance;
}

Plane::Plane(const glm::vec3& p1, const glm::vec3& normal) : Entity() {
	_normal = glm::normalize(normal);
	_distance = -glm::dot(_normal, p1);
}

//Plane::Plane(glm::vec3 normal, glm::vec3 point) : Entity2D() {
//	_normal = glm::normalize(normal);
//	_distance = -glm::dot(normal, point);
//}

Plane::Plane(glm::vec3 a, glm::vec3 b, glm::vec3 c) : Entity() {
	_normal = glm::normalize(glm::cross(b - a, c - a));
	_distance = -glm::dot(_normal, a);
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

bool Plane::SameSide(glm::vec3 a, glm::vec3 b) {
	bool positiveSide = (GetSignedDistanceToPlane(a) >= 0) && (GetSignedDistanceToPlane(b) >= 0);
	bool negativeSide = (GetSignedDistanceToPlane(a) <= 0) && (GetSignedDistanceToPlane(b) <= 0);
	return positiveSide || negativeSide;
}

void Plane::Set3Points(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
	_normal = glm::normalize(glm::cross(b - a, c - a));
	_distance = -glm::dot(_normal, a);
}

void Plane::Flip() {
	_normal = -_normal;
	_distance = -_distance;
}

float Plane::GetDistanceToPoint(glm::vec3 point) {
	return glm::dot(_normal, point) + _distance;
}

bool Plane::GetSide(glm::vec3 point) {
	return glm::dot(_normal, point) + _distance > 0.0f;
}

bool Plane::SameSideA(glm::vec3 pointA, glm::vec3 pointB) {
	float dist0 = GetDistanceToPoint(pointA);
	float dist1 = GetDistanceToPoint(pointB);
	return (dist0 > 0.0f && dist1 > 0.0f || dist0 <= 0.0f && dist1 <= 0.0f);
}