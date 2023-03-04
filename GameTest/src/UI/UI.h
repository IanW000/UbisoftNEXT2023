#pragma once
#include <chrono>
#include <App/app.h>
#include "Button/Button.h"
#include "HPBar/HPBar.h"
#include <Object/Player/Player.h>

class Scene;

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
	HPBar hpBar;
	Button StartButton, ControlsButton, ExitButton, BackButton, PauseButton, BackButtonInGame, ResumeButton;
	Screens getCurrentScreen() const;
	void CenteringPrint(float x, float y, const char* st, float r, float g, float b, void* font, bool center);
	void setCurrentScreen(Screens screen);


	//void Init();
	void Init(Scene &scene);
	void Update(float deltaTime);
	void Render();

private:
	//Player* m_player;
	Scene *m_scene;
	Screens currentScreen;
	bool failSFXPlayedOnce, winSFXPlayedOnce;
};
