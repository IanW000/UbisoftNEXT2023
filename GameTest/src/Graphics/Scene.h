#pragma once
#include <Math/Matrix/Matrix.h>
#include <Object/Player/Player.h>
#include <UI/UI.h>



//Screen width is 1024, height is 768, each object will be 32*32

enum ATTR {
	SPACE,
	BLOCK,
	BRICK
};

class Scene
{
public:
	Scene();
	//UI &UISettings
	void Init();
	void Update(float deltaTime);
	void Render();
	
	const static int WIN_WIDTH = 1024;
	const static int WIN_HEIGHT = 768;
	const static int BLOCK_BRICK_SIZE = 32;
	const static int ROW = WIN_HEIGHT / BLOCK_BRICK_SIZE;
	const static int COL = WIN_WIDTH / BLOCK_BRICK_SIZE;
	const static int brickNum = 512;

	//UI *UISettings;
	Player *player;

private:
	Matrix Mat2D;
};

