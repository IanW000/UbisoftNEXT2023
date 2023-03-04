#pragma once
#include <Math/Matrix/Matrix.h>
#include <Object/Player/Player.h>
#include <UI/UI.h>
#include <Object/Bomb/Bomb.h>
#include <Math/Timer/Timer.h>



//Screen width is 1024, height is 768, each object will be 32*32

enum ATTR {
	SPACE,
	BLOCK,
	BRICK
};

class MapManager
{
public:
	MapManager();
	
	void generateMap();
	void resetMap();
	void explosion(float x, float y);
	void placeBomb(int x, int y);

	void Init(UI& UISettings);
	void Update(float deltaTime);
	void Render();


	Timer GetTimer() const;
	void SetTime(float deltaTime);
	float GetDeltaTime() const;
	float GetTime() const;
	void SetPause(std::chrono::time_point<std::chrono::steady_clock> pause);

	
	const static int WIN_WIDTH = 1024;
	const static int WIN_HEIGHT = 768;
	const static int BLOCK_BRICK_SIZE = 32;
	const static int ROW = WIN_HEIGHT / BLOCK_BRICK_SIZE;
	const static int COL = WIN_WIDTH / BLOCK_BRICK_SIZE;
	const static int brickNum = 800;

	UI * m_UISettings;
	Player player;
	bool deadScreen;

private:

	Matrix Mat2D;

	float m_deltaTime;
	std::chrono::time_point<std::chrono::steady_clock> m_start;
	std::chrono::time_point<std::chrono::steady_clock> m_current;
	std::chrono::duration<float> m_time;

	//std::vector<Timer> m_timer;
	Timer m_timer;
	
};

