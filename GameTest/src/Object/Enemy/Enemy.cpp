#include "stdafx.h"
#include "Enemy.h"
#include <list>
#include <GameManager/GameManager.h>
#include <string>
#include <Math/PathFinding.h>
#include <Math/Utils.h>
#include <Math/Timer/Timer.h>

CSimpleSprite* enemySprite;
CSimpleSprite* enemyDiedSprite;

bool Enemy::createEnemy()
{
	// Create a 2D array of nodes - this is for convenience of rendering and construction
		// and is not required for the algorithm to work - the nodes could be placed anywhere
		// in any space, in multiple dimensions...
	nodes = new sNode[GameManager::WIN_WIDTH * GameManager::WIN_WIDTH];
	for (int x = 0; x < GameManager::WIN_WIDTH; x++)
		for (int y = 0; y < GameManager::WIN_WIDTH; y++)
		{
			nodes[y * GameManager::WIN_WIDTH + x].x = x; // ...because we give each node its own coordinates
			nodes[y * GameManager::WIN_WIDTH + x].y = y;
			nodes[y * GameManager::WIN_WIDTH + x].bObstacle = false;
			nodes[y * GameManager::WIN_WIDTH + x].parent = nullptr;
			nodes[y * GameManager::WIN_WIDTH + x].bVisited = false;
		}

	// Create connections - in this case nodes are on a regular grid
	for (int x = 0; x < GameManager::WIN_WIDTH; x++)
		for (int y = 0; y < GameManager::WIN_WIDTH; y++)
		{
			if (y > 0)
				nodes[y * GameManager::WIN_WIDTH + x].vecNeighbours.push_back(&nodes[(y - 1) * GameManager::WIN_WIDTH + (x + 0)]);
			if (y < GameManager::WIN_WIDTH - 1)
				nodes[y * GameManager::WIN_WIDTH + x].vecNeighbours.push_back(&nodes[(y + 1) * GameManager::WIN_WIDTH + (x + 0)]);
			if (x > 0)
				nodes[y * GameManager::WIN_WIDTH + x].vecNeighbours.push_back(&nodes[(y + 0) * GameManager::WIN_WIDTH + (x - 1)]);
			if (x < GameManager::WIN_WIDTH - 1)
				nodes[y * GameManager::WIN_WIDTH + x].vecNeighbours.push_back(&nodes[(y + 0) * GameManager::WIN_WIDTH + (x + 1)]);

			// We can also connect diagonally
			/*if (y>0 && x>0)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x - 1)]);
			if (y<nMapHeight-1 && x>0)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x - 1)]);
			if (y>0 && x<nMapWidth-1)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x + 1)]);
			if (y<nMapHeight - 1 && x<nMapWidth-1)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x + 1)]);
			*/
		}

	// Manually positio the start and end markers so they are not nullptr
	nodeStart = &nodes[(GameManager::WIN_WIDTH / 2) * GameManager::WIN_WIDTH + 1];
	nodeEnd = &nodes[(GameManager::WIN_WIDTH / 2) * GameManager::WIN_WIDTH + GameManager::WIN_WIDTH - 2];
	return true;
}


void Enemy::Init(GameManager& gameManager)
{

	enemySprite = App::CreateSprite(".\\res\\Sprite\\Player.bmp", 4, 4);
	enemyDiedSprite = App::CreateSprite(".\\res\\Sprite\\DeathAnimation.bmp", 6, 1);
	enemySprite->SetPosition(locX,locY);
	float playerSpeed = 1.0f / 15.0f;

	enemySprite->CreateAnimation(ANIM_BACKWARDS, playerSpeed, { 4,5,6,7 });
	enemySprite->CreateAnimation(ANIM_LEFT, playerSpeed, { 8,9,10,11 });
	enemySprite->CreateAnimation(ANIM_RIGHT, playerSpeed, { 12,13,14,15 });
	enemySprite->CreateAnimation(ANIM_FORWARDS, playerSpeed, { 0,1,2,3 });
	enemySprite->SetScale(0.15f);

	enemyDiedSprite->CreateAnimation(0, playerSpeed * 2, { 0,1,2,3,4,5 });
	enemyDiedSprite->SetScale(0.15f);

}

