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
	void Init(Matrix Mat2d);
	void Update(float deltaTime);
	void Render();
	bool resetOnce;
	int playerX;
	int playerY;

};


