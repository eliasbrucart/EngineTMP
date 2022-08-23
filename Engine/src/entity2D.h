#ifndef ENTITY2D_H
#define ENTITY2D_H
#include "export.h"
#include "mat4x4.hpp"
#include "vec3.hpp"
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
	protected:
		Model model;
		void UpdateMatrices();
		void UpdateModel();
	public:
		//metodos y atributos para scene graph
		std::vector<Entity2D*> children;
		Entity2D* parent = nullptr;
		void AddChild(Entity2D* entity);
		glm::mat4 GetLocalModelMatrix();
		void UpdateSelfAndChild();

		bool m_isDirty;
		void ComputeModelMatrix();
		void ComputeModelMatrix(const glm::mat4& parentGlobalModelMatrix);
		void SetLocalPosition(const glm::vec3& newPosition);
		const glm::mat4& GetModelMatrix();
		bool IsDirty();
		void ForceUpdateSelfAndChild();

		Transform transform;
		Entity2D();
		~Entity2D();
		void RotateX(float angle);
		void RotateY(float angle);
		void RotateZ(float angle);
		void Translate(float x, float y, float z);
		glm::vec2 Lerp(glm::vec2 a, glm::vec2 b, float t);
		void Scale(float x, float y, float z);
		glm::mat4 GetModel();
	};

}

#endif // !ENTITY2D_H

