#include "stdafx.h"
#include "Player.h"
#include <App/app.h>
#include <Math/Utils.h>
#include <gameManager/gameManager.h>

CSimpleSprite* playerSprite;
CSimpleSprite* diedSprite;


Player::Player() : currentHP(100), isDied(false), locX(-50), locY(-50), speed(1.0f)
{
}

void Player::Reset()
{
	currentHP = 100;
	isDied = false;
	speed = 1;
}

void Player::Init(GameManager& gameManager)
{
	playerSprite = App::CreateSprite(".\\res\\Sprite\\Player.bmp", 4, 4);
	diedSprite = App::CreateSprite(".\\res\\Sprite\\DeathAnimation.bmp", 6, 1);

	playerSprite->SetPosition((float)locX, (float)locY);
	float playerSpeed = 1.0f / 15.0f;
	playerSprite->CreateAnimation(ANIM_BACKWARDS, playerSpeed, { 4,5,6,7 });
	playerSprite->CreateAnimation(ANIM_LEFT, playerSpeed, { 8,9,10,11 });
	playerSprite->CreateAnimation(ANIM_RIGHT, playerSpeed, { 12,13,14,15 });
	playerSprite->CreateAnimation(ANIM_FORWARDS, playerSpeed, { 0,1,2,3 });
	playerSprite->SetScale(0.15f);

	diedSprite->CreateAnimation(0, playerSpeed*2, { 0,1,2,3,4,5 });
	diedSprite->SetScale(0.15f);
}

void Player::Update(GameManager& gameManager)
{
	m_Matrix = gameManager.Mat2D;
	playerSprite->Update(gameManager.GetDeltaTime());

	//movement
	if(!isDied)
	{	
		if (App::IsKeyPressed('D'))
		{
			playerSprite->SetAnimation(ANIM_RIGHT);
			float x, y;
			playerSprite->GetPosition(x, y);
			if (gameManager.Mat2D((int)(locY - 16.0f) / GameManager::BLOCK_BRICK_SIZE, (int)(locX + 16.0f) / GameManager::BLOCK_BRICK_SIZE) == SPACE) {
				locX = (int)x;
				x += speed;
				playerSprite->SetPosition(x, y);
			}
		}

		if (App::IsKeyPressed('A'))
		{
			playerSprite->SetAnimation(ANIM_LEFT);
			float x, y;
			playerSprite->GetPosition(x, y);

			if (gameManager.Mat2D((int)(locY - 16.0f) / GameManager::BLOCK_BRICK_SIZE, (int)(locX - 16.0f) / GameManager::BLOCK_BRICK_SIZE) == SPACE) {
				locX = (int)x;
				x -= speed;
				playerSprite->SetPosition(x, y);
			}
		}

		if (App::IsKeyPressed('W'))
		{
			playerSprite->SetAnimation(ANIM_FORWARDS);

			float x, y;
			playerSprite->GetPosition(x, y);

			if (gameManager.Mat2D((int)(locY + 16.0f) / GameManager::BLOCK_BRICK_SIZE, (int)locX / GameManager::BLOCK_BRICK_SIZE) == SPACE) {
				locY = (int)y;
				y += speed;
				playerSprite->SetPosition(x, y);
			}
		}

		if (App::IsKeyPressed('S'))
		{
			playerSprite->SetAnimation(ANIM_BACKWARDS);
			float x, y;
			playerSprite->GetPosition(x, y);

			if (gameManager.Mat2D((int)(locY - 25.0f) / GameManager::BLOCK_BRICK_SIZE, (int)locX / GameManager::BLOCK_BRICK_SIZE) == SPACE) {

				locY = (int)y;
				y -= speed;

				playerSprite->SetPosition(x, y);
			}
		}
	}
	//DEBUGGING
	if (App::IsKeyPressed('M'))
	{
		currentHP -= 1;
	}

	if (currentHP <= 0) {
		diedSprite->Update(gameManager.GetDeltaTime());
		diedSprite->SetAnimation(0);
		diedSprite->SetPosition((float)locX, (float)locY);
		currentHP = 0;
		isDied = true;
	}
}

void Player::Render(GameManager& gameManager)
{
	if (gameManager.getUI()->getCurrentScreen() == Screens::GAME|| gameManager.getUI()->getCurrentScreen() == Screens::DEAD || gameManager.getUI()->getCurrentScreen() == Screens::PAUSE) {
		if (isDied) {
			diedSprite->Draw();
			if (diedSprite->GetFrame() == 5) {
				diedSprite->SetAnimation(-1);
			}
		}
		else {
			playerSprite->Draw();
		}
	}
}

int Player::getX()
{
	return locX;
}

int Player::getY()
{
	return locY;
}
void Player::setX(int x) {
	locX = x;
}

void Player::setY(int y) {
	locY = y;
}
void Player::setLocation() {
	playerSprite->SetPosition((float)locX, (float)locY);
}
void Player::setHP(int loseHp) {

	currentHP -= loseHp;

}

bool Player::checkDied()
{
	return isDied;
}

float Player::getSpeed()
{
	return speed;
}

void Player::addSpeed(float speed)
{
	this->speed += speed;
}

void Player::setDied(bool died)
{
	this->isDied = isDied;
}


int Player::getHp() {

	return currentHP;
}

