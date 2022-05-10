#include "light.h"
#include "GL/glew.h"

using namespace Engine;

Light::Light() : Entity2D(){
	_renderer = NULL;
}

Light::Light(Renderer* renderer, Shader shader) {
	_renderer = renderer;
	_shader = shader;
}

Light::Light(Renderer* renderer, Shader shader, LightType type) {
	_renderer = renderer;
	_shader = shader;
	_type = type;
}

Light::~Light() {

}

void Light::SetShader(Shader shader) {
	_shader = shader;
}

void Light::SetRenderer(Renderer* renderer) {
	_renderer = renderer;
}

void Light::Init() {
	if (_type == LightType::directional) {
		_direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	}
	//Inicializar la posicion de la light
}

void Light::SetDirection(glm::vec3 direction) {
	_direction = direction;
}

void Light::SetColor(float r, float g, float b) {
	_color = glm::vec3(r, g, b);
	//crear un metodo en la clase shader para setear el color de la variable uniforme lightColor
	//glUniform3f(glGetUniformLocation(_shader.GetID(), "lightColor"), r, g, b);
}

void Light::Draw() {
	//Pasarle al draw light de renderer el tipo de luz a mostrar
	//Dependiendo del tipo de luz, el renderer o clase shader manda a determinados uniforms
	//determinados datos para el uso del shader.
	_renderer->DrawBasicLight(_shader, transform.position, _color, _direction);
}