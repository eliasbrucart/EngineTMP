#include "light.h"
#include "GL/glew.h"

using namespace Engine;

Light::Light() : Entity2D(){
	_renderer = NULL;
}

Light::Light(Renderer* renderer, Shader shader) {
	_renderer = renderer;
	_shader = shader;
	_type = LightType::directional;
	_lightCount++;
}

Light::Light(Renderer* renderer, Shader shader, LightType type) {
	_renderer = renderer;
	_shader = shader;
	_type = type;
	if(_lightCount < 4)
		_lightCount++;
}

Light::~Light() {
	_lightCount--;
}

void Light::SetShader(Shader shader) {
	_shader = shader;
}

void Light::SetRenderer(Renderer* renderer) {
	_renderer = renderer;
}

void Light::Init() {
	if (_type == LightType::directional)
		_direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	if (_type == LightType::point) {
		_constant = 1.0f;
		_linear = 0.09f;
		_quadratic = 0.032f;
	}
	//Inicializar la posicion de la light
}

void Light::SetDirection(glm::vec3 direction) {
	_direction = direction;
}

void Light::SetAmbient(glm::vec3 ambient) {
	_ambient = ambient;
}

void Light::SetDiffuse(glm::vec3 diffuse) {
	_diffuse = diffuse;
}

void Light::SetSpecular(glm::vec3 specular) {
	_specular = specular;
}

void Light::SetConstant(float constant) {
	_constant = constant;
}

void Light::SetLinear(float linear) {
	_linear = linear;
}

void Light::SetQuadratic(float quadratic) {
	_quadratic = quadratic;
}

//Agregar seters de constant, linear y quadratic para las luces point

void Light::SetColor(float r, float g, float b) {
	_color = glm::vec3(r, g, b);
	//crear un metodo en la clase shader para setear el color de la variable uniforme lightColor
	//glUniform3f(glGetUniformLocation(_shader.GetID(), "lightColor"), r, g, b);
}

void Light::Draw() {
	//Pasarle al draw light de renderer el tipo de luz a mostrar
	//Dependiendo del tipo de luz, el renderer o clase shader manda a determinados uniforms
	//determinados datos para el uso del shader.
	if(_type == LightType::directional)
		_renderer->DrawDirectionalLight(_shader, transform.position, _color, _direction);
	if(_type == LightType::point)
		_renderer->DrawPointLight(_shader, transform.position, _color, _ambient, _diffuse, _specular, _constant, _linear, _quadratic ,_lightCount);
}