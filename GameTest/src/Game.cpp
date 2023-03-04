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
#include "Graphics/MapManager.h"
#include <UI/UI.h>
//------------------------------------------------------------------------

GameManager gameManager;
MapManager mapMananger;
UI UISettings;


void Init()
{
	mapMananger.Init(UISettings);
	gameManager.Init();
	UISettings.Init(mapMananger);
}

void Update(float deltaTime)
{
	mapMananger.Update(deltaTime);
	gameManager.Update(deltaTime);
	UISettings.Update(deltaTime);
}

void Render()
{
	mapMananger.Render();
	gameManager.Render();
	UISettings.Render();
}

void Shutdown()
{
}