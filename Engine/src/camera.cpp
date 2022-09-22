#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "camera.h"
#include "gtc/matrix_transform.hpp"
#include "mat4x4.hpp"
#include "gtc/type_ptr.hpp"
#include "renderer.h"

using namespace Engine;


Camera::Camera(Renderer* renderer, ProjectionType type, CamMode mode){
	_renderer = renderer;
	_view = glm::mat4(1.0);
	_projection = glm::mat4(1.0);
	_type = type;
	_yaw = -90.0f;
	_pitch = 0.0f;
	_firstMouse = true;
	_mode = mode;
	_rotationAngle = 5.0f;
	_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera(){
}

void Camera::SetView(glm::vec3 direction, glm::vec3 up){
	_view = glm::translate(_view, transform.position);
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
	
	//glfwSetCursorPosCallback(window, mouse_callback);
}

void Camera::SetCameraMode(CamMode mode) {
	_mode = mode;
}

void Camera::SetCameraFront(glm::vec3 cameraFront) {
	_cameraFront = cameraFront;
}

void Camera::SetCameraUp(glm::vec3 cameraUp) {
	_cameraUp = cameraUp;
}

void Camera::SetYaw(float yaw) {
	_yaw = yaw;
}

void Camera::SetPitch(float pitch) {
	_pitch = pitch;
}

float Camera::GetYaw() {
	return _yaw;
}

float Camera::GetPitch() {
	return _pitch;
}

glm::vec3 Camera::GetCameraFront() {
	return _cameraFront;
}

glm::vec3 Camera::GetCameraUp() {
	return _cameraUp;
}

void Camera::SetLookAt(glm::vec3 forward) {
	if(_mode == CamMode::firstPerson)
		_view = glm::lookAt(transform.position, transform.position +  _cameraFront, _cameraUp);
	else if (_mode == CamMode::thirdPerson) {
		_view = glm::lookAt(transform.position, forward, _cameraUp);
	}
}

void Camera::FollowTarget(glm::vec3 positionTarget) {
	if (_mode == CamMode::thirdPerson) {
		//En todos los frames estamos seteando la posicion de la camara
		transform.position.x = positionTarget.x;
		transform.position.y = positionTarget.y + 10.0f;
		transform.position.z = positionTarget.z + 20.0f;
		RotatePitch(-10.0f);
		float radius = 30.0f;
		if (inputCam.GetKey(KeyCode::R)) {
			transform.position.x = positionTarget.x + sin(_rotationAngle * glfwGetTime()) * radius;
			transform.position.z = positionTarget.z + cos(_rotationAngle * glfwGetTime()) * radius;
		}
		SetLookAt(positionTarget);
	}
}

void Camera::UpdateRotation() {
	//Esto es para movimiento del mouse
	//float xpos = static_cast<float>(posX);
	//float ypos = static_cast<float>(posY);
	//
	//if (_firstMouse) {
	//	SetLastX(xpos);
	//	SetLastY(ypos);
	//	_firstMouse = false;
	//}
	//
	//float xoffset = xpos - GetLastX();
	//float yoffset = GetLastY() - ypos;
	//
	//SetLastX(xpos);
	//SetLastY(ypos);
	//
	//float sensitivity = 0.1f;
	//xoffset *= sensitivity;
	//yoffset *= sensitivity;
	//
	//_yaw += xoffset;
	//_pitch += yoffset;

	//glm::vec3 front;
	_cameraFront.x = glm::cos(glm::radians(transform.rotation.y)) * glm::cos(glm::radians(transform.rotation.x));
	_cameraFront.y = glm::sin(glm::radians(transform.rotation.x));
	_cameraFront.z = glm::sin(glm::radians(transform.rotation.y)) * glm::cos(glm::radians(transform.rotation.x));
	SetCameraFront(glm::normalize(_cameraFront));					//este vector es el world up
	_cameraRight = glm::normalize(glm::cross(_cameraFront, _worldUp));
	_cameraUp = glm::normalize(glm::cross(_cameraRight, _cameraFront));
	//glm::vec3 _right = glm::normalize(glm::cross(_cameraFront, _cameraUp));
	//_cameraUp = glm::normalize(glm::cross(_right, _cameraFront));
	//limitamos que el pitch se pase de rotacion
	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;
	
	//float camX = sin(glfwGetTime()) * radius;
	//float camZ = cos(glfwGetTime()) * radius;
	//_view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}

void Camera::RotateYaw(float yaw) {
	transform.rotation.y += yaw;
}

void Camera::RotatePitch(float pitch) {
	transform.rotation.x += pitch;
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

Frustum Camera::CreateFrustumFromCamera(float aspect, float fovY, float zNear, float zFar) {
	//Frustum frustum;
	const float halfVSide = zFar * tanf(fovY * 0.5f);
	const float halfHSide = halfVSide * aspect;
	const glm::vec3 frontMultFar = zFar * _cameraFront;

	_frustum.nearFace = {transform.position + zNear * _cameraFront, _cameraFront};
	_frustum.farFace = {transform.position + frontMultFar , -_cameraFront};
	_frustum.rightFace = {transform.position, glm::cross(_cameraUp, frontMultFar + _cameraRight * halfHSide)};
	_frustum.leftFace = {transform.position, glm::cross(frontMultFar - _cameraRight * halfHSide, _cameraUp)};
	_frustum.topFace = {transform.position, glm::cross(_cameraRight, frontMultFar - _cameraUp * halfVSide)};
	_frustum.bottomFace = { transform.position, glm::cross(frontMultFar + _cameraUp * halfVSide, _cameraRight) };

	std::cout << "_camera right x: " << _cameraRight.x << std::endl;
	std::cout << "_camera right y: " << _cameraRight.y << std::endl;
	std::cout << "_camera right z: " << _cameraRight.z << std::endl;

	return _frustum;
}

Plane Camera::GetNear() {
	return _frustum.nearFace;
}

Plane Camera::GetLeft() {
	return _frustum.leftFace;
}

Plane Camera::GetRight() {
	return _frustum.rightFace;
}

Plane Camera::GetFar() {
	return _frustum.farFace;
}

void Camera::Draw(Shader& shader){
	_renderer->DrawCamera(shader, transform.position, GetModel(), GetView(), GetProjection());
}
