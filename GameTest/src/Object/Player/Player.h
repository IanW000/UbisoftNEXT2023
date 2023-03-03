#pragma once
#include "Object/Object.h"
class Player : Object
{
public:
	void Init();
	void Update(float deltaTime);
	void Render();
};


