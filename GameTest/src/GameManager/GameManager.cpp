#include "stdafx.h"
#include "GameManager.h"
#include "App/app.h"
#include <App/main.h>

GameManager::GameManager()
{
}

MouseInput GameManager::getMousePosition()
{
	MouseInput newMousePos;
	POINT mousePos;
	GetCursorPos(&mousePos);	// Get the mouse cursor 2D x,y position			
	ScreenToClient(MAIN_WINDOW_HANDLE, &mousePos);
	newMousePos.x = (float)mousePos.x;
	newMousePos.y = (float)mousePos.y;
	newMousePos.x = ((float)mousePos.x * (2.0f / WINDOW_WIDTH) - 1.0f);
	newMousePos.y = ((float)mousePos.y * (2.0f / WINDOW_HEIGHT) - 1.0f);;
	return newMousePos;
};

void GameManager::Init() {

	App::PlaySound(".\\res\\Sound\\mainMenuBGM.wav", true);
	UISettings.Init(player);
}

void GameManager::Update(float deltaTime) {


	switch (UISettings.getCurrentScreen()) {

	case Screens::MAINMENU:

		player.Reset();
		deadScreen = false;
		break;

	case Screens::GAME:

		player.Update(deltaTime);
		break;
	}

	if (player.died && !deadScreen) {
		deadScreen = true;
		UISettings.setCurrentScreen(Screens::DEAD);
	}


	UISettings.Update(deltaTime, player, deadScreen);
}
void GameManager::Render() {

	UISettings.Render();

	//Debug Line || player.currentHP || (int)UISettings.getCurrentScreen()
	debugLine = std::to_string(player.currentHP);
	App::Print(40, 650, "Debug:", 1.0f, .25f, .5f, GLUT_BITMAP_HELVETICA_18);
	App::Print(120, 650, debugLine.c_str(), 1.0f, .25f, .5f, GLUT_BITMAP_HELVETICA_18);

}

float GameManager::GetDeltaTime() const
{
	return 0.0f;
}