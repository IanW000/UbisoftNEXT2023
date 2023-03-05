#pragma once
#include <Object/Player/Player.h>
#include <App/App.h>

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


//struct Node
//{
//	Node *parentNode;
//	int x,y,f,g,h;
//	Node(int x, int y, int g, int h, Node *parentNode) {
//		this->x = x;
//		this->y = y;
//		this->g = g;
//		this->h = h;
//		this->f = g + h;
//		this->parentNode = parentNode;
//	}
//};

class Enemy:public Player
{
public:

	void Enemy::findPath(GameManager& gameManager);

	bool createEnemy();

	virtual void Init(GameManager& gameManager) override;

	virtual void Update(GameManager& gameManager) override;
	
	virtual void Render(GameManager& gameManager) override;
	
	bool AStartPathFinding();

	void setLocation();


	void Movement(GameManager& gameManager);


private:

	bool findpathonce = false;
	float speed = 1;
	sNode* nodes = nullptr;
	sNode* nodeStart = nullptr;
	sNode* nodeEnd = nullptr;
};

