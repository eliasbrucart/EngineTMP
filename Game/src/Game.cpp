#include "Game.h"

float speed = 100.0f;

using namespace Engine;

glm::vec3 pointLightPositions[4] = {
		glm::vec3(0.0f, 0.0f, -2.0f),
		glm::vec3(5.0f, 0.0f, -2.0f),
		glm::vec3(10.0f, 0.0f, -2.0f),
		glm::vec3(15.0f, 0.05f, -2.0f)
};

float rotationSpeed = 100.0f; //dejamos como esta

Game::Game() {

}
Game::~Game() {
	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
	}
	//
	//if (player != NULL) {
	//	delete player;
	//	player = NULL;
	//}

	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}

	if (_shape2 != NULL) {
		delete _shape2;
		_shape2 = NULL;
	}

	for (int i = 0; i < 4; i++) {
		if (_light[i] != NULL) {
			delete _light[i];
			_light[i] = NULL;
		}
	}

	if (_model != NULL) {
		delete _model;
		_model = NULL;
	}

	//if (_point1 != NULL) {
	//	delete _point1;
	//	_point1 = NULL;
	//}
	//
	//if (_point2 != NULL) {
	//	delete _point2;
	//	_point2 = NULL;
	//}

	if (_dirLight != NULL) {
		delete _dirLight;
		_dirLight = NULL;
	}

	if (_spotLight != NULL) {
		delete _spotLight;
		_spotLight = NULL;
	}

	//if (map != NULL) {
	//	delete map;
	//	map = NULL;
	//}
}
void Game::InitGame() {
	//_sprite = new Sprite(true, "res/textures/container2.png", GetRenderer(), basicShader);
	//player = new Animation();

	_sprite = new Sprite(true, "res/textures/container2.png", "res/textures/container2_specular.png", GetRenderer(), basicShader, MaterialType::lambertPro);

	//map = new Tilemap(glm::vec2(10, 10), textureShader, "res/textures/Dungeon_Tileset.png", GetRenderer());
	//map->LoadMap("res/tilemap/Map2.tmx");
	_shape = new Shape(Type::cube, GetRenderer(), basicShader, MaterialType::gold);
	_shape2 = new Shape(Type::cube, GetRenderer(), basicShader, MaterialType::esmerald);
	_dirLight = new Light(GetRenderer(), basicShader, LightType::directional);
	_spotLight = new Light(GetRenderer(), basicShader, LightType::spot);
	//_point1 = new Light(GetRenderer(), basicShader, LightType::point);
	//_point2 = new Light(GetRenderer(), basicShader, LightType::point);


	for (int i = 0; i < 4; i++) {
		_light[i] = new Light(GetRenderer(), basicShader, LightType::point);
		_light[i]->SetPosition(pointLightPositions[i]);
		_light[i]->SetAmbient(glm::vec3(0.2f));
		_light[i]->SetDiffuse(glm::vec3(0.5f));
		_light[i]->SetSpecular(glm::vec3(1.0f));
		_light[i]->SetConstant(1.0f);
		_light[i]->SetLinear(0.09f);
		_light[i]->SetQuadratic(0.032f);
	}

	//_model = new ModelImp("res/models/ejemplo/source/Jack Sparrow/Jack Sparrow.obj", "res/models/pandemic/textures/color_1.png", basicShader);
	_model = new ModelImp("res/models/cyborg/cyborg.obj");
	//_model = new ModelImp("res/models/backpack/backpack.obj", "res/models/backpack2/textures/1001_metallic.jpg", basicShader);
	//_model->SetTexturePath("res/models/backpack2/textures/1001_albedo.jpg");
	//_model->SetShader(GetRenderer()->GetShader());

	//_light[3]->transform.position = pointLightPositions[3];
	//
	//for (int i = 0; i < 3; i++) {
	//	_light[i]->transform.position = pointLightPositions[i];
	//}

	_shape->Init();
	_shape2->Init();

	_sprite->Init();

	//Crear un array de posiciones para las luces y array de ambient, diffuse, specular, eviar hardcodeo.

	_dirLight->Init();

	//_light[3]->transform.position = glm::vec3(0.0f, 0.0f, 1.0f);
	_dirLight->SetColor(1.0f, 1.0f, 0.0f);

	_spotLight->Init();
	_spotLight->transform.position = glm::vec3(0.0f, 0.0f, -2.0f);
	//_spotLight->SetDirection(_camera->GetCameraFront());
	//_spotLight->SetAmbient(glm::vec3(0.0f));
	//_spotLight->SetDiffuse(glm::vec3(1.0f));
	//_spotLight->SetSpecular(glm::vec3(1.0f));
	//_spotLight->SetConstant(1.0f);
	//_spotLight->SetLinear(0.09f);
	//_spotLight->SetQuadratic(0.032f);
	//_spotLight->SetCutOff(glm::cos(glm::radians(12.5f)));
	//_spotLight->SetOuterCutOff(glm::cos(glm::radians(15.0f)));


	_shape->Color(1.0f, 0.0f, 0.0f);
	_shape->transform.position = glm::vec3(0.0f, 0.0f, -5.0f);
	_shape->transform.scale = glm::vec3(3.0f, 3.0f, 3.0f);

	_shape2->Color(0.0f, 0.0f, 1.0f);
	_shape2->transform.position = glm::vec3(-12.0f, 0.0f, -10.0f);
	_shape2->transform.scale = glm::vec3(5.0f, 5.0f, 5.0f);

	//player->Init(_sprite, glm::ivec2(6,3));
	//   first frame     Last frame   Loop    anim speed
	//player->AddAnimation(0, 6, false, 1.f); //ataque
	//player->AddAnimation(6, 11, false, 1.f); // bloqueo
	//player->AddAnimation(12, 14, true,  .4f); // idle
	//player->SetAnimation(2);


	//ahora se pueden mover las cosas estilo unity
	//_sprite->Color(1.0f, 1.0f, 1.0f);
	_sprite->transform.position = glm::vec3(15.0f, 0.0f, -10.0f);
	_sprite->transform.scale = glm::vec3(5.0f, 5.0f, 5.0f);
}
void Game::PlayerInputs() {
	if (input.GetKey(KeyCode::I)) {
		//_camera->transform.position.z -= speed * time.GetDeltaTime();
		_spotLight->transform.position.x -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::O)) {
		_spotLight->transform.position.x += speed * time.GetDeltaTime();
	}
	//else if (input.GetKey(KeyCode::S)) {
	//	_camera->transform.position.z += speed * time.GetDeltaTime();
	//	//_shape->transform.position.z += speed * time.GetDeltaTime();
	//}
	//else if (input.GetKey(KeyCode::D)) {
	//	_camera->transform.position.x += speed * time.GetDeltaTime();
	//	//_shape->transform.position.x += speed * time.GetDeltaTime();
	//}
	//else if (input.GetKey(KeyCode::A)) {
	//	_camera->transform.position.x -= speed * time.GetDeltaTime();
	//	//_shape->transform.position.x -= speed * time.GetDeltaTime();
	//}
	//else if (input.GetKey(KeyCode::LEFT)) {
	//	_light->transform.position.x -= speed * time.GetDeltaTime();
	//}
	//else if (input.GetKey(KeyCode::RIGHT)) {
	//	_light->transform.position.x += speed * time.GetDeltaTime();
	//}
	//else if (input.GetKey(KeyCode::UP)) {
	//	_light->transform.position.z -= speed * time.GetDeltaTime();
	//}
	//else if (input.GetKey(KeyCode::DOWN)) {
	//	_light->transform.position.z += speed * time.GetDeltaTime();
	//}
	//else if (input.GetKey(KeyCode::T)) {
	//	float value = 10.0f;
	//	value += 20.0f * time.GetDeltaTime();
	//	_shape2->RotateZ(value);
	//}

	if (input.GetKey(KeyCode::W)) {
		_camera->transform.position += speed * time.GetDeltaTime() * _camera->GetCameraFront();
	}

	else if (input.GetKey(KeyCode::S)) {
		_camera->transform.position -= speed * time.GetDeltaTime() * _camera->GetCameraFront();
	}

	else if (input.GetKey(KeyCode::A)) {
		_camera->transform.position -= glm::normalize(glm::cross(_camera->GetCameraFront(), _camera->GetCameraUp())) * speed * time.GetDeltaTime();
	}

	else if (input.GetKey(KeyCode::D)) {
		_camera->transform.position += glm::normalize(glm::cross(_camera->GetCameraFront(), _camera->GetCameraUp())) * speed * time.GetDeltaTime();
	}

	if (input.GetKey(KeyCode::DOWN)) {
		//_camera->_rotationSpeed = rotationSpeed * time.GetDeltaTime();
		_camera->RotatePitch(-rotationSpeed * time.GetDeltaTime());
	}

	if (input.GetKey(KeyCode::UP)) {
		//_camera->_rotationSpeed = rotationSpeed * time.GetDeltaTime();
		_camera->RotatePitch(rotationSpeed * time.GetDeltaTime());
	}

	if (input.GetKey(KeyCode::LEFT)) {
		//_camera->_rotationSpeed = rotationSpeed * time.GetDeltaTime();
		_camera->RotateYaw(-rotationSpeed * time.GetDeltaTime());
	}

	if (input.GetKey(KeyCode::RIGHT)) {
		//_camera->_rotationSpeed = rotationSpeed * time.GetDeltaTime();
		_camera->RotateYaw(rotationSpeed * time.GetDeltaTime());
	}
	
	//
	//if (input.GetMouseButton(MouseButtons::LEFT_MOUSE_BUTTON)) {
	//	player->SetAnimation(0);
	//}
	//if (input.GetMouseButton(MouseButtons::RIGHT_MOUSE_BUTTON)) {
	//	player->SetAnimation(1);
	//}
}
void Game::UpdateGame() {

	PlayerInputs();

	//if (!player->GetCurrentAnimation().loop && player->GetCurrentAnimation().hasEnded) {
	//	player->SetAnimation(2);
	//}
	//
	//_shape2->RotateX(105.0f * time.GetDeltaTime());

	//_camera->SetCameraFront(_shape->transform.position);

	//glm::vec3 thirdPosition = _shape->transform.position + glm::vec3(_shape->transform.position.x, 0.0f, _shape->transform.position.z + 10.0f);

	//_camera->transform.position.x = _shape->transform.position.x;
	//_camera->transform.position.z = _shape->transform.position.z + 15.0f;

	//_camera->SetLookAt(_shape->transform.position.x, _shape->transform.position.z + 15.0f, _shape->transform.position + glm::vec3(0.0f, 0.0f, 5.0f));

	//_shape->transform.position = glm::vec3(1.2f, 1.0f, -2.0f);

	//_camera->FollowTarget(_shape->transform.position);

	//_camera->UpdateRotation(_shape->transform.position);

	_camera->UpdateRotation();
	_camera->SetLookAt(_camera->GetCameraFront());
	_camera->Draw(basicShader);

	_shape->Draw();
	_shape2->Draw();
	_model->Draw(basicShader);
	//Directional light
	_dirLight->DrawDirectionalLight();
	_spotLight->DrawSpotLight();

	//_point1->Draw();
	//_point2->Draw();


	for (int i = 0; i < 4; i++)
		_light[i]->DrawPointLight(i);

	_sprite->DrawSprite();

	//map->Draw();
	
	//map->CheckCollisionWithTileMap(_sprite, _sprite->transform.position, speed * time.GetDeltaTime());

	//player->UpdateIndex(time);
	//
	//_sprite->DrawAnimation(player->GetUVs(player->GetCurrentIndex()));

}
void Game::UnloadGame() {

	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}

	if (_shape2 != NULL) {
		delete _shape2;
		_shape2 = NULL;
	}

	for (int i = 0; i < 4; i++) {
		if (_light[i] != NULL) {
			delete _light[i];
			_light[i] = NULL;
		}
	}
	
	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
	}

	if (_dirLight != NULL) {
		delete _dirLight;
		_dirLight = NULL;
	}

	if (_spotLight != NULL) {
		delete _spotLight;
		_spotLight = NULL;
	}

	if (_model != NULL) {
		delete _model;
		_model = NULL;
	}

	//if (_point1 != NULL) {
	//	delete _point1;
	//	_point1 = NULL;
	//}
	//
	//if (_point2 != NULL) {
	//	delete _point2;
	//	_point2 = NULL;
	//}

	//if (player != NULL) {
	//	delete player;
	//	player = NULL;
	//}

	//if (map != NULL) {
	//	delete map;
	//	map = NULL;
	//}
}