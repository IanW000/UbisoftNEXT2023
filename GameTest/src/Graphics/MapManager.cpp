#include "stdafx.h"
#include "MapManager.h"
#include <App/App.h>
#include <Math/Utils.h>
#include <string>


std::vector<CSimpleSprite*> brickSprite;
std::vector<CSimpleSprite*> blockSprite;
std::vector<CSimpleSprite*> grassSprite;

std::vector<CSimpleSprite*> bombSprite;

std::vector<CSimpleSprite*> explosionSprite;
CSimpleSprite* testSprite;

//
Bomb testBomb;

std::vector<Bomb> m_Bombs;

MapManager::MapManager() : m_UISettings(nullptr), deadScreen(false) ,m_deltaTime(0.0f)
{
}

void MapManager::generateMap() {

	for (int i = 0; i < ROW; i++) {
		Mat2D(i, 0) = Mat2D(i, COL - 1) = BLOCK;
	}

	for (int i = 0; i < COL; i++) {
		Mat2D(0, i) = Mat2D(ROW - 1, i) = BLOCK;
	}

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (i % 4 == 0 && j % 4 == 0) {
				Mat2D(i, j) = BLOCK;
			}
		}
	}

	for (int i = 0; i < brickNum; i++) {
		int r = Utils::RandomInt(1, ROW - 2);
		int c = Utils::RandomInt(1, COL - 2);
		if (Mat2D(r, c) == SPACE)
			Mat2D(r, c) = BRICK;
	}

	int x = Utils::RandomInt(2, MapManager::COL - 3);
	int y = Utils::RandomInt(2, MapManager::ROW - 3);


	Mat2D(y + 1, x + 1) = SPACE;
	Mat2D(y + 1, x) = SPACE;
	Mat2D(y + 1, x - 1) = SPACE;
	Mat2D(y, x + 1) = SPACE;
	Mat2D(y, x) = SPACE;
	Mat2D(y, x - 1) = SPACE;
	player.setX(x * MapManager::BLOCK_BRICK_SIZE);
	player.setY(y * MapManager::BLOCK_BRICK_SIZE + 55);

	player.setPlayerLocation();

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			switch (Mat2D(i, j)) {

			case SPACE:
				CSimpleSprite* space;
				space = App::CreateSprite(".\\res\\Sprite\\Ground.bmp", 1, 1);
				space->SetPosition(j * (float)BLOCK_BRICK_SIZE + 16, i * (float)BLOCK_BRICK_SIZE + 16);

				space->SetScale(0.2f);
				grassSprite.push_back(space);
				break;

			case BLOCK:
				CSimpleSprite* block;
				block = App::CreateSprite(".\\res\\Sprite\\Block.bmp", 1, 1);
				block->SetPosition(j * (float)BLOCK_BRICK_SIZE + 16, i * (float)BLOCK_BRICK_SIZE + 16);

				block->SetScale(0.2f);
				blockSprite.push_back(block);
				break;

			case BRICK:
				CSimpleSprite* brick;
				brick = App::CreateSprite(".\\res\\Sprite\\Brick.bmp", 1, 1);
				brick->SetPosition(j * (float)BLOCK_BRICK_SIZE + 16, i * (float)BLOCK_BRICK_SIZE + 16);

				brick->SetScale(0.2f);
				brickSprite.push_back(brick);
				break;

			}
		}
	}
}

void MapManager::resetMap() {

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
				Mat2D(i, j) = SPACE;
		}
	}

	grassSprite.clear();
	brickSprite.clear();
	blockSprite.clear();

}

