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
	App::PlaySound(".\\res\\mainMenuBGM.wav", true);
	player.Init();
	UISettings.Init();
}

void GameManager::Update(float deltaTime) {
	player.Update(deltaTime);
	UISettings.Update(deltaTime);
}
void GameManager::Render() {
	player.Render();
	UISettings.Render();
}