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
	//scene.Init(UISettings);
	scene.Init();
	gameManager.Init();
	//UISettings.Init();
	UISettings.Init(scene);
}

void Update(float deltaTime)
{
	scene.Update(deltaTime);
	gameManager.Update(deltaTime);
	UISettings.Update(deltaTime);
}

void Render()
{
	scene.Render();
	gameManager.Render();
	UISettings.Render();
}

void Shutdown()
{
}