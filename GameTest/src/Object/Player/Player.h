#pragma once
#include "Object/Object.h"
#include <Math/Matrix/Matrix.h>

enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};

class Player : Object
{
public:

	Player();

	int currentHP;
	bool died;
	void Reset();
	void Init();
	//void Init(Matrix Mat2d);
	void Update(float deltaTime, Matrix Mat2d);
	void Render();
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	void setPlayerLocation();
	

private:
	Matrix m_Matrix;
	int playerWidth;
	int playerHeight;
	int playerX;
	int playerY;

};


