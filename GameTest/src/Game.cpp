//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
#include <GameManager/GameManager.h>
#include <vector>
#include "Graphics/Scene.h"
#include <UI/UI.h>
//------------------------------------------------------------------------

GameManager gameManager;
Scene scene;
UI UISettings;


void Init()
{

	scene.Init();
	gameManager.Init();
	UISettings.Init();
}

void Update(float deltaTime)
{
	//------------------------------------------------------------------------
// Example Sprite Code....
	scene.Update(deltaTime);
	gameManager.Update(deltaTime);
	UISettings.Update(deltaTime);
}

std::string debugLine;

void Render()
{
	scene.Render();
	gameManager.Render();
	UISettings.Render();
}

void Shutdown()
{	
	//delete playerSprite;
}