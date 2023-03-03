#pragma once

#include <string>

struct MouseInput {
	float x, y;
};

class GameManager {
public:

	GameManager();

	static MouseInput getMousePosition();
	void Init();
	void Update(float deltaTime);
	void Render();
	float GetDeltaTime() const;
	std::string debugLine;

	bool deadScreen = false;


private:
};