void MapManager::placeBomb(int x, int y) {
	
	float bombX = y * 32 + 16.0f;
	float bombY = x * 32 + 16.0f;

	CSimpleSprite* bomb;
	bomb = App::CreateSprite(".\\res\\Sprite\\Bomb.bmp", 4, 1);
	float bombSpeed = 1.0f / 15.0f;
	bomb->SetPosition(bombX ,bombY);
	bomb->CreateAnimation(0, bombSpeed, { 0,1,2,3 });
	bomb->SetScale(0.4f);
	bombSprite.push_back(bomb);

	//explosion
	 
	//Timer timer = GetTimer();

	//if (timer.timeElapsed(GetTime()) > 2.0f)
	//{
	explosion(bombX, bombY);
	//	Timer timer = GetTimer();
	//	timer.start = GetTime();
	//	m_timer = timer;
	//}

	//Bomb newBomb;
	//newBomb.Init(player.getX(), player.getY());


	//testBomb = newBomb;
	//m_Bombs.push_back(newBomb);
}

void MapManager::explosion(float bombX, float bombY) {

	//CSimpleSprite* explosionMiddle;
	//explosionMiddle = App::CreateSprite(".\\res\\Sprite\\ExplosionStart.bmp", 8, 1);
	//float bombSpeed = 1.0f / 15.0f;
	//explosionMiddle->SetPosition(bombX, bombY);
	//explosionMiddle->CreateAnimation(0, bombSpeed, { 0,1,2,3,4,5,6,7 });
	//explosionMiddle->SetScale(0.2f);

	testSprite = App::CreateSprite(".\\res\\Sprite\\ExplosionStart.bmp", 8, 1);
	testSprite->SetPosition(bombX, bombY);
	testSprite->CreateAnimation(0, 1.0f / 15.0f, { 0,1,2,3,4,5,6,7 });
	testSprite->SetScale(0.2f);



	//CSimpleSprite* explosionTop;
	//explosionMiddle = App::CreateSprite(".\\res\\Sprite\\ExplosionMiddle.bmp", 8, 1);
	//explosionMiddle->SetPosition(bombX, bombY+32);
	//explosionMiddle->CreateAnimation(0, bombSpeed, { 0,1,2,3,4,5,6,7 });
	//explosionMiddle->SetScale(0.4f);

	//CSimpleSprite* explosionDown;
	//explosionMiddle = App::CreateSprite(".\\res\\Sprite\\ExplosionMiddle.bmp", 8, 1);
	//explosionMiddle->SetPosition(bombX, bombY-32);
	//explosionMiddle->CreateAnimation(0, bombSpeed, { 0,1,2,3,4,5,6,7 });
	//explosionMiddle->SetScale(0.4f);

	//CSimpleSprite* explosionLeft;
	//explosionMiddle = App::CreateSprite(".\\res\\Sprite\\ExplosionMiddle.bmp", 8, 1);
	//explosionMiddle->SetPosition(bombX+32, bombY);
	//explosionMiddle->CreateAnimation(0, bombSpeed, { 0,1,2,3,4,5,6,7 });
	//explosionMiddle->SetScale(0.4f);

	//CSimpleSprite* explosionRight;
	//explosionMiddle = App::CreateSprite(".\\res\\Sprite\\ExplosionMiddle.bmp", 8, 1);
	//explosionMiddle->SetPosition(bombX+32, bombY);
	//explosionMiddle->CreateAnimation(0, bombSpeed, { 0,1,2,3,4,5,6,7 });
	//explosionMiddle->SetScale(0.4f);


	//explosionSprite.push_back(explosionMiddle);
	//explosionSprite.push_back(explosionTop);
	//explosionSprite.push_back(explosionDown);
	//explosionSprite.push_back(explosionLeft);
	//explosionSprite.push_back(explosionRight);
}

void MapManager::Init(UI& UISettings)
{
	m_UISettings = &UISettings;

	player.Init();
}


