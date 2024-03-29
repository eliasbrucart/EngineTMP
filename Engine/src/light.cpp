#include "light.h"
#include "GL/glew.h"

using namespace Engine;

//Esta clase deejarla como Base y crear derivadas para cada tipo de light

Light::Light() : Entity2D(){
	_renderer = NULL;
}

Light::Light(Renderer* renderer, Shader shader) : Entity2D() {
	_renderer = renderer;
	_shader = shader;
	_type = LightType::directional;
	_lightCount++;
}

Light::Light(Renderer* renderer, Shader shader, LightType type) : Entity2D() {
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
	if (_type == LightType::directional) {
		_direction = glm::vec3(-0.2f, -1.0f, -0.3f);
		_ambient = glm::vec3(0.05f);
		_diffuse = glm::vec3(0.04f);
		_ambient = glm::vec3(0.4f);
		_turnOn = true;
	}
	if (_type == LightType::point) {
		_ambient = glm::vec3(0.2f);
		_diffuse = glm::vec3(0.5f);
		_specular = glm::vec3(1.0f);
		_constant = 1.0f;
		_linear = 0.09f;
		_quadratic = 0.032f;
		_turnOn = true;
	}
	if (_type == LightType::spot) {
		_direction = glm::vec3(0.0, 0.0, -2.0f);
		_ambient = glm::vec3(0.0f);
		_diffuse = glm::vec3(1.0f);
		_specular = glm::vec3(1.0f);
		_constant = 1.0f;
		_linear = 0.09f;
		_quadratic = 0.032f;
		_cutOff = glm::cos(glm::radians(12.5f));
		_outerCutOff = glm::cos(glm::radians(15.0f));
		_turnOn = true;
	}
}

void Light::SetPosition(glm::vec3 position) {
	_position = position;
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

void Light::SetCutOff(float cutOff) {
	_cutOff = cutOff;
}

void Light::SetOuterCutOff(float outerCutOff) {
	_outerCutOff = outerCutOff;
}

void Light::SetTurnOnState(bool state) {
	_turnOn = state;
}

bool Light::GetTurnState() {
	return _turnOn;
}

void Light::SetColor(float r, float g, float b) {
	_color = glm::vec3(r, g, b);
	//crear un metodo en la clase shader para setear el color de la variable uniforme lightColor
	//glUniform3f(glGetUniformLocation(_shader.GetID(), "lightColor"), r, g, b);
}

void Light::DrawDirectionalLight() {
	if (_type == LightType::directional) {
		if (!_turnOn) {
			_ambient = glm::vec3(0.0f);
			_diffuse = glm::vec3(0.0f);
			_specular = glm::vec3(0.0f);
		}
		else {
			_ambient = glm::vec3(0.05f);
			_diffuse = glm::vec3(0.04f);
			_ambient = glm::vec3(0.4f);
		}
		_renderer->DrawDirectionalLight(_shader, _position, _color, _direction, _ambient, _diffuse, _specular);
	}
}

void Light::DrawPointLight(int numberOfLight) {
	//Pasarle al draw light de renderer el tipo de luz a mostrar
	//Dependiendo del tipo de luz, el renderer o clase shader manda a determinados uniforms
	//determinados datos para el uso del shader.
	//if(_type == LightType::directional)
	//	_renderer->DrawDirectionalLight(_shader, _position, _color, _direction);
	if (_type == LightType::point) {
		if (!_turnOn) {
			_ambient = glm::vec3(0.0f);
			_diffuse = glm::vec3(0.0f);
			_specular = glm::vec3(0.0f);
		}
		else
		{
			_ambient = glm::vec3(0.2f);
			_diffuse = glm::vec3(0.5f);
			_specular = glm::vec3(1.0f);
		}
		_renderer->DrawPointLight(_shader, _position, _color, _ambient, _diffuse, _specular, _constant, _linear, _quadratic, _lightCount, numberOfLight);
	}
}

void Light::DrawSpotLight() {
	if (_type == LightType::spot) {
		if (!_turnOn) {
			_ambient = glm::vec3(0.0f);
			_diffuse = glm::vec3(0.0f);
			_specular = glm::vec3(0.0f);
		}
		else
		{
			_ambient = glm::vec3(0.0f);
			_diffuse = glm::vec3(1.0f);
			_specular = glm::vec3(1.0f);
		}
		_renderer->DrawSpotLight(_shader, transform.position, _direction, _ambient, _diffuse, _specular, _constant, _linear, _quadratic, _cutOff, _outerCutOff);
	}
}