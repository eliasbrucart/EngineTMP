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

	if (_type == MaterialType::lambert) {
		SetAmbient(glm::vec3(1.0f));
		SetDiffuse(glm::vec3(1.0f));
		SetSpecular(glm::vec3(1.0f));
		SetShininess(32.0f);
		unsigned int esmeraldAmbientLoc = glGetUniformLocation(shader.GetID(), "material.ambient");
		glUniform3fv(esmeraldAmbientLoc, 1, glm::value_ptr(_ambient));

		unsigned int esmeraldDiffuseLoc = glGetUniformLocation(shader.GetID(), "material.diffuse");
		glUniform3fv(esmeraldDiffuseLoc, 1, glm::value_ptr(_diffuse));

		unsigned int esmeraldSpecularLoc = glGetUniformLocation(shader.GetID(), "material.specular");
		glUniform3fv(esmeraldSpecularLoc, 1, glm::value_ptr(_specular));

		unsigned int esmeraldShininessLoc = glGetUniformLocation(shader.GetID(), "material.shininess");
		glUniform1f(esmeraldShininessLoc, _shininess);

		unsigned int materialDiffuseLoc = glGetUniformLocation(shader.GetID(), "material.diffuse");
		glUniform1f(materialDiffuseLoc, 0);
	}

	if (_type == MaterialType::lambertPro) {
		SetAmbient(glm::vec3(1.0f));
		SetDiffuse(glm::vec3(1.0f));
		SetSpecular(glm::vec3(1.0f));
		SetShininess(32.0f);
		unsigned int esmeraldAmbientLoc = glGetUniformLocation(shader.GetID(), "materialPro.ambient");
		glUniform3fv(esmeraldAmbientLoc, 1, glm::value_ptr(_ambient));

		unsigned int esmeraldDiffuseLoc = glGetUniformLocation(shader.GetID(), "materialPro.diffuse");
		glUniform3fv(esmeraldDiffuseLoc, 1, glm::value_ptr(_diffuse));

		unsigned int esmeraldSpecularLoc = glGetUniformLocation(shader.GetID(), "materialPro.specular");
		glUniform3fv(esmeraldSpecularLoc, 1, glm::value_ptr(_specular));

		unsigned int esmeraldShininessLoc = glGetUniformLocation(shader.GetID(), "materialPro.shininess");
		glUniform1f(esmeraldShininessLoc, _shininess);

		unsigned int materialDiffuseLoc = glGetUniformLocation(shader.GetID(), "materialPro.diffuse");
		glUniform1f(materialDiffuseLoc, 0);
	}

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

	if (_type == MaterialType::pearl) {
		SetAmbient(glm::vec3(0.25f, 0.20725f, 0.20725f));
		SetDiffuse(glm::vec3(1.0f, 0.829f, 0.829f));
		SetSpecular(glm::vec3(0.296648f, 0.296648f, 0.296648f));
		SetShininess(0.088f * 128.0f);
		unsigned int pearlAmbientLoc = glGetUniformLocation(shader.GetID(), "material.ambient");
		glUniform3fv(pearlAmbientLoc, 1, glm::value_ptr(_ambient));

		unsigned int pearlDiffuseLoc = glGetUniformLocation(shader.GetID(), "material.diffuse");
		glUniform3fv(pearlDiffuseLoc, 1, glm::value_ptr(_diffuse));

		unsigned int pearlSpecularLoc = glGetUniformLocation(shader.GetID(), "material.specular");
		glUniform3fv(pearlSpecularLoc, 1, glm::value_ptr(_specular));

		unsigned int pearlShininessLoc = glGetUniformLocation(shader.GetID(), "material.shininess");
		glUniform1f(pearlShininessLoc, _shininess);
	}

	if (_type == MaterialType::bronze) {
		SetAmbient(glm::vec3(0.2125f, 0.1275f, 0.054f));
		SetDiffuse(glm::vec3(0.714f, 0.4284f, 0.18144f));
		SetSpecular(glm::vec3(0.393548f, 0.271906f, 0.166721f));
		SetShininess(0.088f * 128.0f);
		unsigned int bronzeAmbientLoc = glGetUniformLocation(shader.GetID(), "material.ambient");
		glUniform3fv(bronzeAmbientLoc, 1, glm::value_ptr(_ambient));

		unsigned int bronzeDiffuseLoc = glGetUniformLocation(shader.GetID(), "material.diffuse");
		glUniform3fv(bronzeDiffuseLoc, 1, glm::value_ptr(_diffuse));

		unsigned int bronzeSpecularLoc = glGetUniformLocation(shader.GetID(), "material.specular");
		glUniform3fv(bronzeSpecularLoc, 1, glm::value_ptr(_specular));

		unsigned int bronzeShininessLoc = glGetUniformLocation(shader.GetID(), "material.shininess");
		glUniform1f(bronzeShininessLoc, _shininess);
	}

	if (_type == MaterialType::gold) {
		SetAmbient(glm::vec3(0.24725f, 0.1995f, 0.0745f));
		SetDiffuse(glm::vec3(0.75164f, 0.60648f, 0.22648f));
		SetSpecular(glm::vec3(0.628281f, 0.555802f, 0.366065f));
		SetShininess(0.4f * 128.0f);
		unsigned int goldAmbientLoc = glGetUniformLocation(shader.GetID(), "material.ambient");
		glUniform3fv(goldAmbientLoc, 1, glm::value_ptr(_ambient));

		unsigned int goldDiffuseLoc = glGetUniformLocation(shader.GetID(), "material.diffuse");
		glUniform3fv(goldDiffuseLoc, 1, glm::value_ptr(_diffuse));

		unsigned int goldSpecularLoc = glGetUniformLocation(shader.GetID(), "material.specular");
		glUniform3fv(goldSpecularLoc, 1, glm::value_ptr(_specular));

		unsigned int goldShininessLoc = glGetUniformLocation(shader.GetID(), "material.shininess");
		glUniform1f(goldShininessLoc, _shininess);
	}

	if (_type == MaterialType::cyan_plastic) {
		SetAmbient(glm::vec3(0.0f, 0.1f, 0.06f));
		SetDiffuse(glm::vec3(0.0f, 0.50980392f, 0.50980392f));
		SetSpecular(glm::vec3(0.50196078f, 0.50196078f, 0.50196078f));
		SetShininess(0.25f * 128.0f);
		unsigned int cyanPlasticAmbientLoc = glGetUniformLocation(shader.GetID(), "material.ambient");
		glUniform3fv(cyanPlasticAmbientLoc, 1, glm::value_ptr(_ambient));

		unsigned int cyanPlasticDiffuseLoc = glGetUniformLocation(shader.GetID(), "material.diffuse");
		glUniform3fv(cyanPlasticDiffuseLoc, 1, glm::value_ptr(_diffuse));

		unsigned int cyanPlasticSpecularLoc = glGetUniformLocation(shader.GetID(), "material.specular");
		glUniform3fv(cyanPlasticSpecularLoc, 1, glm::value_ptr(_specular));

		unsigned int cyanPlasticShininessLoc = glGetUniformLocation(shader.GetID(), "material.shininess");
		glUniform1f(cyanPlasticShininessLoc, _shininess);
	}

	if (_type == MaterialType::red_plastic) {
		SetAmbient(glm::vec3(0.0f, 0.0f, 0.0f));
		SetDiffuse(glm::vec3(0.5f, 0.0f, 0.0f));
		SetSpecular(glm::vec3(0.7f, 0.6f, 0.6f));
		SetShininess(0.25f * 128.0f);
		unsigned int redPlasticAmbientLoc = glGetUniformLocation(shader.GetID(), "material.ambient");
		glUniform3fv(redPlasticAmbientLoc, 1, glm::value_ptr(_ambient));

		unsigned int redPlasticDiffuseLoc = glGetUniformLocation(shader.GetID(), "material.diffuse");
		glUniform3fv(redPlasticDiffuseLoc, 1, glm::value_ptr(_diffuse));

		unsigned int redPlasticSpecularLoc = glGetUniformLocation(shader.GetID(), "material.specular");
		glUniform3fv(redPlasticSpecularLoc, 1, glm::value_ptr(_specular));

		unsigned int redPlasticShininessLoc = glGetUniformLocation(shader.GetID(), "material.shininess");
		glUniform1f(redPlasticShininessLoc, _shininess);
	}

	if (_type == MaterialType::green_rubber) {
		SetAmbient(glm::vec3(0.0f, 0.05f, 0.0f));
		SetDiffuse(glm::vec3(0.4f, 0.5f, 0.4f));
		SetSpecular(glm::vec3(0.04f, 0.7f, 0.04f));
		SetShininess(0.078125f * 128.0f);
		unsigned int greenRubberAmbientLoc = glGetUniformLocation(shader.GetID(), "material.ambient");
		glUniform3fv(greenRubberAmbientLoc, 1, glm::value_ptr(_ambient));

		unsigned int greenRubberDiffuseLoc = glGetUniformLocation(shader.GetID(), "material.diffuse");
		glUniform3fv(greenRubberDiffuseLoc, 1, glm::value_ptr(_diffuse));

		unsigned int greenRubberSpecularLoc = glGetUniformLocation(shader.GetID(), "material.specular");
		glUniform3fv(greenRubberSpecularLoc, 1, glm::value_ptr(_specular));

		unsigned int greenRubberShininessLoc = glGetUniformLocation(shader.GetID(), "material.shininess");
		glUniform1f(greenRubberShininessLoc, _shininess);
	}

	if (_type == MaterialType::yellow_rubber) {
		SetAmbient(glm::vec3(0.05f, 0.05f, 0.0f));
		SetDiffuse(glm::vec3(0.5f, 0.5f, 0.4f));
		SetSpecular(glm::vec3(0.7f, 0.7f, 0.04f));
		SetShininess(0.078125f * 128.0f);
		unsigned int yellowRubberAmbientLoc = glGetUniformLocation(shader.GetID(), "material.ambient");
		glUniform3fv(yellowRubberAmbientLoc, 1, glm::value_ptr(_ambient));

		unsigned int yellowRubberDiffuseLoc = glGetUniformLocation(shader.GetID(), "material.diffuse");
		glUniform3fv(yellowRubberDiffuseLoc, 1, glm::value_ptr(_diffuse));

		unsigned int yellowRubberSpecularLoc = glGetUniformLocation(shader.GetID(), "material.specular");
		glUniform3fv(yellowRubberSpecularLoc, 1, glm::value_ptr(_specular));

		unsigned int yellowRubberShininessLoc = glGetUniformLocation(shader.GetID(), "material.shininess");
		glUniform1f(yellowRubberShininessLoc, _shininess);
	}
}