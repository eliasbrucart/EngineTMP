#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "base.h"
using namespace Engine;


Base::Base(){
	_renderer = new Renderer();
	_window = new Window(1280, 720);
	_camera = new Camera(_renderer, ProjectionType::perspective);
	collisionmanager = new CollisionManager();
}

Base::~Base() {
	if (_renderer != NULL) {
		delete _renderer;
		_renderer = NULL;
	}
	if (_window != NULL)
	{
		delete _window;
		_window = NULL;
	}
	if (_camera != NULL) {
		delete _camera;
		_camera = NULL;
	}
	if (collisionmanager != NULL) {
		delete collisionmanager;
		collisionmanager = NULL;
	}
}

void Base::Execute()
{
	Init();
	Update();
	Unload();
}

int Base::Init(){
	_window->CreateWindow("Unreal Engine pero con Intellisense");

	if (!_renderer->InitializeGlew()) {
		return 0;
	}

	basicShader.Create("..//Engine//src//Shaders//vertex.vert", "..//Engine//src//Shaders//fragment.frag");
	textureShader.Create("..//Engine//src//Shaders//texture_vert.vert", "..//Engine//src//Shaders//texture_frag.frag");
	glEnable(GL_DEPTH_TEST);
	//_camera->SetView(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	_camera->SetProjection(ProjectionType::perspective);
	_camera->Init(basicShader, _window->GetWindow());
	//_camera->Init(textureShader, _window->GetWindow());
	//_camera->SetLookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	_camera->SetCameraPos(glm::vec3(0.0f, 0.0f, 3.0f));
	//_camera->transform.position = glm::vec3(0.0f, 0.0f, 3.0f);
	_camera->SetCameraFront(glm::vec3(0.0, 0.0, -1.0f));
	_camera->SetCameraUp(glm::vec3(0.0, 1.0, 0.0));
	input.SetWindow(_window->GetWindow());

	time.Reset();

	InitGame();
}

void Base::Update(){
	float speed = 50.0f;
	float rotationSpeed = 50.0f;
	while (!glfwWindowShouldClose(_window->GetWindow())){
		_renderer->BeginFrame(0.0f,0.0f,0.0f);
		//_camera->transform.position.x += speed;
		//std::cout << _camera->transform.position.x << std::endl;
		UpdateGame();
		if (input.GetKey(KeyCode::W))
			_camera->transform.position += (speed * time.GetDeltaTime()) * _camera->GetCameraFront();

		if (input.GetKey(KeyCode::S))
			_camera->transform.position -= (speed * time.GetDeltaTime()) * _camera->GetCameraFront();

		if (input.GetKey(KeyCode::A))
			_camera->transform.position -= glm::normalize(glm::cross(_camera->GetCameraFront(), _camera->GetCameraUp())) * (speed * time.GetDeltaTime());

		if (input.GetKey(KeyCode::D))
			_camera->transform.position += glm::normalize(glm::cross(_camera->GetCameraFront(), _camera->GetCameraUp())) * (speed * time.GetDeltaTime());

		if (input.GetKey(KeyCode::DOWN)) {
			rotationSpeed += rotationSpeed * time.GetDeltaTime();
			_camera->RotatePitch(-rotationSpeed);
		}

		if (input.GetKey(KeyCode::UP)) {
			rotationSpeed += rotationSpeed * time.GetDeltaTime();
			_camera->RotatePitch(rotationSpeed);
		}

		if (input.GetKey(KeyCode::LEFT)) {
			rotationSpeed += rotationSpeed * time.GetDeltaTime();
			_camera->RotateYaw(-rotationSpeed);
		}

		if (input.GetKey(KeyCode::RIGHT)) {
			rotationSpeed += rotationSpeed * time.GetDeltaTime();
			_camera->RotateYaw(rotationSpeed);
		}
		//_camera->MoveCamera();
		_camera->UpdateRotation();
		_camera->SetLookAt();
		_camera->Draw(basicShader);
		//_camera->Draw(textureShader);
		time.CalculateFPS();
		time.Tick();
		_renderer->EndFrame(_window->GetWindow());
	}
}

void Base::Unload(){
	UnloadGame();
	glfwTerminate();
}

Renderer* Base::GetRenderer(){
	return _renderer;
}

Window* Base::GetWindow(){
	return _window;
}