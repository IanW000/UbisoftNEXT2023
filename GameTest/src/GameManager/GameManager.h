#pragma once
#include <chrono>

#include <Object/AI/AI.h>
#include <Math/Matrix/Matrix.h>
#include <Object/Player/Player.h>
#include <Object/Bomb/Bomb.h>
#include <Object/PowerUp/PowerUp.h>
#include <Object/Enemy/Enemy.h>
#include <Math/Timer/Timer.h>
#include <UI/UI.h>



//Screen width pixels 1024, height pixels 768, each block 32*32

enum ATTR {
	SPACE,
	BLOCK,
	BRICK
};

class GameManager
{
public:
	GameManager();
	
	void Init(UI& UISettings);
	void Update(float deltaTime);
	void Render();

	void generateMap();
	void resetMap();
	void UpdateMap(int xaxis,int yaxis);

	int CreateId();
	void SetTime(float deltaTime);
	float GetDeltaTime() const;
	float GetTime() const;
	void SetPause(std::chrono::time_point<std::chrono::steady_clock> pause);
	void PlaceBomb(int id);
	
	const static int WIN_WIDTH = 1024;
	const static int WIN_HEIGHT = 768;
	const static int BLOCK_BRICK_SIZE = 32;
	const static int ROW = WIN_HEIGHT / BLOCK_BRICK_SIZE;
	const static int COL = WIN_WIDTH / BLOCK_BRICK_SIZE;
	const static int brickNum = 200;

	UI * m_UISettings;
	Player m_player;
	Enemy m_enemy;
	Bomb m_bomb;
	PowerUp m_powerUp;
	bool deadScreen;
	Matrix Mat2D;

	UI* getUI();
	Timer GetTimer(int num) const;

	Bomb& GetBombs();
	Player& GetPlayer();
	Enemy& GetEnemy();

	void BomberTimer(int num, Timer timer);

private:

	int m_id;
	float m_deltaTime;
	std::chrono::time_point<std::chrono::steady_clock> m_start;
	std::chrono::time_point<std::chrono::steady_clock> m_current;
	std::chrono::duration<float> m_time;
	std::vector<Timer> m_timer;
};

