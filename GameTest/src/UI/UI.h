#pragma once
#include <chrono>
#include <App/app.h>
#include "Button/Button.h"
#include "HPBar/HPBar.h"
#include <Object/Player/Player.h>

class GameManager;

enum class Screens {
	MAINMENU,
	CONTROLS,
	GAME,
	PAUSE,
	DEAD,
	WIN
};


class UI {
public:
	UI();
	void Init(GameManager& gameManager);
	void Update(float deltaTime);
	void Render();

	HPBar playerHP;
	HPBar enemyHP;
	Button StartButton, ControlsButton, ExitButton, BackButton, PauseButton, BackButtonInGame, ResumeButton;
	Screens getCurrentScreen() const;
	void CenteringPrint(float x, float y, const char* st, float r, float g, float b, void* font, bool center);
	void setCurrentScreen(Screens screen);
	void addBombsUp();
	void addSpeedUp();
	void addFireUp();

private:
	Player m_player;
	GameManager *m_gameManager;
	Screens currentScreen;
	bool failSFXPlayedOnce, winSFXPlayedOnce;
	int bombsUp, speedUp, fireUp;
};
