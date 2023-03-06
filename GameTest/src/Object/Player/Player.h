#pragma once
#include "Object/Object.h"
#include <Math/Matrix/Matrix.h>

enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT
};

class Player : Object
{
public:

	Player();

	virtual void Init(GameManager& gameManager) override;

	virtual void Update(GameManager& gameManager) override;

	virtual void Render(GameManager& gameManager) override;

	int getX();
	int getY();
	int getHp();
	bool checkDied();
	float getSpeed();
	
	void Reset();
	void setX(int);
	void setY(int y);	

	void reset();
	void setLocation();
	void setHP(int loseHp);
	void addSpeed(float speed);
	void setDied(bool isDied);

	const static int PLAYER_WIDTH = 16;
	const static int PLAYER_HEIGHT = 16;

	int locX;
	int locY;

private:



	Matrix m_Matrix;

	float speed;
	int currentHP;
	bool isDied;

};


