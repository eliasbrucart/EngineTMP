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

Light::~Light() {

}

void Light::SetShader(Shader shader) {
	_shader = shader;
}

void Light::SetRenderer(Renderer* renderer) {
	_renderer = renderer;
}

void Light::Init() {
	//Inicializar la posicion de la light
}

void Light::SetColor(float r, float g, float b) {
	_color = glm::vec3(r, g, b);
	//crear un metodo en la clase shader para setear el color de la variable uniforme lightColor
	//glUniform3f(glGetUniformLocation(_shader.GetID(), "lightColor"), r, g, b);
}

void Light::Draw() {
	_renderer->DrawBasicLight(_shader, transform.position, _color);
}