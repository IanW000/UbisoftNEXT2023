#pragma once
//#include <string>

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

	//std::string debugLine;

private:
};
