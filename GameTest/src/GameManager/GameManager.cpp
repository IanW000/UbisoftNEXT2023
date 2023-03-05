#include "stdafx.h"
#include "GameManager.h"
#include <App/App.h>
#include <Math/Utils.h>
#include <string>

std::vector<CSimpleSprite*> brickSprite;
std::vector<CSimpleSprite*> blockSprite;

GameManager::GameManager() : m_UISettings(nullptr), deadScreen(false) ,m_deltaTime(0.0f)
{
	m_start = std::chrono::steady_clock::now();
	m_current = m_start;
	m_time = m_current - m_start;
}

void GameManager::Init(UI& UISettings)
{
	m_UISettings = &UISettings;
	m_player.Init(*this);
	m_enemy.Init(*this);
	m_bomb.Init(*this);
	m_powerUp.Init(*this);

}

void GameManager::Update(float deltaTime)
{
	SetTime(deltaTime);

	if(App::IsKeyPressed('J') ){
		PlaceBomb(0);
	}

	switch ((*m_UISettings).getCurrentScreen()) {

		case Screens::MAINMENU:
			glClearColor((float)0 / 255, (float)70 / 255, (float)0 / 255, 1);
			m_player.Reset();
			m_enemy.Reset();
			deadScreen = false;
			break;

		case Screens::GAME:
			glClearColor((float)0/255, (float)100/255, (float)0/255, 1);

			m_player.Update(*this);
			m_enemy.Update(*this);
			m_bomb.Update(*this);
			m_powerUp.Update(*this);

			break;

		case Screens::DEAD:
			glClearColor((float)0 / 255, (float)100 / 255, (float)0 / 255, 1);
			m_enemy.Update(*this);
			m_player.Update(*this);

			break;
	}

	if (m_player.checkDied() && !deadScreen) {

		deadScreen = true;
		(*m_UISettings).setCurrentScreen(Screens::DEAD);
	}

}

void GameManager::Render()
{
	//Draw tilemap
	for (auto block : blockSprite) {
		block->Draw();
	}
	for (auto brick : brickSprite) {
		brick->Draw();
	}

	//draw components
	m_player.Render(*this);
	m_enemy.Render(*this);

	if (getUI()->getCurrentScreen() == Screens::GAME) {
		m_bomb.Render(*this);
		m_powerUp.Render(*this);
	}
}


void GameManager::generateMap() {

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

	int x = Utils::RandomInt(2, GameManager::COL - 3);
	int y = Utils::RandomInt(2, GameManager::ROW - 3);


	Mat2D(y + 1, x + 1) = SPACE;
	Mat2D(y + 1, x) = SPACE;
	Mat2D(y + 1, x - 1) = SPACE;
	Mat2D(y, x + 1) = SPACE;
	Mat2D(y, x) = SPACE;
	Mat2D(y, x - 1) = SPACE;

	m_player.setX(x * GameManager::BLOCK_BRICK_SIZE);
	m_player.setY(y * GameManager::BLOCK_BRICK_SIZE + 35);
	m_player.setLocation();

	int EnemyX = GameManager::COL  - x;
	int EnemyY = GameManager::ROW  - y-2;

	Mat2D(EnemyY + 1, EnemyX + 1) = SPACE;
	Mat2D(EnemyY + 1, EnemyX) = SPACE;
	Mat2D(EnemyY + 1, EnemyX - 1) = SPACE;
	Mat2D(EnemyY, EnemyX + 1) = SPACE;
	Mat2D(EnemyY, EnemyX) = SPACE;
	Mat2D(EnemyY, EnemyX - 1) = SPACE;

	m_enemy.setX(EnemyX * GameManager::BLOCK_BRICK_SIZE);
	m_enemy.setY(EnemyY * GameManager::BLOCK_BRICK_SIZE + 35);
	m_enemy.setLocation();

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			switch (Mat2D(i, j)) {

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

void GameManager::resetMap() {

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			Mat2D(i, j) = SPACE;
		}
	}

	brickSprite.clear();
	blockSprite.clear();
}



void GameManager::UpdateMap(int xaxis, int yaxis) {

	brickSprite.clear();

	for (int i = 0; i < ROW; i++) {

		for (int j = 0; j < COL; j++) {

			if (Mat2D(i, j) == BRICK) {

				CSimpleSprite* brick;
				brick = App::CreateSprite(".\\res\\Sprite\\Brick.bmp", 1, 1);
				brick->SetPosition(j * (float)BLOCK_BRICK_SIZE + 16, i * (float)BLOCK_BRICK_SIZE + 16);

				brick->SetScale(0.2f);
				brickSprite.push_back(brick);

			}
		}
	}
}


void GameManager::PlaceBomb(int id)
{

	float current = GetTime();

	Timer timer = GetTimer(id);

	int xaxis = (int)(m_player.getX() - 16) / BLOCK_BRICK_SIZE;
	int yaxis = (int)(m_player.getY() - 16) / BLOCK_BRICK_SIZE;
	float bombX = (int)m_player.getX() / BLOCK_BRICK_SIZE * 32 + 16.0f;
	float bombY = (int)m_player.getY() / BLOCK_BRICK_SIZE * 32 + 16.0f;

	if (timer.timeElapsed(current) > timer.cooldown)
	{
		Timer timer = GetTimer(id);
		timer.start = GetTime();
		BomberTimer(id, timer);
		GetBombs().spawnBomb(*this, bombX, bombY);
	}
}

void GameManager::SetTime(float deltaTime) {
	m_deltaTime = deltaTime;
	m_current = std::chrono::steady_clock::now();
	m_time = m_current - m_start;
}
float GameManager::GetDeltaTime() const
{
	return m_deltaTime;
}


float GameManager::GetTime() const
{
	return m_time.count();
}

void GameManager::SetPause(std::chrono::time_point<std::chrono::steady_clock> pause)
{
	m_start += std::chrono::steady_clock::now() - pause;
}

UI* GameManager::getUI()
{
	return m_UISettings;
}


Timer GameManager::GetTimer(int id) const
{
	return m_timer[id];
}


Bomb& GameManager::GetBombs()
{
	return m_bomb;
}


Player& GameManager::GetPlayer()
{
	return m_player;
}

Enemy& GameManager::GetEnemy()
{
	return m_enemy;
}

void GameManager::BomberTimer(int id, Timer timer)
{
	m_timer[id] = timer;
}

int GameManager::CreateId()
{
	m_timer.push_back(Timer());
	m_id++;
	return m_id - 1; // Array index starts at 0
}