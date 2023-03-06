#pragma once
#include <Object/Player/Player.h>
#include <App/App.h>


class Enemy:public Player
{
public:

	Enemy();

	void findPath(GameManager& gameManager);

	bool createEnemy();

	virtual void Init(GameManager& gameManager) override;

	virtual void Update(GameManager& gameManager) override;
	
	virtual void Render(GameManager& gameManager) override;
	

	void setLocation();

	void Movement(GameManager& gameManager);

	bool checkDied();

	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void Reset();
	int getHp();
	void setHP(int hp);

	void moveTo(GameManager& gameManager, int targetX, int targetY);

	bool OnUserCreate();
	bool Solve_AStar();
	bool OnUserUpdate(float fElapsedTime);

private:
	int locX, locY;
	bool isDied;
	int currentHP;
	bool findpathonce = false;
	float speed = 1;


	struct sNode
	{
		bool bObstacle = false;			// Is the node an obstruction?
		bool bVisited = false;			// Have we searched this node before?
		float fGlobalGoal;				// Distance to goal so far
		float fLocalGoal;				// Distance to goal if we took the alternative route
		int x;							// Nodes position in 2D space
		int y;
		std::vector<sNode*> vecNeighbours;	// Connections to neighbours
		sNode* parent;					// Node connecting to this node that offers shortest parent
	};

	sNode* nodes = nullptr;
	int nMapWidth = 1024;
	int nMapHeight = 768;

	sNode* nodeStart = nullptr;
	sNode* nodeEnd = nullptr;

};

