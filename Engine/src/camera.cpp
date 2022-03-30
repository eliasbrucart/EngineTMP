#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "camera.h"
#include "gtc/matrix_transform.hpp"
#include "mat4x4.hpp"
#include "gtc/type_ptr.hpp"
#include "renderer.h"

using namespace Engine;

Camera::Camera(Renderer* renderer, ProjectionType type){
	_renderer = renderer;
	_view = glm::mat4(1.0);
	_projection = glm::mat4(1.0);
	_type = type;
	//_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	//_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	//_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera(){
}

void Camera::SetView(glm::vec3 direction, glm::vec3 up){
	_view = glm::translate(_view, _cameraPos);
}

void Camera::SetProjection(ProjectionType type){
	_type = type;
	switch (_type)
	{
	case ProjectionType::orthographic:
		_projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, 0.01f, 100.0f);
		break;
	case ProjectionType::perspective:
		_projection = glm::perspective(glm::radians(45.0f), GLfloat(1280.0f) / GLfloat(720.0f), 1.0f, 100.0f);
		break;
	default:
		break;
	}
}

//Le pasamos las matrices al shader y lo modificamos
void Camera::Init(Shader& shader, GLFWwindow* window){
	unsigned int transformLoc = glGetUniformLocation(shader.GetID(), "model");
	unsigned int viewLoc = glGetUniformLocation(shader.GetID(), "view");
	unsigned int projLoc = glGetUniformLocation(shader.GetID(), "projection");
	shader.Use();
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(GetModel()));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(GetProjection()));
	inputCam.SetWindow(window);
}

void Camera::SetCameraPos(glm::vec3 cameraPos) {
	_cameraPos = cameraPos;
}

void Camera::SetCameraFront(glm::vec3 cameraFront) {
	_cameraFront = cameraFront;
}

void Camera::SetCameraUp(glm::vec3 cameraUp) {
	_cameraUp = cameraUp;
}

glm::vec3 Camera::GetCameraPos() {
	return _cameraPos;
}

glm::vec3 Camera::GetCameraFront() {
	return _cameraFront;
}

glm::vec3 Camera::GetCameraUp() {
	return _cameraUp;
}

void Camera::SetLookAt() {
	_view = glm::lookAt(transform.position, transform.position + _cameraFront, _cameraUp);
}

void Camera::RotateCamera() {
	const float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	_view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}

glm::mat4 Camera::GetView(){
	return _view;
}

glm::mat4 Camera::GetProjection(){
	return _projection;
}

glm::mat4 Engine::Camera::GetMVP(){
	return GetProjection() * GetView() * GetModel();
}

ProjectionType Camera::GetProjectionType(){
	return _type;
}

void Camera::Draw(Shader& shader){
	_renderer->DrawCamera(shader, GetModel(), GetView(), GetProjection());
}
