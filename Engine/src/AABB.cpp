#include "AABB.h"

using namespace Engine;

AABB::AABB() : BoundingVolume() {

}

AABB::AABB(glm::vec3& min, glm::vec3& max) : BoundingVolume() {
	_center = (max + min) * 0.5f;
	_extents = glm::vec3(max.x - _center.x, max.y - _center.y, max.z - _center.z);
}

AABB::AABB(glm::vec3& inCenter, float iI, float iJ, float iK) : BoundingVolume() {
	_center = inCenter;
	_extents = glm::vec3(iI, iJ, iK);
}

AABB::~AABB() {

}

bool AABB::IsOnFrustum(Frustum& camFrustum, Entity2D* mesh) {
	glm::vec3 globalCenter{ mesh->model.trs * glm::vec4(_center, 1.0f) };

	glm::vec3 right = mesh->transform.right * _extents.x;
	glm::vec3 up = mesh->transform.up * _extents.y;
	glm::vec3 forward = mesh->transform.forward * _extents.z;

	float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
		std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
		std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

	float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

	float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

	AABB globalAABB(globalCenter, newIi, newIj, newIk);

	return (globalAABB.IsOnOrForwardPlan(camFrustum.leftFace) &&
		globalAABB.IsOnOrForwardPlan(camFrustum.rightFace) &&
		globalAABB.IsOnOrForwardPlan(camFrustum.topFace) &&
		globalAABB.IsOnOrForwardPlan(camFrustum.bottomFace) &&
		globalAABB.IsOnOrForwardPlan(camFrustum.nearFace) &&
		globalAABB.IsOnOrForwardPlan(camFrustum.farFace));
}

bool AABB::IsOnOrForwardPlan(Plane& plane) {
	float r = _extents.x * std::abs(plane.GetNormal().x) + _extents.y * std::abs(plane.GetNormal().y) + _extents.z * std::abs(plane.GetNormal().z);

	return -r <= plane.GetSignedDistanceToPlane(_center);
}

glm::vec3 AABB::GetCenter() {
	return _center;
}

glm::vec3 AABB::GetExtents() {
	return _extents;
}