void Enemy::findPath(GameManager& gameManager){

	vector<vector<int>> PathFindingMarix;

	int startX = 1;
	int startY = 1;
	int endX = 5;
	int endY = 5;

	//int startX = (int)(locX-16)/GameManager::BLOCK_BRICK_SIZE;
	//int startY = (int)(locY -16) / GameManager::BLOCK_BRICK_SIZE;
	//int endX = (int)(gameManager.GetPlayer().getX() - 16) / GameManager::BLOCK_BRICK_SIZE;
	//int endY = (int)(gameManager.GetPlayer().getY() - 16) / GameManager::BLOCK_BRICK_SIZE;

	for (int i = 0; i < gameManager.ROW; i++) {
		for (int j = 0; j < gameManager.COL; j++) {
			if (gameManager.Mat2D(i, j) != SPACE)
				PathFindingMarix[i][j] = 1;
			else
				PathFindingMarix[i][j] = 0;
		}
	}
	vector<pair<int, int>> path = PathFinding::a_star_pathfinding(startX,startY,endX,endY,PathFindingMarix);
	int x, y;
	for (int i = 0; i < path.size(); i++) {
		x = path[i].first;
		y = path[i].second;

		locX = y * 32 + 16;
		locY = x * 32 + 16;


		enemySprite->SetPosition(locX, locY);
	}
}


void Enemy::Movement(GameManager& gameManager) {

	float current = gameManager.GetTime();
	Timer timer = gameManager.GetTimer(0);

	if (timer.timeElapsed(current) > 2.0f)
	{

		Timer timer = gameManager.GetTimer(0);
		timer.start = gameManager.GetTime();
		gameManager.BomberTimer(0, timer);
	}

		int rand = Utils::RandomInt(0, 100);
		float x, y;
		switch (rand / 25) {
		case 1:

			enemySprite->SetAnimation(ANIM_LEFT);

			enemySprite->GetPosition(x, y);

			if (gameManager.Mat2D((int)(locY - 16.0f) / GameManager::BLOCK_BRICK_SIZE, (int)(locX - 16.0f) / GameManager::BLOCK_BRICK_SIZE) == SPACE) {
				locX = (int)x;
				x -= speed;
				enemySprite->SetPosition(x, y);

			}
			break;

		case 2:

			enemySprite->SetAnimation(ANIM_RIGHT);

			enemySprite->GetPosition(x, y);
			if (gameManager.Mat2D((int)(locY - 16.0f) / GameManager::BLOCK_BRICK_SIZE, (int)(locX + 16.0f) / GameManager::BLOCK_BRICK_SIZE) == SPACE) {
				locX = (int)x;
				x += speed;
				enemySprite->SetPosition(x, y);
			}
			break;

		case 3:
			enemySprite->SetAnimation(ANIM_FORWARDS);

			enemySprite->GetPosition(x, y);

			if (gameManager.Mat2D((int)(locY + 16.0f) / GameManager::BLOCK_BRICK_SIZE, (int)locX / GameManager::BLOCK_BRICK_SIZE) == SPACE) {
				locY = (int)y;
				y += speed;
				enemySprite->SetPosition(x, y);
			}
			break;

		case 4:
			enemySprite->SetAnimation(ANIM_BACKWARDS);

			enemySprite->GetPosition(x, y);

			if (gameManager.Mat2D((int)(locY - 25.0f) / GameManager::BLOCK_BRICK_SIZE, (int)locX / GameManager::BLOCK_BRICK_SIZE) == SPACE) {
				locY = (int)y;
				y -= speed;
				enemySprite->SetPosition(x, y);
			}
			break;
		}
}
			



