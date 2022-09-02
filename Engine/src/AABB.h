#ifndef AABB_H
#define AABB_H
#include "export.h"
#include "glm.hpp"
#include "bounding_volume.h"
#include "plane.h"
#include "entity2D.h"

namespace Engine {
	class ENGINE_API AABB : public BoundingVolume {
	private:
		glm::vec3 _center;
		glm::vec3 _extents;
	public:
		AABB();
		AABB(glm::vec3& min, glm::vec3& max);
		AABB(glm::vec3& inCenter, float iI, float iJ, float iK);
		~AABB();
		bool IsOnFrustum(Frustum& camFrustum, Entity2D* mesh);
		bool IsOnOrForwardPlan(Plane& plane);
		glm::vec3 GetCenter();
		glm::vec3 GetExtents();
	};
}

#endif