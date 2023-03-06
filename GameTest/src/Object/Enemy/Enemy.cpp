#include "stdafx.h"
#include "Enemy.h"
#include <list>
#include <GameManager/GameManager.h>
#include <string>
#include <Math/PathFinding.h>
#include <Math/Utils.h>
#include <Math/Timer/Timer.h>
#include <cmath>
#include <Math/PathFinding.cpp>


CSimpleSprite* enemySprite;
CSimpleSprite* enemyDiedSprite;

Enemy::Enemy() : currentHP(100), isDied(false), speed(1.0f), enemyAI(PATROL), lastBombPosX(0.0f), lastBombPosY(0.0f), lastBombTime(0.0f)
{
}


void Enemy::moveFowards()
{
	enemySprite->SetAnimation(ANIM_FORWARDS);
	locY += speed * (*m_gameManager).GetDeltaTime() * 0.03f;
	enemySprite->SetPosition(locX, locY);
}

void Enemy::moveLeft()
{
	enemySprite->SetAnimation(ANIM_LEFT);
	locX -= speed * (*m_gameManager).GetDeltaTime() * 0.03f;
	enemySprite->SetPosition(locX, locY);
}

void Enemy::moveBackwards()
{
	enemySprite->SetAnimation(ANIM_BACKWARDS);
	locY -= speed * (*m_gameManager).GetDeltaTime() * 0.03f;
	enemySprite->SetPosition(locX, locY);
}

void Enemy::moveRight()
{
	enemySprite->SetAnimation(ANIM_RIGHT);
	locX += speed * (*m_gameManager).GetDeltaTime() * 0.03f;
	enemySprite->SetPosition(locX, locY);
}

void Enemy::Init(GameManager& gameManager)
{
	m_gameManager = &gameManager;
	enemySprite = App::CreateSprite(".\\res\\Sprite\\Player.bmp", 4, 4);
	enemyDiedSprite = App::CreateSprite(".\\res\\Sprite\\DeathAnimation.bmp", 6, 1);
	enemySprite->SetPosition((float)locX,(float)locY);
	float playerSpeed = 1.0f / 15.0f;

	enemySprite->CreateAnimation(ANIM_BACKWARDS, playerSpeed, { 4,5,6,7 });
	enemySprite->CreateAnimation(ANIM_LEFT, playerSpeed, { 8,9,10,11 });
	enemySprite->CreateAnimation(ANIM_RIGHT, playerSpeed, { 12,13,14,15 });
	enemySprite->CreateAnimation(ANIM_FORWARDS, playerSpeed, { 0,1,2,3 });
	enemySprite->SetScale(0.15f);

	enemyDiedSprite->CreateAnimation(0, playerSpeed * 2, { 0,1,2,3,4,5 });
	enemyDiedSprite->SetScale(0.15f);

}
void Enemy::Update(GameManager& gameManager)
{

	moveTo(gameManager, gameManager.GetPlayer().getX(), gameManager.GetPlayer().getY());
	const float elapsedTime = gameManager.GetTimeElapsed();
	
	enemyDiedSprite->Update(gameManager.GetDeltaTime());
	enemySprite->Update(gameManager.GetDeltaTime());
	enemyDiedSprite->SetAnimation(0);
	enemySprite->SetAnimation(0);


	float current = gameManager.GetTime();
	Timer timer = gameManager.GetTimer(0);

	if (timer.timeElapsed(current) > 5.0f)
	{
		lastBombPosX = locX;
		lastBombPosX = locY;
		
		gameManager.PlaceBomb(0, locX, locY);
		Timer timer = gameManager.GetTimer(0);
		timer.start = gameManager.GetTime();
		gameManager.BomberTimer(0, timer);
	}


	if (currentHP <= 0) {
		enemyDiedSprite->Update(gameManager.GetDeltaTime());
		enemyDiedSprite->SetAnimation(0);
		enemyDiedSprite->SetPosition((float)locX, (float)locY);
		currentHP = 0;
		isDied = true;
	}

	//DEBUGGING
	if (App::IsKeyPressed('B'))
	{
		currentHP -= 1;
	}
	
}

void Enemy::Render(GameManager& gameManager)
{

	//App::Print(100, 700, std::to_string(asdda).c_str(), (float)0 / 255, (float)191 / 255, (float)255 / 255, GLUT_BITMAP_HELVETICA_18);

		App::Print(100, 720, std::to_string(1).c_str(), (float)0 / 255, (float)191 / 255, (float)255 / 255, GLUT_BITMAP_HELVETICA_18);

		App::Print(100, 720, std::to_string(5).c_str(), (float)0 / 255, (float)191 / 255, (float)255 / 255, GLUT_BITMAP_HELVETICA_18);
	//App::Print(100, 650, std::to_string(result[0].first).c_str(), (float)0 / 255, (float)191 / 255, (float)255 / 255, GLUT_BITMAP_HELVETICA_18);

	if (gameManager.getUI()->getCurrentScreen() == Screens::GAME || gameManager.getUI()->getCurrentScreen() == Screens::DEAD || gameManager.getUI()->getCurrentScreen() == Screens::PAUSE) {
		if (checkDied()) {
			enemyDiedSprite->Draw();
			if (enemyDiedSprite->GetFrame() == 5) {
				enemyDiedSprite->SetAnimation(-1);
			}
		}
		else {
			enemySprite->Draw();
		}
	}

}

bool Enemy::checkDied()
{
	return isDied;
}

void Enemy::setX(float x)
{
	locX = x;
}

void Enemy::setY(float y)
{
	locY = y;
}

float Enemy::getX()
{
	return locX;
}

float Enemy::getY()
{
	return locY;
}
			
void Enemy::setLocation() {
	enemySprite->SetPosition((float)locX, (float)locY);
}
void Enemy::Reset() {
	speed = 1;
	currentHP = 100;
	isDied = false;
}

int Enemy::getHp() {
	return currentHP;
}

void Enemy::setHP(int hp) {
	currentHP -= hp;
}

void Enemy::moveTo(GameManager& gameManager, float targetX, float targetY)
{
	float distance = Utils::Distance(locX, locY, targetX, targetY);
	// If the enemy is already at the target position, don't move
	if (distance == 0.0f) {
		return;
	}

	if (locX < targetX) {
		enemySprite->SetAnimation(ANIM_RIGHT);
		locX += speed * gameManager.GetDeltaTime() * 0.02f;
	}
	else if (locX > targetX) {
		enemySprite->SetAnimation(ANIM_LEFT);
		locX -= speed * gameManager.GetDeltaTime() * 0.02f;
	}
	if (locY < targetY) {
		enemySprite->SetAnimation(ANIM_FORWARDS);
		locY += speed * gameManager.GetDeltaTime() * 0.02f;
	}
	else if (locY > targetY) {
		//enemySprite->SetAnimation(ANIM_BACKWARDS);
		locY -= speed * gameManager.GetDeltaTime() * 0.02f;
	}
	enemySprite->SetPosition(locX, locY);
}

void Enemy::Movement(GameManager& gameManager, float targetX, float targetY)
{
	float playerDistance = Utils::Distance(locX, locY, targetX, targetY);
	// If the enemy is already at the target position, don't move
	//if (playerDistance == 0.0f) {
	//	return;
	//}

	switch(enemyAI) {
	case RUNAWAY:
			
		while(lastBombPosX)

		break;
	case CHASE:

		break;
	case PATROL:

		break;
	case COLLECT:

		break;

	default:
		break;
	}



	
}