void Enemy::Update(GameManager& gameManager)
{
	enemyDiedSprite->Update(gameManager.GetDeltaTime());
	enemySprite->Update(gameManager.GetDeltaTime());
	enemyDiedSprite->SetAnimation(0);
	enemySprite->SetAnimation(0);





	if (App::IsKeyPressed('I')) {

		Movement(gameManager);
	}

		if (App::IsKeyPressed('V') && !findpathonce) {

			//locX++;
			//locY++;
			//enemySprite->SetPosition(locX, locY);

			findpathonce = true;
			findPath(gameManager);
		}

		//	int nNodeSize = 9;
		//	int nNodeBorder = 2;
		//
		//	// Use integer division to nicely get cursor position in node space
		//	int nSelectedNodeX = 300;
		//	int nSelectedNodeY = 300;
		//
		//
		//
		//	nodeStart = &nodes[300 * GameManager::WIN_WIDTH + 300];
		//
		//	nodeEnd = &nodes[500 * GameManager::WIN_WIDTH + 500];
		//
		//	for()
		//
		//	nodes[nSelectedNodeY * GameManager::WIN_WIDTH + nSelectedNodeX].bObstacle = !nodes[nSelectedNodeY * GameManager::WIN_WIDTH + nSelectedNodeX].bObstacle;
		//
		//	AStartPathFinding(); // Solve in "real-time" gives a nice effect
		//
		//	
		//
		//	// Draw Connections First - lines from this nodes position to its
		//	// connected neighbour node positions
		//
		//	for (int x = 0; x < GameManager::WIN_WIDTH; x++)
		//		for (int y = 0; y < GameManager::WIN_WIDTH; y++)
		//		{
		//			for (auto n : nodes[y * GameManager::WIN_WIDTH + x].vecNeighbours)
		//			{
		//				DrawLine(x * nNodeSize + nNodeSize / 2, y * nNodeSize + nNodeSize / 2,
		//					n->x * nNodeSize + nNodeSize / 2, n->y * nNodeSize + nNodeSize / 2, PIXEL_SOLID, FG_DARK_BLUE);
		//			}
		//		}
		//
		//	// Draw Nodes on top
		//	for (int x = 0; x < GameManager::WIN_WIDTH; x++)
		//		for (int y = 0; y < GameManager::WIN_WIDTH; y++)
		//		{
		//
		//			Fill(x * nNodeSize + nNodeBorder, y * nNodeSize + nNodeBorder,
		//				(x + 1) * nNodeSize - nNodeBorder, (y + 1) * nNodeSize - nNodeBorder,
		//				PIXEL_HALF, nodes[y * GameManager::WIN_WIDTH + x].bObstacle ? FG_WHITE : FG_BLUE);
		//
		//			if (nodes[y * GameManager::WIN_WIDTH + x].bVisited)
		//				Fill(x * nNodeSize + nNodeBorder, y * nNodeSize + nNodeBorder, (x + 1) * nNodeSize - nNodeBorder, (y + 1) * nNodeSize - nNodeBorder, PIXEL_SOLID, FG_BLUE);
		//
		//			if (&nodes[y * GameManager::WIN_WIDTH + x] == nodeStart)
		//				Fill(x * nNodeSize + nNodeBorder, y * nNodeSize + nNodeBorder, (x + 1) * nNodeSize - nNodeBorder, (y + 1) * nNodeSize - nNodeBorder, PIXEL_SOLID, FG_GREEN);
		//
		//			if (&nodes[y * GameManager::WIN_WIDTH + x] == nodeEnd)
		//				Fill(x * nNodeSize + nNodeBorder, y * nNodeSize + nNodeBorder, (x + 1) * nNodeSize - nNodeBorder, (y + 1) * nNodeSize - nNodeBorder, PIXEL_SOLID, FG_RED);
		//
		//		}
		//
		//
		//
		//	// Draw Path by starting ath the end, and following the parent node trail
		//	// back to the start - the start node will not have a parent path to follow
		//	if (nodeEnd != nullptr)
		//	{
		//		sNode* p = nodeEnd;
		//		while (p->parent != nullptr)
		//		{
		//			DrawLine(p->x * nNodeSize + nNodeSize / 2, p->y * nNodeSize + nNodeSize / 2,
		//				p->parent->x * nNodeSize + nNodeSize / 2, p->parent->y * nNodeSize + nNodeSize / 2, PIXEL_SOLID, FG_YELLOW);
		//
		//			// Set next node to this node's parent
		//			p = p->parent;
		//		}
		//	}
		//
		//	return true;
		//}

}

