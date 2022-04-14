#include "Game.h"

float speed = 100.0f;

Game::Game() {

}
Game::~Game() {
	//if (_sprite != NULL) {
	//	delete _sprite;
	//	_sprite = NULL;
	//}
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

	//if (map != NULL) {
	//	delete map;
	//	map = NULL;
	//}
}
void Game::InitGame() {

	//_sprite = new Engine::Sprite(true, "res/textures/samurai.png", GetRenderer(), textureShader);
	//player = new Animation();

	//map = new Tilemap(glm::vec2(10, 10), textureShader, "res/textures/Dungeon_Tileset.png", GetRenderer());
	//map->LoadMap("res/tilemap/Map2.tmx");
	_shape = new Shape(Type::lightCube, GetRenderer(), basicShader);
	_shape2 = new Shape(Type::cube, GetRenderer(), basicShader);

	_shape->Init();
	_shape2->Init();

	//_sprite->Init();

	//_shape->Color(1.0f, 0.0f, 0.0f);
	_shape->transform.position = glm::vec3(0.0f, 0.0f, -5.0f);
	_shape->transform.scale = glm::vec3(3.0f, 3.0f, 3.0f);

	_shape2->Color(0.0f, 0.0f, 1.0f);
	_shape2->transform.position = glm::vec3(2.0f, 0.0f, -10.0f);
	_shape2->transform.scale = glm::vec3(5.0f, 5.0f, 5.0f);

	//player->Init(_sprite, glm::ivec2(6,3));
	//   first frame     Last frame   Loop    anim speed
	//player->AddAnimation(0, 6, false, 1.f); //ataque
	//player->AddAnimation(6, 11, false, 1.f); // bloqueo
	//player->AddAnimation(12, 14, true,  .4f); // idle
	//player->SetAnimation(2);


	//_sprite->Scale(50.0f, 50.0f, 1.0f);

	//ahora se pueden mover las cosas estilo unity
	//_sprite->Color(1.0f, 1.0f, 1.0f);
	//_sprite->transform.position = glm::vec3(400,400,0);
}
void Game::PlayerInputs() {
	if (input.GetKey(KeyCode::W)) {
		_shape->transform.position.z -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::S)) {
		_shape->transform.position.z += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::D)) {
		_shape->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::A)) {
		_shape->transform.position.x -= speed * time.GetDeltaTime();
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
	//_sprite->RotateZ(-55.0f);

	//_camera->SetCameraFront(_shape->transform.position);

	//glm::vec3 thirdPosition = _shape->transform.position + glm::vec3(_shape->transform.position.x, 0.0f, _shape->transform.position.z + 10.0f);

	//_camera->transform.position.x = _shape->transform.position.x;
	//_camera->transform.position.z = _shape->transform.position.z + 15.0f;

	//_camera->SetLookAt(_shape->transform.position.x, _shape->transform.position.z + 15.0f, _shape->transform.position + glm::vec3(0.0f, 0.0f, 5.0f));

	//_shape->transform.position = glm::vec3(1.2f, 1.0f, -2.0f);

	_camera->FollowTarget(_shape->transform.position);

	//_camera->UpdateRotation(_shape->transform.position);

	_shape->Draw();
	_shape2->Draw();

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

	//if (_sprite != NULL) {
	//	delete _sprite;
	//	_sprite = NULL;
	//}
	//
	//if (player != NULL) {
	//	delete player;
	//	player = NULL;
	//}

	//if (map != NULL) {
	//	delete map;
	//	map = NULL;
	//}
}