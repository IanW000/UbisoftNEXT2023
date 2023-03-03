#pragma once
#include <UI/UI.h>
#include <Object/Player/Player.h>
#include <string>

struct MouseInput {
	float x, y;
};

class GameManager {
public:

	GameManager();


	UI UISettings;
	Player player;

	static MouseInput getMousePosition();
	void Init();
	void Update(float deltaTime);
	void Render();
	float GetDeltaTime() const;
	std::string debugLine;

	bool deadScreen = false;


private:
};