void Enemy::Render(GameManager& gameManager)
{
	pair<int, int> haha = make_pair(1, 2);

	App::Print(100, 700, std::to_string(haha.first).c_str(), (float)0 / 255, (float)191 / 255, (float)255 / 255, GLUT_BITMAP_HELVETICA_18);
	App::Print(100, 720, std::to_string(haha.second).c_str(), (float)0 / 255, (float)191 / 255, (float)255 / 255, GLUT_BITMAP_HELVETICA_18);

	if (gameManager.getUI()->getCurrentScreen() == Screens::GAME || gameManager.getUI()->getCurrentScreen() == Screens::DEAD) {
		if (checkDied()) {
			enemyDiedSprite->Draw();
			if (enemyDiedSprite->GetFrame() == 5) {
				enemyDiedSprite->SetAnimation(-1);
			}
		}
		else {
			enemySprite->Draw();
		}
	}

}

//bool Enemy::AStartPathFinding()
//{
//	// Reset Navigation Graph - default all node states
//	for (int x = 0; x < GameManager::WIN_WIDTH; x++)
//		for (int y = 0; y < GameManager::WIN_HEIGHT; y++)
//		{
//			nodes[y * GameManager::WIN_WIDTH + x].bVisited = false;
//			nodes[y * GameManager::WIN_WIDTH + x].fGlobalGoal = INFINITY;
//			nodes[y * GameManager::WIN_WIDTH + x].fLocalGoal = INFINITY;
//			nodes[y * GameManager::WIN_WIDTH + x].parent = nullptr;	// No parents
//		};
//
//	auto distance = [](sNode* a, sNode* b) // For convenience
//	{
//		return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
//	};
//
//	auto heuristic = [distance](sNode* a, sNode* b) // So we can experiment with heuristic
//	{
//		return distance(a, b);
//	};
//
//
//
//	// Setup starting conditions
//	sNode* nodeCurrent = nodeStart;
//	nodeStart->fLocalGoal = 0.0f;
//	nodeStart->fGlobalGoal = heuristic(nodeStart, nodeEnd);
//
//	// Add start node to not tested list - this will ensure it gets tested.
//	// As the algorithm progresses, newly discovered nodes get added to this
//	// list, and will themselves be tested later
//	std::list<sNode*> listNotTestedNodes;
//	listNotTestedNodes.push_back(nodeStart);
//
//	// if the not tested list contains nodes, there may be better paths
//	// which have not yet been explored. However, we will also stop 
//	// searching when we reach the target - there may well be better
//	// paths but this one will do - it wont be the longest.
//	while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd)// Find absolutely shortest path // && nodeCurrent != nodeEnd)
//	{
//		// Sort Untested nodes by global goal, so lowest is first
//		listNotTestedNodes.sort([](const sNode* lhs, const sNode* rhs) { return lhs->fGlobalGoal < rhs->fGlobalGoal; });
//
//		// Front of listNotTestedNodes is potentially the lowest distance node. Our
//		// list may also contain nodes that have been visited, so ditch these...
//		while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
//			listNotTestedNodes.pop_front();
//
//		// ...or abort because there are no valid nodes left to test
//		if (listNotTestedNodes.empty())
//			break;
//
//		nodeCurrent = listNotTestedNodes.front();
//		nodeCurrent->bVisited = true; // We only explore a node once
//
//
//		// Check each of this node's neighbours...
//		for (auto nodeNeighbour : nodeCurrent->vecNeighbours)
//		{
//			// ... and only if the neighbour is not visited and is 
//			// not an obstacle, add it to NotTested List
//			if (!nodeNeighbour->bVisited && nodeNeighbour->bObstacle == 0)
//				listNotTestedNodes.push_back(nodeNeighbour);
//
//			// Calculate the neighbours potential lowest parent distance
//			float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbour);
//
//			// If choosing to path through this node is a lower distance than what 
//			// the neighbour currently has set, update the neighbour to use this node
//			// as the path source, and set its distance scores as necessary
//			if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal)
//			{
//				nodeNeighbour->parent = nodeCurrent;
//				nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;
//
//				// The best path length to the neighbour being tested has changed, so
//				// update the neighbour's score. The heuristic is used to globally bias
//				// the path algorithm, so it knows if its getting better or worse. At some
//				// point the algo will realise this path is worse and abandon it, and then go
//				// and search along the next best path.
//				nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + heuristic(nodeNeighbour, nodeEnd);
//			}
//		}
//	}
//
//	return true;
//}

void Enemy::setLocation() {
	enemySprite->SetPosition((float)locX, (float)locY);
}
