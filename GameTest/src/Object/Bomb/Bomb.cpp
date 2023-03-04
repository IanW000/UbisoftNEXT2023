#include "stdafx.h"
#include "Bomb.h"
#include <App/App.h>

CSimpleSprite* bomBSprite;

Bomb::Bomb() :explosion(false), inventory(1),power(1), x (0), y (0)
{

}

void Bomb::Init(int x, int y)
{
	bomBSprite = App::CreateSprite(".\\res\\Sprite\\Bomb.bmp", 4, 1);
	float bombSpeed = 1.0f / 15.0f;
	bomBSprite->SetPosition(400, 400);
	//bomBSprite->SetPosition((float)x, (float)y);
	bomBSprite->CreateAnimation(0, bombSpeed, { 0,1,2,3 });
	bomBSprite->SetScale(2.0f);
}

void Bomb::Update()
{
	bomBSprite->SetAnimation(0);
}

void Bomb::Render()
{
	bomBSprite->Draw();
}




