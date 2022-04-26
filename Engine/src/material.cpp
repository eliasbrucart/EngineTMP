#include "material.h"
#include "GL/glew.h"

using namespace Engine;

Material::Material() {
	_ambient = glm::vec3(1.0f);
	_diffuse = glm::vec3(1.0f);
	_specular = glm::vec3(1.0f);
	_shininess = 32.0f;
	_type = MaterialType::lambert;
}

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) {
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
	_shininess = shininess;
	_type = MaterialType::lambert;
}

Material::Material(MaterialType type) {
	_type = type;
	//_ambient = glm::vec3(1.0f);
	//_diffuse = glm::vec3(1.0f);
	//_specular = glm::vec3(1.0f);
	//_shininess = 32.0f;
	//_type = MaterialType::lambert;
}

Material::~Material() {

}

void Material::SetAmbient(glm::vec3 ambient) {
	_ambient = ambient;
}

void Material::SetDiffuse(glm::vec3 diffuse) {
	_diffuse = diffuse;
}

void Material::SetSpecular(glm::vec3 specular) {
	_specular = specular;
}

void Material::SetShininess(float shininess) {
	_shininess = shininess;
}

void Material::SetMaterialType(MaterialType type){
	_type = type;
}

glm::vec3 Material::GetAmbient() {
	return _ambient;
}

glm::vec3 Material::GetDiffuse() {
	return _diffuse;
}

glm::vec3 Material::GetSpecular() {
	return _specular;
}

float Material::GetShininess() {
	return _shininess;
}

MaterialType Material::GetMaterialType() {
	return _type;
}

void Material::ApplyMaterial(Shader shader) {
	if (_type == MaterialType::esmerald) {
		SetAmbient(glm::vec3(0.0125f, 0.1745f, 0.0215f));
		SetDiffuse(glm::vec3(0.07568f, 0.61424f, 0.07568f));
		SetSpecular(glm::vec3(0.633f, 0.727811f, 0.633f));
		SetShininess(0.6f * 128.0f);
		unsigned int esmeraldAmbientLoc = glGetUniformLocation(shader.GetID(), "material.ambient");
		glUniform3fv(esmeraldAmbientLoc, 1, glm::value_ptr(_ambient));

		unsigned int esmeraldDiffuseLoc = glGetUniformLocation(shader.GetID(), "material.diffuse");
		glUniform3fv(esmeraldDiffuseLoc, 1, glm::value_ptr(_diffuse));

		unsigned int esmeraldSpecularLoc = glGetUniformLocation(shader.GetID(), "material.specular");
		glUniform3fv(esmeraldSpecularLoc, 1, glm::value_ptr(_specular));

		unsigned int esmeraldShininessLoc = glGetUniformLocation(shader.GetID(), "material.shininess");
		glUniform1f(esmeraldShininessLoc, _shininess);
	}
}