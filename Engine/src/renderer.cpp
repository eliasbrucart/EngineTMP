#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "renderer.h"
#include "shader.h"

#include <iostream>

using namespace Engine;

Renderer::Renderer() {
}

Renderer::~Renderer() {
}

bool Renderer::InitializeGlew() {
	glewExperimental = GL_TRUE;
	glewInit();
	if (glewInit() != GLEW_OK) {
		std::cout << "Error in GLEW INIT" << std::endl;
		std::cout << glewGetErrorString(glewInit()) << std::endl;
		return false;
	}
	return true;
}

void Renderer::BeginFrame(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::EndFrame(GLFWwindow* window) {
	glfwSwapBuffers(window);
	glfwPollEvents();
}
void Renderer::GenerateVAO(unsigned int& vao) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}
void Renderer::BindVAO(unsigned int& vao) {
	glBindVertexArray(vao);
}

void Renderer::GenerateLightVAO(unsigned int& lightvao) {
	glGenVertexArrays(1, &lightvao);
	glBindVertexArray(lightvao);
}

void Renderer::BindLightVAO(unsigned int& lightvao) {
	glBindVertexArray(lightvao);
}

void Renderer::BindBufferLight(unsigned int& vbo) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void Renderer::BindVBO(unsigned int& vbo, float* vertices, int verticesAmmount) {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * verticesAmmount, vertices, GL_STATIC_DRAW);
}

