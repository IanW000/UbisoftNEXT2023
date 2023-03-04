#pragma once

enum BombState
{
	NORMAL,
	EXPLOSION,
	DISAPPEAR
};

class Bomb
{

public:

	Bomb();

	void Init(int x, int y);
	void Update(float deltaTime);
	void Render();

	int getBombX();
	int getBombY();

private:

	int bombX, bombY;
	bool explosion;
	int inventory;
	int power;

	BombState bombState;

};

