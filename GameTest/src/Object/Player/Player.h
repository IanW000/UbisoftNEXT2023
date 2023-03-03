#pragma once
#include "Object/Object.h"
class Player : Object
{
public:

	Player();
	int currentHP;
	bool died;
	void Reset();
	void Update(float deltaTime);
	void Render();
	bool resetOnce;

};


