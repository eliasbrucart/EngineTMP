#ifndef ENTITY
#define ENTITY

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "export.h"
#include <vector>


namespace Engine
{
	class renderer;

	class ENGINE_API Entity{
	public:
		Entity();
		~Entity();
		void SetPos(glm::vec3 pos);
		void SetPos(float x, float y, float z);
		void SetRot(glm::vec3 rot);
		void SetRotRadians(glm::vec3 rot);
		void SetRot(float x, float y, float z);
		void SetScale(glm::vec3 localScale);
		void SetScale(float x, float y, float z);
		void SetColor(glm::vec3 color);
		void SetColor(float r, float g, float b);
		void UpdateWorldModelMatrix(glm::mat4 localModel);
		void InvertX();
		void InvertY();
		void InvertZ();
		void SetMatrix(glm::mat4 mat);

		void UseLocalMatrix();

		glm::vec3 GetColor();
		glm::vec3 GetPos();
		glm::vec3 GetPosFromTransformMatrix();
		glm::vec3 GetRot();
		glm::vec3 GetScale();
		glm::mat4 GetModelConst() const
		{
			return worldModel;
		}
		glm::vec3 GetRightConst() const
		{
			return worldModel[0];
		}
		glm::vec3 GetUpConst() const
		{
			return worldModel[1];
		}
		glm::vec3 GetForwardConst() const
		{
			return worldModel[2];
		}
		glm::vec3 GetForward();
		glm::vec3 GetPos(glm::mat4 mat);
		glm::vec3 GetRot(glm::mat4 mat);
		glm::vec3 GetScale(glm::mat4 mat);

		glm::vec3 ToEulerRad(glm::quat rot);
		glm::vec3 NormalizeAngles(glm::vec3 angles);
		float NormalizeAngle(float angle);
		glm::quat GetRotationByMatrix(glm::mat4 mat);
		glm::quat EulerToQuat(glm::vec3 euler);
		glm::vec3 QuatToVec(glm::quat quat, glm::vec3 vec);

		glm::mat4 GetModel();
		glm::mat4 GetLocalModel();

	protected:
		renderer* _renderer;

		//Transform transform;

		glm::vec3 v3localPos;
		glm::vec3 v3localRot;
		glm::vec3 v3localScale;

		glm::mat4 worldModel;
		glm::mat4 localModel;
		glm::mat4 parentModel;

		glm::mat4 localTranslate;
		glm::mat4 localRotateX;
		glm::mat4 localRotateY;
		glm::mat4 localRotateZ;
		glm::mat4 localScale;

		glm::vec3 color;

		unsigned int VAO, VBO, EBO, _vertices;

		void UpdateModelMatrix();
	private:
		void SetRotX(float x);
		void SetRotY(float y);
		void SetRotZ(float z);

		bool useLocalMatrix;
	};
}
#endif // !ENTITY