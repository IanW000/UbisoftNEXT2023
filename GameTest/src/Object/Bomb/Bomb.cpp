#include "stdafx.h"
#include "Bomb.h"
#include <App/App.h>

CSimpleSprite* bombSprite;

Bomb::Bomb() :explosion(false), inventory(1),power(1), bombX (0), bombY(0), bombState(NORMAL)
{

}

void Bomb::Init(int x, int y)
{

	bombX = x;
	bombY = y;

	bombSprite = App::CreateSprite(".\\res\\Sprite\\Bomb.bmp", 4, 1);
	float bombSpeed = 1.0f / 15.0f;
	bombSprite->SetPosition((float)bombX, (float)bombY -5);
	bombSprite->CreateAnimation(0, bombSpeed, { 0,1,2,3 });
	bombSprite->SetScale(0.4f);
}

void Bomb::Update(float deltaTime)
{
	bombSprite->Update(deltaTime);
	bombSprite->SetAnimation(0);
}

void Bomb::Render()
{
	bombSprite->Draw();
}

int Bomb::getBombX()
{
	return bombX;
}

int Bomb::getBombY()
{
	return bombY;
}




