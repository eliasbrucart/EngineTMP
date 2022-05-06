#ifndef MATERIAL_H
#define MATERIAL_H
#include "export.h"
#include "glm.hpp"
#include "vec3.hpp"
#include "shader.h"

namespace Engine {
	enum class ENGINE_API MaterialType {
		lambert,
		lambertPro,
		esmerald,
		jade,
		obsidian,
		pearl,
		ruby,
		turquoise,
		brass,
		bronze,
		chrome,
		copper,
		gold,
		silver,
		black_plastic,
		cyan_plastic,
		green_plastic,
		red_plastic,
		white_plastic,
		yellow_plastic,
		black_rubber,
		cyan_rubber,
		green_rubber,
		red_rubber,
		white_rubber,
		yellow_rubber
	};
	class ENGINE_API Material {
	private:
		glm::vec3 _ambient;
		glm::vec3 _diffuse;
		glm::vec3 _specular;
		float _shininess;
		MaterialType _type;
	public:
		Material();
		Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
		Material(MaterialType type);
		~Material();
		void SetAmbient(glm::vec3 ambient);
		void SetDiffuse(glm::vec3 diffuse);
		void SetSpecular(glm::vec3 specular);
		void SetShininess(float shininess);
		void SetMaterialType(MaterialType type);
		glm::vec3 GetAmbient();
		glm::vec3 GetDiffuse();
		glm::vec3 GetSpecular();
		float GetShininess();
		MaterialType GetMaterialType();
		void ApplyMaterial(Shader shader);
	};
}

#endif