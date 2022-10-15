#ifndef BSP_ALGORITHM_H
#define BSP_ALGORITHM_H
#include "export.h"
#include "mesh.h"
#include "plane.h"
#include "glm.hpp"
#include "camera.h"
#include "AABB.h"
#include "node.h"
#include <vector>
#include <iostream>
using namespace std;

namespace Engine {
	class ENGINE_API BSPAlgorithm {
	private:
		bool _isSameSign; //test
		std::vector<Plane*> _planes;
		std::vector<Node*> _nodes;
		Camera* _camera;
		AABB* _aabb;
	public:
		BSPAlgorithm();
		~BSPAlgorithm();
		void BSP(Camera* camera);
		void CheckBSP(Camera* camera, Mesh* mesh);
		//void CheckPlaneWithCamera(Camera* camera);
		void AddPlane(Plane* plane);
		void AddNode(Node* model);
	};
}

#endif