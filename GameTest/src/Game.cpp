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
//------------------------------------------------------------------------

GameManager gameManager;

void Init()
{
	gameManager.Init();
}

void Update(float deltaTime)
{
	gameManager.Update(deltaTime);
}

void Render()
{	
	gameManager.Render();
}


void Shutdown()
{	
}