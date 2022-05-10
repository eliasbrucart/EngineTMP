#ifndef LIGHT_H
#define LIGHT_H
#include "export.h"
#include "entity2D.h"
#include "shader.h"
#include "renderer.h"

namespace Engine {
	enum class ENGINE_API LightType {
		directional, point, spot
	};
	class ENGINE_API Light : public Entity2D {
	private:
		Shader _shader;
		Renderer* _renderer;
		glm::vec3 _direction;
		float _constant;
		float _linear;
		float _quadratic;
		glm::vec3 _color;
		LightType _type;
	public:
		Light();
		Light(Renderer* renderer, Shader shader);
		Light(Renderer* renderer, Shader shader, LightType type);
		~Light();
		void SetShader(Shader shader);
		void SetRenderer(Renderer* renderer);
		void Init();
		void SetDirection(glm::vec3 direction);
		void SetColor(float r, float g, float b);
		void Draw();
	};
}

#endif