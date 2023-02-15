#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "base.h"
using namespace Engine;


Base::Base(){
	_renderer = new Renderer();
	_window = new Window(1280, 720);
	_camera = new Camera(_renderer, ProjectionType::perspective, CamMode::firstPerson);
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
	if (_modelMobile != NULL) {
		delete _modelMobile;
		_modelMobile = NULL;
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
	//textureShader.Create("..//Engine//src//Shaders//texture_vert.vert", "..//Engine//src//Shaders//texture_frag.frag");
	stbi_set_flip_vertically_on_load(true);
	//_renderer->SetShader(basicShader);
	glEnable(GL_DEPTH_TEST);
	//_camera->SetView(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	_camera->SetProjection(ProjectionType::perspective);
	_camera->Init(basicShader, _window->GetWindow());
	//_camera->Init(textureShader, _window->GetWindow());
	//_camera->SetLookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//_camera->SetCameraPos(glm::vec3(0.0f, 0.0f, 5.0f));
	_camera->transform.position = glm::vec3(0.0f, 0.0f, 3.0f);
	_camera->SetCameraFront(glm::vec3(0.0, 0.0, -2.0f));
	_camera->SetCameraUp(glm::vec3(0.0, 1.0, 0.0));
	input.SetWindow(_window->GetWindow());

	time.Reset();

	InitGame();
#pragma region Init
	_modelMobile->GetChildrens()[4]->SetMeshPos(0.0f, 0.0f, 1.0f, 0); //Cabeza
	_modelMobile->GetChildrens()[4]->SetMeshScale(3.0f, 1.0f, 3.0f, 0);
	_modelMobile->GetChildrens()[1]->SetMeshPos(0.0f, 0.0f, -2.5f, 0); //Cadera
	_modelMobile->GetChildrens()[3]->SetMeshPos(0.0f, 0.0f, -1.0f, 0); //Torzo
	_modelMobile->GetChildrens()[3]->SetMeshScale(0.3f, 0.4f, 1.0f, 0);
	//
	_modelMobile->GetChildrens()[5]->SetMeshPos(0.0f, -1.4f, -1.0f, 0); //Brazo izquiedo
	_modelMobile->GetChildrens()[5]->SetMeshScale(0.6f, 1.9f, 0.6f, 0);
	_modelMobile->GetChildrens()[2]->SetMeshPos(0.0f, 1.5f, -1.0f, 0); //Brazo derecho
	
	_modelMobile->GetChildrens()[0]->SetMeshPos(0.0f, 3.0f, -1.0f, 0); //Mano derecha
	_modelMobile->GetChildrens()[6]->SetMeshPos(0.0f, -3.0f, -1.0f, 0); //Mano izquierda
	_modelMobile->GetChildrens()[6]->SetMeshScale(1.01f, 1.0f, 0.85f, 0);
	
	_modelMobile->GetChildrens()[8]->SetMeshPos(0.0f, 0.7f, -3.7f, 0); //Pie derecho
	_modelMobile->GetChildrens()[8]->SetMeshScale(0.5f, 0.5f, 1.20f, 0);
	_modelMobile->GetChildrens()[7]->SetMeshPos(0.0f, -0.7f, -3.7f, 0); //Pie izquierdo
	_modelMobile->GetChildrens()[7]->SetMeshScale(0.5f, 0.5f, 1.0f, 0);
	//
	_modelMobile->SetRotRadians(glm::vec3(270.0f, 0.0f, 0.0f));
	//
	//_modelMobile->GenerateAABB();
#pragma endregion
}

void Base::Update(){
	float speed = 50.0f;
	float rotationSpeed = 100.0f; //dejamos como esta
	while (!glfwWindowShouldClose(_window->GetWindow())){
		_renderer->BeginFrame(0.0f,0.0f,0.0f);
		//_camera->transform.position.x += speed;
		//std::cout << _camera->transform.position.x << std::endl;
		UpdateGame();
		if (_modelMobile->GetChildrens()[0]->GetCanDraw()) {
			_modelMobile->GetChildrens()[2]->SetCanDraw(true);
			_modelMobile->GetChildrens()[3]->SetCanDraw(true);
		}
		else if (_modelMobile->GetChildrens()[6]->GetCanDraw()) {
			_modelMobile->GetChildrens()[5]->SetCanDraw(true);
			_modelMobile->GetChildrens()[3]->SetCanDraw(true);
		}
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