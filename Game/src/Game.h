#ifndef GAME_H
#define GAME_H

#include"base.h"
#include <string>
#include <vector>

using namespace Engine;

class Game: public Base {
private:
	float angle = 0;
	float t = 0;
	glm::vec2 shapePos = glm::vec2(0,0);
	Shape* _shape = NULL;
	Shape* _shape2 = NULL;
	Light* _light[4] = {NULL, NULL, NULL, NULL};
	//Light* _point1 = NULL;
	//Light* _point2 = NULL;
	Light* _dirLight = NULL;
	Light* _spotLight = NULL;
	Sprite* _sprite = NULL;
	ModelImp* _model = NULL;
	Node* _modelLeft = NULL;
	Node* _modelRight = NULL;
	Node* _modelForward = NULL;
	Node* _modelMobile = NULL;
	Node* _bspPlanes[3] = {NULL, NULL, NULL};
	BSPAlgorithm* _bsp = NULL;
	//Plane _planes[3];
	//ModelImp* _modelA = NULL;
	//Animation* player = NULL;
	//Tilemap* map = NULL;
public:
	Game();
	~Game();
	void PlayerInputs();
	void InitGame() override;
	void UpdateGame() override;
	void UnloadGame() override;
};

#endif