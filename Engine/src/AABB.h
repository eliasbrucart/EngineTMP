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
		AABB* _globalAABB;
	public:
		AABB();
		AABB(glm::vec3& min, glm::vec3& max);
		AABB(glm::vec3& inCenter, float iI, float iJ, float iK);
		~AABB();
		bool IsOnFrustum(Frustum& camFrustum, Entity2D* mesh);
		bool IsOnFrustum(Frustum& camFrustum, glm::mat4 worldModel);
		bool IsOnBSP(std::vector<Plane*> planes, Entity2D* mesh);
		void GenerateGlobalAABB(Entity2D* mesh);
		AABB* GetGlobalAABB();
		AABB GetGlobalAABBWithMatrix(glm::mat4 matrix);
		bool IsOnOrForwardPlan(Plane& plane);
		bool IsOnOrForwardPlan(Plane* plane);
		bool IsOnOrForwardPlan(Plane plane);
		bool IsOnOrBackwardPlan(Plane* plane);
		glm::vec3 GetCenter();
		glm::vec3 GetExtents();
		glm::vec3 min;
		glm::vec3 max;
		void UpdateAABB(glm::vec3 min, glm::vec3 max);
	};
}

#endif