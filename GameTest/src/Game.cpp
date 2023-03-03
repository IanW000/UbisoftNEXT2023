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
#include "Render/Renderer.h"
//------------------------------------------------------------------------

GameManager gameManager;
Renderer renderer;


void Init()
{

	renderer.Init();

	gameManager.Init();
}

void Update(float deltaTime)
{
	//------------------------------------------------------------------------
// Example Sprite Code....
	renderer.Update(deltaTime);
	gameManager.Update(deltaTime);
}

std::string debugLine;

void Render()
{
	//debugLine = std::to_string(map[0][0]);
	App::Print(40, 650, "Debug:", 1.0f, .25f, .5f, GLUT_BITMAP_HELVETICA_18);
	App::Print(120, 650, debugLine.c_str(), 1.0f, .25f, .5f, GLUT_BITMAP_HELVETICA_18);

	renderer.Render();
	gameManager.Render();

}

void Shutdown()
{	
	//delete playerSprite;
}