void Renderer::BindLightVBO(unsigned int& lightvbo, float* vertices, int verticesAmmount) {
	glGenBuffers(1, &lightvbo);
	glBindBuffer(GL_ARRAY_BUFFER, lightvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Renderer::BindEBO(unsigned int& ebo, unsigned int* indices, int indicesAmmount) {
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * indicesAmmount, indices, GL_STATIC_DRAW);
}
void Engine::Renderer::UpdateBuffers(unsigned int& vbo, float* vertices, int verticesAmmount){
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * verticesAmmount, vertices, GL_STATIC_DRAW);
}
void Renderer::UnbindBuffers() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}
void Renderer::DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo, unsigned int& lightvao) {
	glDeleteVertexArrays(1, &vao);
	glDeleteVertexArrays(1, &lightvao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void Renderer::DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo) {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void Renderer::CreateAtribPointers(unsigned int shaderAttribIndex, int dataAmmount, int dataSize, int dataPosition) {
	glVertexAttribPointer(shaderAttribIndex, dataAmmount, GL_FLOAT, GL_FALSE, sizeof(float) * dataSize, (void*)(sizeof(float) * dataPosition));
	glEnableVertexAttribArray(shaderAttribIndex);
}

void Renderer::SetTexAttribPointer(unsigned int shaderID) {
	GLuint posAttrib = glGetAttribLocation(shaderID, "aPos");
	GLuint colorAttrib = glGetAttribLocation(shaderID, "aColor"); // no daba el valor correcto porque no usaba la variable en el main
	GLuint texAttrib = glGetAttribLocation(shaderID, "aTexCoord");
	glUniform1i((glGetUniformLocation(shaderID, "mainTexture")), 0);
	CreateAtribPointers(posAttrib, 3, 8, 0);
	CreateAtribPointers(colorAttrib, 3, 8, 3);
	CreateAtribPointers(texAttrib, 2, 8, 6);
}

void Renderer::Draw(Shader& shader, glm::mat4 model, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmount, unsigned int* indices, int indicesAmmount){
	BindVAO(vao);
	UpdateBuffers(vbo, vertices, verticesAmount);
	shader.SetVertexAttributes("position",9); //especificamos como leer los datos del vertice y se lo pasamos al shader
	shader.SetColorAttributes("color",9);
	//Crear en la clase shader un metodo para leer los nuevos datos de normales
	shader.SetNormalAttributes("aNormal",9);
	//Le pasamos al shdera la matriz modelo de cada shape
	shader.Use(model);
	//Temporal: Le pasamos al fragment shader un color del objeto y color de la luz, esto tiene que estar en la clase lighting cuando este
	glUniform3f(glGetUniformLocation(shader.GetID(), "objectColor"), 1.0f, 0.5f, 0.31f);
	//Aca le estamos seteando la posicion de la luz al uniforme del fragment shader, cuando este la clase light lista pasarlo para ahi.
	glDrawElements(GL_TRIANGLES, indicesAmmount, GL_UNSIGNED_INT, 0);
	UnbindBuffers();
}

void Renderer::DrawBasicLight(Shader& shader, glm::vec3 lightPos, glm::vec3 lightColor) {
	shader.Use();
	//light pos
	unsigned int lightPosLoc = glGetUniformLocation(shader.GetID(), "lightPos");
	glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
	//light color
	unsigned int lightColorLoc = glGetUniformLocation(shader.GetID(), "lightColor");
	glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));
	//Seteamos los valores del material que queremos lograr, seteamos los vectores del struct uniforme llamado Material
	//El Shader ahora toma estos valores del material para hacer los calculos pertinentes de la iluminacion
	//Cuando este la clase material pasarlo a su clase
	glUniform3f(glGetUniformLocation(shader.GetID(), "material.ambient"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(shader.GetID(), "material.diffuse"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(shader.GetID(), "material.specular"), 0.5f, 0.5f, 0.5f);
	glUniform1f(glGetUniformLocation(shader.GetID(), "material.shininess"), 32.0f);

	//Le pasamos a la variable uniforme light la intensidad de cada componente de la fuente de luz
	//Esto se hace para lograr un resultado mas realista del reflejo de la luz sobre el objeto 
	//y que tenga sentido el calculo de la luz con el material del mismo

	//jugamos con los valores de los componentes de la luz
	//Estos efectos extra que generamos y hacemos que la luz reaccione diferente al material del objeto
	//Pasarlos a Light class
	glm::vec3 lColor;
	lColor.x = sin(glfwGetTime() * 0.2f);
	lColor.y = sin(glfwGetTime() * 0.7f);
	lColor.z = sin(glfwGetTime() * 0.13f);

	glm::vec3 diffuseColor = lColor * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

	glUniform3f(glGetUniformLocation(shader.GetID(), "light.ambient"), ambientColor.x, ambientColor.y, ambientColor.z);
	glUniform3f(glGetUniformLocation(shader.GetID(), "light.diffuse"), diffuseColor.x, diffuseColor.y, diffuseColor.z);
	glUniform3f(glGetUniformLocation(shader.GetID(), "light.specular"), 1.0f, 1.0f, 1.0f);

	//unsigned int materialAmbientLoc = glGetUniformLocation(shader.GetID(), "material.ambient");
	//glUniform3fv(materialAmbientLoc, 1, glm::vec3(1.0f, 0.5f, 0.31f));
}

void Renderer::DrawSprite(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmount, unsigned int* indices, int indicesAmmount, glm::mat4 model) {
	BindVAO(vao);
	UpdateBuffers(vbo,vertices, verticesAmount);
	SetTexAttribPointer(shader.GetID());
	shader.Use(model);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	UnbindBuffers();
}

void Renderer::DrawLightCube(Shader& shader, glm::mat4 model, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmount, unsigned int* indices, int indicesAmmount) {
	BindVAO(vao);
	UpdateBuffers(vbo, vertices, verticesAmount);
	//Para crear los punteros de atributos de vertices (AttribPointer)
	shader.SetVertexAttributes("position",9);
	shader.SetNormalAttributes("aNormal", 9);
	//shader.SetColorAttributes("color", 6);
	shader.Use(model);
	glUniform3f(glGetUniformLocation(shader.GetID(), "objectColor"), 1.0f, 1.0f, 1.0f);
	//shader.SetColorAttributes("color",6);
	glDrawElements(GL_TRIANGLES, indicesAmmount, GL_UNSIGNED_INT, 0);
	UnbindBuffers();
}

void Renderer::DrawCamera(Shader& shader, glm::vec3 camPos, glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
	//unsigned int projectionLoc = glGetUniformLocation(shader.GetID(), "projection");

	unsigned int transformLoc = glGetUniformLocation(shader.GetID(), "model");
	unsigned int viewLoc = glGetUniformLocation(shader.GetID(), "view");
	unsigned int projectionLoc = glGetUniformLocation(shader.GetID(), "projection");
	//Pasamos la posicion de la camara para calcular la iluminacion specular
	unsigned int camPosLoc = glGetUniformLocation(shader.GetID(), "viewPos");
	shader.Use(model);
	glUniform3fv(camPosLoc, 1, glm::value_ptr(camPos));
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}


