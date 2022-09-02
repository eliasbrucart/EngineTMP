#include "bounding_volume.h"

using namespace Engine;

BoundingVolume::BoundingVolume() {

}

BoundingVolume::~BoundingVolume() {

}

bool BoundingVolume::IsOnFrustum(Frustum& camFrustum) {
	return (IsOnOrForwardPlan(camFrustum.leftFace) &&
		IsOnOrForwardPlan(camFrustum.rightFace) &&
		IsOnOrForwardPlan(camFrustum.topFace) &&
		IsOnOrForwardPlan(camFrustum.bottomFace) &&
		IsOnOrForwardPlan(camFrustum.nearFace) &&
		IsOnOrForwardPlan(camFrustum.farFace));
}