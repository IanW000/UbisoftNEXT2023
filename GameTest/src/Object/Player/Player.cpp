#include "stdafx.h"
#include "Player.h"
#include <App/app.h>
#include <Math/Utils.h>
#include <Graphics/Scene.h>

CSimpleSprite* playerSprite;

Player::Player() : currentHP(100), died(false), playerX(0), playerY(0)
{
}

void Player::Reset()
{
	currentHP = 100;
	died = false;
}


void Player::Init(Matrix Mat2D) {

	playerSprite = App::CreateSprite(".\\res\\Sprite\\Player.bmp", 4, 4);


	while (1) {
		int x = Utils::RandomInt(1, Scene::ROW - 2);
		int y = Utils::RandomInt(1, Scene::COL - 2);
		if (Mat2D(x,y) == SPACE) {
			playerX = y * Scene::BLOCK_BRICK_SIZE;
			playerY = x * Scene::BLOCK_BRICK_SIZE;
			break;
		}
	}

	playerSprite->SetPosition((float)playerX + 18, (float)playerY + 24);
	float playerSpeed = 1.0f / 15.0f;
	playerSprite->CreateAnimation(ANIM_BACKWARDS, playerSpeed, { 4,5,6,7 });
	playerSprite->CreateAnimation(ANIM_LEFT, playerSpeed, { 8,9,10,11 });
	playerSprite->CreateAnimation(ANIM_RIGHT, playerSpeed, { 12,13,14,15 });
	playerSprite->CreateAnimation(ANIM_FORWARDS, playerSpeed, { 0,1,2,3 });
	playerSprite->SetScale(0.2f);
}

void Player::Update(float deltaTime)
{
	playerSprite->Update(deltaTime);

	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		playerSprite->SetAnimation(ANIM_RIGHT);
		float x, y;
		playerSprite->GetPosition(x, y);
		x += 1.0f;
		playerSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		playerSprite->SetAnimation(ANIM_LEFT);
		float x, y;
		playerSprite->GetPosition(x, y);
		x -= 1.0f;
		playerSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		playerSprite->SetAnimation(ANIM_FORWARDS);
		float x, y;
		playerSprite->GetPosition(x, y);
		y += 1.0f;
		playerSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		playerSprite->SetAnimation(ANIM_BACKWARDS);
		float x, y;
		playerSprite->GetPosition(x, y);
		y -= 1.0f;
		playerSprite->SetPosition(x, y);
	}


	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		playerSprite->SetAnimation(-1);
	}

	if (App::IsKeyPressed('J'))
	{
		//boom.x = 
	}



	if (App::IsKeyPressed('M'))
	{
		currentHP -= 1;
	}

	if (App::IsKeyPressed('N'))
	{
		Reset();
	}
	if (currentHP <= 0) {
		currentHP = 0;
		died = true;
	}
}

void Player::Render()
{
	playerSprite->Draw();
}