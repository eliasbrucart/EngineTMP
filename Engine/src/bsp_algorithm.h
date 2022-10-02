#ifndef BSP_ALGORITHM_H
#define BSP_ALGORITHM_H
#include "export.h"
#include "mesh.h"
#include "modelimp.h"
#include "plane.h"
#include "glm.hpp"
#include "camera.h"
#include "AABB.h"
#include <vector>
#include <iostream>
using namespace std;

namespace Engine {
	class ENGINE_API BSPAlgorithm {
	private:
		bool _isSameSign; //test
		std::vector<Plane*> _planes;
		std::vector<ModelImp*> _models;
		AABB* _aabb;
	public:
		BSPAlgorithm();
		~BSPAlgorithm();
		void BSP(Camera* camera);
		void CheckBSP(Camera* camera, Mesh* mesh);
		void CheckBSP(Camera* camera, AABB* aabb, Entity2D* parent, Mesh* mesh);
		//void CheckPlaneWithCamera(Camera* camera);
		void AddPlane(Plane* plane);
		void AddModel(ModelImp* model);
		void SetPosPlane(int planeIndex, glm::vec3 position);
		glm::vec3 GetPosPlane(int planeIndex, string tag);
	};
}

#endif