void MapManager::Update(float deltaTime)
{

	SetTime(deltaTime);

	switch ((*m_UISettings).getCurrentScreen()) {

		case Screens::MAINMENU:

			player.Reset();
			deadScreen = false;
			break;

		case Screens::GAME:

			player.Update(deltaTime,Mat2D);
			break;
	}

	if (player.died && !deadScreen) {
		deadScreen = true;

		(*m_UISettings).setCurrentScreen(Screens::DEAD);
	}


	if (App::IsKeyPressed('J'))
	{
		Timer timer = GetTimer();

		if (timer.timeElapsed(GetTime()) > timer.cooldown && GetTimer().inventory > 0 && Mat2D((int)player.getY() / MapManager::BLOCK_BRICK_SIZE, (int)player.getX() / MapManager::BLOCK_BRICK_SIZE) == SPACE)
		{
			explosion((float)player.getX(), (float)player.getY());
			//placeBomb((int)player.getY() / MapManager::BLOCK_BRICK_SIZE, (int)player.getX() / MapManager::BLOCK_BRICK_SIZE);
			Timer timer = GetTimer();
			timer.start = GetTime();
			m_timer = timer;
		}
	}
	
	//for (auto explosion : explosionSprite) {
	//	explosion->Update(deltaTime);
	//	explosion->SetAnimation(0);
	//	if (explosion->GetFrame())
	//		explosion->SetAnimation(-1);
	//}

	//for (auto bomb : bombSprite) {
	//	bomb->Update(deltaTime);
	//	bomb->SetAnimation(0);
	//}

	//for (auto bombs : m_Bombs) {
	//	bombs.Update(deltaTime);
	//}

	//testBomb.Update(deltaTime);

	testSprite->Update(deltaTime);
	testSprite->SetAnimation(0);
}


void MapManager::Render()
{
	//Draw the map
	for (auto block : blockSprite) {
		block->Draw();
	}
	for (auto brick : brickSprite) {
		brick->Draw();
	}
	for (auto space : grassSprite) {
		space->Draw();
	}

	///BLOCK_BRICK_SIZE
	//std::string debugLine = std::to_string(testSave);


	App::Print(40, 650, "Debug:", 1.0f, .25f, .5f, GLUT_BITMAP_HELVETICA_18);
	//App::Print(120, 650, debugLine.c_str(), 1.0f, .25f, .5f, GLUT_BITMAP_HELVETICA_18);

	if (m_Bombs.size() > 4) {
		App::Print(120, 630, std::to_string(m_Bombs[0].getBombX()).c_str(), 1.0f, .25f, .5f, GLUT_BITMAP_HELVETICA_18);
		App::Print(120, 610, std::to_string(m_Bombs[1].getBombX()).c_str(), 1.0f, .25f, .5f, GLUT_BITMAP_HELVETICA_18);
		App::Print(120, 590, std::to_string(m_Bombs[2].getBombX()).c_str(), 1.0f, .25f, .5f, GLUT_BITMAP_HELVETICA_18);
		App::Print(120, 570, std::to_string(m_Bombs[3].getBombX()).c_str(), 1.0f, .25f, .5f, GLUT_BITMAP_HELVETICA_18);
	}

	//draw objects
	player.Render();


	//for (auto bomb : bombSprite) {
	//	bomb->Draw();
	//}

	//for (auto explosion : explosionSprite) {
	//	explosion->Draw();
	//}

	//for (auto bombs : m_Bombs) {
	//	bombs.Render();
	//}

	//testBomb.Render();
	testSprite->Draw();
}

void MapManager::SetTime(float deltaTime) {
	m_deltaTime = deltaTime;
	m_current = std::chrono::steady_clock::now();
	m_time = m_current - m_start;
}
float MapManager::GetDeltaTime() const
{
	return m_deltaTime;
}

Timer MapManager::GetTimer() const
{
	return m_timer;

	//return m_timer;
}

float MapManager::GetTime() const
{
	return m_time.count();
}

void MapManager::SetPause(std::chrono::time_point<std::chrono::steady_clock> pause)
{
	m_start += std::chrono::steady_clock::now() - pause;
}