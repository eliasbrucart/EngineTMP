#ifndef VOLUME_H
#define VOLUME_H
#include "export.h"
#include "camera.h"
#include "entity2D.h"

namespace Engine {
	class ENGINE_API Volume {
	private:
	public:
		Volume();
		~Volume();
		virtual bool IsOnFrustum(const Frustum& camFrustum, const Transform& modelTransform) = 0;
	};
}

#endif