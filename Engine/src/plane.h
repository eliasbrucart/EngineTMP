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
	public:
		Plane();
		Plane(glm::vec3 normal, float distance);
		Plane(const glm::vec3& p1, const glm::vec3& normal);
		//Plane(glm::vec3 normal, glm::vec3 point);
		Plane(glm::vec3 a, glm::vec3 b, glm::vec3 c);
		~Plane();
		void SetNormal(glm::vec3 normal);
		void SetDistance(float distance);
		glm::vec3 GetNormal();
		float GetDistance();
		float GetSignedDistanceToPlane(const glm::vec3& point);
		bool SameSide(glm::vec3 a, glm::vec3 b);
		void Set3Points(glm::vec3 a, glm::vec3 b, glm::vec3 c);
		void Flip();
		float GetDistanceToPoint(glm::vec3 point);
		bool GetSide(glm::vec3 point);
		bool SameSideA(glm::vec3 pointA, glm::vec3 pointB);
		//bool SameSide
	};
}

#endif