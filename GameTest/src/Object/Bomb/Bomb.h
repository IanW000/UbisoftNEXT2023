#pragma once
class Bomb
{

public:

	Bomb();

	void Init(int x, int y);
	void Update();
	void Render();

private:

	int x, y;
	bool explosion;
	int inventory;
	int power;


};

