#include "stdafx.h"
#include "Player.h"
#include <App/app.h>
#include <Math/Utils.h>
#include <Graphics/Scene.h>

CSimpleSprite* playerSprite;
CSimpleSprite* diedSprite;


Player::Player() : currentHP(100), died(false), playerX(0), playerY(0), playerWidth(16),playerHeight(16)
{
}

void Player::Reset()
{
	currentHP = 100;
	died = false;
}


void Player::Init() {
	
	playerSprite = App::CreateSprite(".\\res\\Sprite\\Player.bmp", 4, 4);
	diedSprite = App::CreateSprite(".\\res\\Sprite\\DeathAnimation.bmp", 6, 1);

	playerSprite->SetPosition((float)playerX, (float)playerY);
	float playerSpeed = 1.0f / 15.0f;
	playerSprite->CreateAnimation(ANIM_BACKWARDS, playerSpeed, { 4,5,6,7 });
	playerSprite->CreateAnimation(ANIM_LEFT, playerSpeed, { 8,9,10,11 });
	playerSprite->CreateAnimation(ANIM_RIGHT, playerSpeed, { 12,13,14,15 });
	playerSprite->CreateAnimation(ANIM_FORWARDS, playerSpeed, { 0,1,2,3 });
	playerSprite->SetScale(0.2f);

	diedSprite->CreateAnimation(0, playerSpeed, { 0,1,2,3,4,5 });
	diedSprite->SetScale(0.2f);
}

void Player::Update(float deltaTime, Matrix Mat2d)
{
	m_Matrix = Mat2d;
	playerSprite->Update(deltaTime);

	if (App::IsKeyPressed('D'))
	{
		playerSprite->SetAnimation(ANIM_RIGHT);
		float x, y;
		playerSprite->GetPosition(x, y);
		if (Mat2d((int)(playerY-16.0f) / Scene::BLOCK_BRICK_SIZE, (int)(playerX + 16.0f) / Scene::BLOCK_BRICK_SIZE) == SPACE) {
			playerX = (int)x;
			x += 1.0f;
			playerSprite->SetPosition(x, y);
		}
	}

	if (App::IsKeyPressed('A'))
	{
		playerSprite->SetAnimation(ANIM_LEFT);
		float x, y;
		playerSprite->GetPosition(x, y);

		if (Mat2d((int)(playerY-16.0f) / Scene::BLOCK_BRICK_SIZE, (int)(playerX- 16.0f) / Scene::BLOCK_BRICK_SIZE) == SPACE){
			playerX = (int)x;
			x -= 1.0f;
			playerSprite->SetPosition(x, y);
		}
	}

	if (App::IsKeyPressed('W'))
	{
		playerSprite->SetAnimation(ANIM_FORWARDS);

		float x, y;
		playerSprite->GetPosition(x, y);

		if (Mat2d((int)(playerY + 10.0f) / Scene::BLOCK_BRICK_SIZE, (int)playerX / Scene::BLOCK_BRICK_SIZE) == SPACE) {
			playerY = (int)y;
			y += 1.0f;
			playerSprite->SetPosition(x, y);
		}
	}

	if (App::IsKeyPressed('S'))
	{
		playerSprite->SetAnimation(ANIM_BACKWARDS);
		float x, y;
		playerSprite->GetPosition(x, y);

		if (Mat2d((int)(playerY - 25.0f) / Scene::BLOCK_BRICK_SIZE, (int)playerX / Scene::BLOCK_BRICK_SIZE) == SPACE) {

			playerY = (int)y;
			y -= 1.0f;

			playerSprite->SetPosition(x, y);
		}
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
		diedSprite->SetAnimation(0);
		diedSprite->SetPosition((float)playerX, (float)playerY);
	}
}

void Player::Render()
{
	playerSprite->Draw();
	//wait 2 seconds
	if (died) {
		//delete playerSprite;
		diedSprite->Draw();
	}
}

int Player::getX()
{
	return playerX;
}

int Player::getY()
{
	return playerY;
}
void Player::setX(int x) {
	playerX = x;
}

void Player::setY(int y) {
	playerY = y;
}
void Player::setPlayerLocation() {
	playerSprite->SetPosition(playerX, playerY);
}

