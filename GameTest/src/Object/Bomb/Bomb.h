#pragma once

enum
{
	ANIM_BOMB
};

class Bomb
{

public:

	Bomb();

	void Init(int x, int y);
	void Update(float deltaTime);
	void Render();

private:

	int x, y;
	bool explosion;
	int inventory;
	int power;


};

