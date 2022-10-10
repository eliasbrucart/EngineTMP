#include "Game.h"

float speed = 10.0f;

using namespace std;
using namespace Engine;

glm::vec3 pointLightPositions[4] = {
		glm::vec3(0.0f, 0.0f, -2.0f),
		glm::vec3(5.0f, 0.0f, -2.0f),
		glm::vec3(10.0f, 0.0f, -2.0f),
		glm::vec3(15.0f, 0.05f, -2.0f)
};

float rotationSpeed = 100.0f; //dejamos como esta

glm::vec3 direction = glm::vec3(0.0f);
glm::vec3 scale = glm::vec3(0.0f);

glm::vec3 rot = glm::vec3(0.0f);

Game::Game() {

}

Game::~Game() {
	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
	}

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

	//if (_bsp != NULL) {
	//	delete _bsp;
	//	_bsp = NULL;
	//}

	if (_dirLight != NULL) {
		delete _dirLight;
		_dirLight = NULL;
	}

	if (_spotLight != NULL) {
		delete _spotLight;
		_spotLight = NULL;
	}

	if (_modelLeft != NULL) {
		delete _modelLeft;
		_modelLeft = NULL;
	}

	if (_modelRight != NULL) {
		delete _modelRight;
		_modelRight = NULL;
	}

	if (_modelForward != NULL) {
		delete _modelForward;
		_modelForward = NULL;
	}

	if (_modelMobile != NULL) {
		delete _modelMobile;
		_modelMobile = NULL;
	}

	for (int i = 0; i < 3; i++) {
		if (_bspPlanes[i] != NULL) {
			delete _bspPlanes[i];
			_bspPlanes[i] = NULL;
		}
	}
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
		_light[i]->Init();
		_light[i]->SetPosition(pointLightPositions[i]);
		//_light[i]->SetAmbient(glm::vec3(0.2f));
		//_light[i]->SetDiffuse(glm::vec3(0.5f));
		//_light[i]->SetSpecular(glm::vec3(1.0f));
		//_light[i]->SetConstant(1.0f);
		//_light[i]->SetLinear(0.09f);
		//_light[i]->SetQuadratic(0.032f);
	}

	glm::vec3 farMultiplyCamFront = 100.0f * _camera->GetCameraFront();
	float halfVSide = 100.0f * tanf(glm::radians(45.0f) * 0.5f);
	float halfHSide = (halfVSide * (1280.0f / 720.0f));

	//_planes[0] = _camera->GetFar();
	//_planes[0] = { glm::vec3(0.57f, 0.0f, 0.81f), 1.0f };
	//_planes[0] = { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)};
	//std::cout << "plane 0 distance: " << _planes[0].GetDistance() << std::endl;
	//_planes[0].transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
	//std::cout << "camera front en ese momento en z: " << _camera->GetCameraFront().z << std::endl;
	//std::cout << "Normal del plano 0 en z: " << _planes[0].GetNormal().z << std::endl;
	//_planes[0]->SetAngleA(glm::vec3(0.0f, -90.0f, 0.0f));
	//_planes[0]->SetAngleB(glm::vec3(0.0f, 90.0f, 0.0f));
	//_planes[0]->RotateY(-90.0f);

	//_planes[1] = {_camera->transform.position, glm::cross(farMultiplyCamFront - _camera->_cameraRight * halfVSide, _camera->_cameraUp)};
	//_planes[1] = {_camera->transform.position, glm::vec3(0.0f, 0.0f, 1.0f)};
	//_planes[1] = { glm::vec3(-3.0f, 0.0f, 3.0f), glm::vec3(1.0f, 0.0f, 0.0f) };
	//_planes[1]->transform.position = glm::vec3(-5.0f, 0.0f, 0.0f);
	//_planes[1]->SetNormal(glm::vec3(0.0f, 0.0f, 1.0f));
	//_planes[1]->SetAngleA(glm::vec3(0.0f, 90.0f, 0.0f));
	//_planes[1]->SetAngleB(glm::vec3(0.0f, -90.0f, 0.0f));
	//_planes[1]->RotateY(90.0f);

	//_planes[2] = {_camera->transform.position, glm::cross(_camera->_cameraUp, farMultiplyCamFront + _camera->_cameraRight * halfHSide)};
	//_planes[2] = { _camera->transform.position, glm::vec3(0.0f, 0.0f, -1.0f) };
	//_planes[2] = { glm::vec3(3.0f, 0.0f, 3.0f), glm::vec3(-1.0f, 0.0f, 0.0f) };
	//_planes[2]->SetAngleA(glm::vec3(0.0f, 0.0f, 0.0f));
	//_planes[2]->SetAngleB(glm::vec3(0.0f, 0.0f, -1.0f));

	//_model = new ModelImp("res/models/bar/source/Bar_stool.fbx");
	//string modelpath = "res/models/scene/scenefachera.fbx";
	string modelpath = "res/models/scene/scenefachera.fbx";
	_model = new ModelImp(modelpath, basicShader, GetRenderer());
	//_model->transform.position = glm::vec3(0.0f, 0.0f, 2.0f);
	//_model->Translate(0.0f, 0.0f, 0.0f);
	//_model->transform.scale = glm::vec3(1.0f);

	//std::cout << "Posicion en z del modelo: " << _model->transform.position.z << std::endl;

	_modelLeft = _model->GetSceneNode()->GetChildrenWithName("left");
	_modelLeft->SetRenderer(GetRenderer());
	_modelRight = _model->GetSceneNode()->GetChildrenWithName("right");
	_modelRight->SetRenderer(GetRenderer());
	_modelForward = _model->GetSceneNode()->GetChildrenWithName("foward");
	_modelForward->SetRenderer(GetRenderer());
	_modelMobile = _model->GetSceneNode()->GetChildrenWithName("mobile");
	_modelMobile->SetRenderer(GetRenderer());

	_bspPlanes[0] = _model->GetSceneNode()->GetChildrenWithName("bspPlane");
	_bspPlanes[0]->SetRenderer(GetRenderer());
	_bspPlanes[1] = _model->GetSceneNode()->GetChildrenWithName("bspPlane4");
	_bspPlanes[1]->SetRenderer(GetRenderer());
	_bspPlanes[2] = _model->GetSceneNode()->GetChildrenWithName("bspPlane5");
	_bspPlanes[2]->SetRenderer(GetRenderer());

	//_modelA = new ModelImp(modelpath, basicShader, GetRenderer());
	//_modelA->transform.position = glm::vec3(-0.5f, -0.5f, -1.0f);
	//_modelA->transform.scale = glm::vec3(1.0f);

	//_modelA->AddChild(_model);

	//_modelA->UpdateSelfAndChild();

	//_model = new ModelImp("res/models/ejemplo/source/Jack Sparrow/Jack Sparrow.obj", basicShader);
	//_model = new ModelImp("res/models/backpack/backpack.obj", "res/models/backpack2/textures/1001_metallic.jpg", basicShader);
	//_model->SetTexturePath("res/models/backpack2/textures/1001_albedo.jpg");
	//_model->SetShader(GetRenderer()->GetShader());

	//_light[3]->transform.position = pointLightPositions[3];

	//for (int i = 0; i < 3; i++) {
	//	_light[i]->transform.position = pointLightPositions[i];
	//}

	_shape->Init();
	_shape2->Init();

	_sprite->Init();


	//_model->SetParent(_shape);

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

	//BSP
	//_bsp = new BSPAlgorithm();
	//_bsp->AddModel(_model);

	//Agregar planos
	//_bsp->AddPlane(&_planes[0]);
	//_bsp->AddPlane(&_planes[1]);
	//_bsp->AddPlane(&_planes[2]);
}
void Game::PlayerInputs() {
	if (input.GetKey(KeyCode::I)) {
		//_camera->transform.position.z -= speed * time.GetDeltaTime();
		_spotLight->transform.position.x -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::O)) {
		_spotLight->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::P)) {
		_light[0]->SetTurnOnState(false);
		_spotLight->SetTurnOnState(false);
		_dirLight->SetTurnOnState(false);
	}
	else if (input.GetKey(KeyCode::B)) {
		_spotLight->transform.position.z += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::V)) {
		_spotLight->transform.position.z -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::L)) {
		_light[0]->SetTurnOnState(true);
		_spotLight->SetTurnOnState(true);
		_dirLight->SetTurnOnState(true);
	}
	else if (input.GetKey(KeyCode::G)) {
		direction.x += speed * time.GetDeltaTime();
		_camera->transform.position = _bspPlanes[2]->getPos();
		//_bspPlanes[0]->setPos(_bspPlanes[0]->getPos(_bspPlanes[0]->getModel() + direction.x));
		//_model->MoveModel(direction);
		//_modelA->Translate(direction.x, direction.y, direction.z);
		//std::cout << "_modelA X " << _modelA->transform.position.x << std::endl;
		//std::cout << "_bspPlanes 0 X " << _bspPlanes[0]->transform.position.x << std::endl;
		//_shape->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::F)) {
		direction.x -= speed * time.GetDeltaTime();
		_camera->transform.position = _bspPlanes[1]->getPos();
		//_modelLeft->setPos(direction);
		//_bspPlanes[1]->setPos(_bspPlanes[1]->getPos(_bspPlanes[1]->getModel() + direction.x));
		//_model->MoveModel(direction);
		//_shape->transform.position.x -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::T)) {
		direction.y += speed * time.GetDeltaTime();
		_camera->transform.position = _modelRight->getPos();
		//_bspPlanes[2]->Translate(direction.x, direction.y, direction.z);
		//_model->MoveModel(direction);
		//_shape->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::C)) {
		direction.y -= speed * time.GetDeltaTime();
		_camera->transform.position = _bspPlanes[2]->getPos();
		//_model->MoveModel(direction);
		//_shape->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::K)) {
		direction.z -= speed * time.GetDeltaTime();
		_camera->transform.position = _bspPlanes[0]->getPos();
		//_model->MoveModel(direction);
		//_shape->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::R)) {
		direction.z += speed * time.GetDeltaTime();
		_camera->transform.position = _bspPlanes[1]->getPos();
		//_model->MoveModel(direction);
		//_shape->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::H)) {
		scale.x += speed * time.GetDeltaTime();
		scale.y += speed * time.GetDeltaTime();
		scale.z += speed * time.GetDeltaTime();
		//_shape->Scale(scale.x, scale.y, scale.z);
		_model->ScaleModel(scale.x, scale.y, scale.z);
	}
	else if (input.GetKey(KeyCode::J)) {
		scale.x -= speed * time.GetDeltaTime();
		scale.y -= speed * time.GetDeltaTime();
		scale.z -= speed * time.GetDeltaTime();
		//_shape->Scale(scale.x, scale.y, scale.z);
		_model->ScaleModel(scale.x, scale.y, scale.z);
	}

	else if (input.GetKey(KeyCode::N)) {
		scale.x += speed * time.GetDeltaTime();
		scale.y += speed * time.GetDeltaTime();
		scale.z += speed * time.GetDeltaTime();
		_shape->Scale(scale.x, scale.y, scale.z);
		//_model->ScaleModel(scale.x, scale.y, scale.z);
	}
	else if (input.GetKey(KeyCode::M)) {
		scale.x -= speed * time.GetDeltaTime();
		scale.y -= speed * time.GetDeltaTime();
		scale.z -= speed * time.GetDeltaTime();
		_shape->Scale(scale.x, scale.y, scale.z);
		//_model->ScaleModel(scale.x, scale.y, scale.z);
	}
	else if (input.GetKey(KeyCode::X)) {
		//_planes[0].SetNormal(glm::vec3(-0.100f, 0.23f, 0.96f));
		//_planes[0].SetNormal(glm::vec3(0.0f, 0.0f, -1.0f));
		//rot.x += speed * time.GetDeltaTime();
		//_modelA->RotateModelX(rot.x);
		//_model->RotateModelX(rot.x);
	}
	else if (input.GetKey(KeyCode::Y)) {
		rot.y += speed * time.GetDeltaTime();
		//_modelA->RotateModelY(rot.y);
		_model->RotateModelY(rot.y);
	}
	else if (input.GetKey(KeyCode::Z)) {
		//_planes[0].SetNormal(glm::vec3(0.57f, 0.0f, 0.81f));
		//_planes[0].SetNormal(glm::vec3(0.0f, 0.0f, 1.0f));
		//rot.z += speed * time.GetDeltaTime();
		//_modelA->RotateModelZ(rot.z);
		//_model->RotateModelZ(rot.z);
	}
	else if (input.GetKey(KeyCode::A)) {
		_camera->transform.position.x -= speed * time.GetDeltaTime();
		//_shape->transform.position.x -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::LEFT)) {
		_light[0]->transform.position.x -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::RIGHT)) {
		_light[0]->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::UP)) {
		_light[0]->transform.position.z -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::DOWN)) {
		_light[0]->transform.position.z += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::T)) {
		float value = 10.0f;
		value += 20.0f * time.GetDeltaTime();
		_shape2->RotateZ(value);
	}

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

	Node* child = _modelMobile->GetChildrenWithName("RootNode");
	
	if (child != NULL) {
		child->setScale(child->getScale());
		child->setRotRadians(child->getRot());
	}


	_modelLeft->SetTransformMatrix();
	_modelRight->SetTransformMatrix();
	_modelForward->SetTransformMatrix();
	_modelMobile->SetTransformMatrix();
	
	for (int i = 0; i < 3; i++) {
		_bspPlanes[i]->SetTransformMatrix();
	}

	_camera->UpdateRotation();
	_camera->SetLookAt(_camera->GetCameraFront());
	_camera->Draw(basicShader);

	_shape->Draw();
	_shape2->Draw();
	//_modelA->UpdateSelfAndChild();
	//_model->Draw(basicShader, camFrustum);
	//_modelA->Draw(basicShader);

	//_modelA->Draw(basicShader);
	//Directional light
	_dirLight->DrawDirectionalLight();
	_spotLight->DrawSpotLight();

	//_planes[0] = _camera->GetFar();
	//_planes[1] = _camera->GetRight();
	//_planes[2] = _camera->GetLeft();

	//std::cout << "Normal del plano 0 en x: " << _planes[0].GetNormal().x << std::endl;
	//std::cout << "Normal del plano 0 en y: " << _planes[0].GetNormal().y << std::endl;
	//std::cout << "Normal del plano 0 en z: " << _planes[0].GetNormal().z << std::endl;
	//
	//std::cout << "Distance del plano 0: " << _planes[0].GetDistance() << std::endl;

	//std::cout << "Posicion en z del modelo: " << _model->transform.position.z << std::endl;



	//_point1->Draw();
	//_point2->Draw();


	for (int i = 0; i < 4; i++)
		_light[i]->DrawPointLight(i);

	_sprite->DrawSprite();

	_modelLeft->Draw(basicShader, camFrustum);
	_modelRight->Draw(basicShader, camFrustum);
	_modelForward->Draw(basicShader, camFrustum);
	_modelMobile->Draw(basicShader, camFrustum);
	
	for (int i = 0; i < 3; i++) {
		_bspPlanes[i]->Draw(basicShader, camFrustum);
	}

	//_bsp->CheckPlaneWithCamera(_camera);
	//_bsp->BSP(_camera);

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

	//if (_bsp != NULL) {
	//	delete _bsp;
	//	_bsp = NULL;
	//}
}