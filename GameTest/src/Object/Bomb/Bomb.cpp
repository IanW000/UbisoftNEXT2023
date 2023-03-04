#include "stdafx.h"
#include "Bomb.h"
#include <App/App.h>

CSimpleSprite* bomBSprite;

Bomb::Bomb() :explosion(false), inventory(1),power(1), x (0), y (0)
{

}

void Bomb::Init(int x, int y)
{
	bomBSprite = App::CreateSprite(".\\res\\Sprite\\Bomb.bmp", 3, 1);
	float bombSpeed = 1.0f / 15.0f;
	bomBSprite->SetPosition((float)x, (float)y);
	bomBSprite->CreateAnimation(ANIM_BOMB, bombSpeed, { 0,1,2,3 });
	bomBSprite->SetScale(0.3f);
}

void Bomb::Update(float deltaTime)
{
	bomBSprite->Update(deltaTime);
	bomBSprite->SetAnimation(ANIM_BOMB);
}

void Bomb::Render()
{
	bomBSprite->Draw();
}




