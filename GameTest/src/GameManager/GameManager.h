#pragma once
#include <UI/UI.h>
#include <Object/Player/Player.h>
//#include <string>

struct MouseInput {
	float x, y;
};

class GameManager {
public:

	GameManager();


	Player player;
	UI UISettings;

	static MouseInput getMousePosition();
	void Init();
	void Update(float deltaTime);
	void Render();

	//std::string debugLine;

private:
};
