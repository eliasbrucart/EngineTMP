#ifndef NODE_H
#define NODE_H
#include "export.h"
#include "entity.h"
#include "mesh.h"
#include "AABB.h"
#include "glm.hpp"
#include "renderer.h"
#include "shader.h"
#include "camera.h"
#include "material.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

namespace Engine {
	class ENGINE_API Node : public Entity {
	private:
		std::vector<Node*> _children;
		Node* _parent;

		std::vector<Mesh> _meshes;

		std::string _nameNode;

		std::vector<glm::vec3> _aabb;
		std::vector<glm::vec3> _localAABB;
		std::vector<glm::vec3> _aabbPositions;

		AABB* _localBoundingVolume;
		AABB* _volume;

		Renderer* _renderer;

		bool _canDraw;

		Material* _material;

	public:
		Node();
		~Node();
		void SetChildren(Node* children);
		void SetChildren(std::vector<Node*> children);
		void SetParent(Node* parent);
		void SetMeshes(std::vector<Mesh> meshes);
		void SetLocalBoundingVolume(AABB* localBoundingVolume);
		void SetVolume(AABB* volume);
		void SetName(string name);
		void UpdateNode();
		void UpdateNodeChildren();
		std::vector<Node*> GetChildrens();
		Node* GetParent();
		string GetName();
		AABB* GetLocalBoundingVolume();
		AABB* GetVolume();
		void Init(Renderer* renderer);
		void SetMaterial();
		Node* GetChildrenWithName(string name);
		void GenerateAABB();
		void UpdateAABBchildren(Node* child);
		void Draw(Shader& shader, Frustum frustum);
		void DrawPlane(Shader& shader);
		void SetCanDraw(bool value);
		bool GetCanDraw();
		void StopDrawNodeAndChildrens(Node* node);
		void BSP(vector<Plane*> planes, Camera* camera);
		void SetMeshPos(float x, float y, float z, int meshIndex);
		void SetMeshScale(float x, float y, float z, int meshIndex);
		void IsOnFrustum(Frustum& frustum);
	};
}

#endif