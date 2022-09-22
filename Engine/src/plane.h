#ifndef PLANE_H
#define PLANE_H
#include "export.h"
#include "glm.hpp"
#include "vec3.hpp"
#include "entity2D.h"
#include <iostream>
using namespace std;

namespace Engine {
	class ENGINE_API Plane : public Entity2D {
	private:
		glm::vec3 _normal;
		float _distance;
		glm::vec3 _angleA;
		glm::vec3 _angleB;
	public:
		Plane();
		Plane(glm::vec3 normal, float distance);
		Plane(const glm::vec3& p1, const glm::vec3& normal);
		~Plane();
		void SetNormal(glm::vec3 normal);
		void SetDistance(float distance);
		void SetAngleA(glm::vec3 angle);
		void SetAngleB(glm::vec3 angle);
		glm::vec3 GetNormal();
		float GetDistance();
		float GetSignedDistanceToPlane(const glm::vec3& point);
		bool SameSide(glm::vec3 a, glm::vec3 b);
		glm::vec3 GetAngleA();
		glm::vec3 GetAngleB();
	};
}

#endif