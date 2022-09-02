#ifndef BOUNDING_VOLUME_H
#define BOUNDING_VOLUME_H
#include "export.h"
#include "camera.h"
#include "entity2D.h"
#include "plane.h"
using namespace std;

namespace Engine {
	class ENGINE_API BoundingVolume {
	private:
	public:
		BoundingVolume();
		~BoundingVolume();
		virtual bool IsOnFrustum(Frustum& camFrustum, Entity2D* mesh) = 0;
		virtual bool IsOnOrForwardPlan(Plane& plane) = 0;
		bool IsOnFrustum(Frustum& camFrustum);
	};
}

#endif