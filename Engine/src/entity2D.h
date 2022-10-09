#ifndef ENTITY2D_H
#define ENTITY2D_H
#include "export.h"
#include "mat4x4.hpp"
#include "vec3.hpp"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <vector>

using namespace std;

namespace Engine {

	struct ENGINE_API Rotation {
		glm::mat4 x;
		glm::mat4 y;
		glm::mat4 z;
	};

	struct ENGINE_API Transform {
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 right;
	};

	struct ENGINE_API Model {
		glm::mat4 translate;
		Rotation rotation;
		glm::mat4 scale;
		glm::mat4 trs;
	};

	//Agregar referencias a Model, agregar vector de entidades hijas y puntero al padre.
	//Agregar metodo para agregar hijos al vector.

	class ENGINE_API Entity2D {
	private:
		bool _hasParent;
	protected:
		void UpdateMatrices();
		void UpdateModel();
		void UpdateForward();
		void UpdateUp();
		void UpdateRight();
	public:
		//metodos y atributos para scene graph
		std::vector<Entity2D*> children;
		Entity2D* _parent = nullptr;
		void AddChild(Entity2D* entity);
		glm::mat4 GetLocalModelMatrix();
		void UpdateSelfAndChild();
		//AABB _boundingVolume;
		Model model;
		Model parentModel;
		Model worldModel;
		//AABB GenerateAABB(std::vector<Mesh*> meshes, std::vector<Vertex> vertices);
		//Crear un metodo que devuelva un AABB global
		bool m_isDirty;
		void ComputeModelMatrix();
		void ComputeModelMatrix(const glm::mat4& parentGlobalModelMatrix);
		void SetLocalPosition(const glm::vec3& newPosition);
		const glm::mat4& GetModelMatrix();
		bool IsDirty();
		void ForceUpdateSelfAndChild();
		inline void SetParent(Entity2D* parent);
		void setHasParent(bool value);
		inline bool GetHasParent();
		Transform transform;
		Entity2D();
		~Entity2D();
		void RotateX(float angle);
		void RotateY(float angle);
		void RotateZ(float angle);
		void Translate(float x, float y, float z);
		glm::vec2 Lerp(glm::vec2 a, glm::vec2 b, float t);
		void Scale(float x, float y, float z);
		void UpdateVectors();
		glm::mat4 GetModel();
		void SetWorldModel(glm::mat4 matrix);
		void SetMatrix(glm::mat4 matrix);
		void SetPos(glm::vec3 position);
		glm::vec3 GetPos(glm::mat4 matrix);
		glm::vec3 GetPos();
		void SetRotationRadians(glm::vec3 rotation);
		glm::vec3 GetRotation(glm::mat4 matrix);
		glm::vec3 GetRotation();
		void SetScale(glm::vec3 localScale);
		glm::vec3 GetScale(glm::mat4 matrix);
		glm::vec3 GetScale();
		glm::vec3 ToEulerRad(glm::quat rotation);
		glm::quat GetRotationInMatrix(glm::mat4 matrix);
		glm::vec3 NormalizeAngles(glm::vec3 angles);
		float NormalizeAngle(float angle);

		//Crear metodo ToEulerRad

		glm::vec3 vlocalPosition;
		glm::vec3 vlocalRotation;
		glm::vec3 vlocalScale;
	};

}

#endif // !ENTITY2D_H

