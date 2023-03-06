#pragma once
#include <Object/Player/Player.h>
#include <App/App.h>

enum enemyAI {
	RUNAWAY,
	CHASE,
	PATROL,
	COLLECT
};

class Enemy:public Player
{
public:

	Enemy();

	virtual void Init(GameManager& gameManager) override;

	virtual void Update(GameManager& gameManager) override;
	
	virtual void Render(GameManager& gameManager) override;
	
	void moveFowards();
	void moveBackwards();
	void moveLeft();
	void moveRight();

	void Enemy::Movement(GameManager& gameManager, float targetX, float targetY);
;


	void setLocation();
	bool checkDied();

	void setX(float x);
	void setY(float y);
	float getX();
	float getY();
	void Reset();
	int getHp();
	void setHP(int hp);

	bool OnUserCreate();
	bool Solve_AStar();
	bool OnUserUpdate(float fElapsedTime);
	enemyAI enemyAI;
	void moveTo(GameManager& gameManager, float targetX, float targetY);

private:
	float locX, locY;
	bool isDied;
	int currentHP;
	bool findpathonce = false;
	float speed;
	float lastBombPosX, lastBombPosY, lastBombTime;
	GameManager* m_gameManager;
	bool getStuck, moving;
};

