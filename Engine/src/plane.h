#ifndef PLANE_H
#define PLANE_H
#include "export.h"
#include "glm.hpp"
#include "vec3.hpp"
#include <iostream>
using namespace std;

namespace Engine {
	class ENGINE_API Plane {
	private:
		glm::vec3 _normal;
		float _distance;
	public:
		Plane();
		Plane(glm::vec3 normal, float distance);
		Plane(const glm::vec3& p1, const glm::vec3& normal);
		~Plane();
		void SetNormal(glm::vec3 normal);
		void SetDistance(float distance);
		glm::vec3 GetNormal();
		float GetDistance();
		float GetSignedDistanceToPlane(const glm::vec3& point);
	};
}

#endif