//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
#include <vector>
#include <Math/Utils.h>
#include <GameManager/GameManager.h>
#include <UI/UI.h>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <list>
//------------------------------------------------------------------------

GameManager gameManager;
UI UISettings;

void Init()
{
	gameManager.Init(UISettings);
	UISettings.Init(gameManager);
}

void Update(float deltaTime)
{
	//OnUserUpdate(gameManager.GetDeltaTime());
	gameManager.Update(deltaTime);
	UISettings.Update(deltaTime);
}

void Render()
{
	
	gameManager.Render();
	UISettings.Render();
}

void Shutdown()
{
}






