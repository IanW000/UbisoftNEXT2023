#pragma once
class Bomb
{

	Bomb();

	int x, y;
	bool explosion;
	int inventory;
	int power;

	void Init();
	void Update();
	void Render();
};

