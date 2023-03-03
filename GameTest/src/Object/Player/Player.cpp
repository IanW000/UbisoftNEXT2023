#include "stdafx.h"
#include "Player.h"
#include <App/app.h>

Player::Player() : currentHP(100), died(false)
{
}

void Player::Reset()
{
	currentHP = 100;
	died = false;
}

void Player::Update(float deltaTime)
{
	if (App::IsKeyPressed('M'))
	{
		currentHP -= 1;
	}

	if (App::IsKeyPressed('N'))
	{
		Reset();
	}

	if (resetOnce) {
		Reset();
		resetOnce = false;
	}

	if (currentHP <= 0) {
		currentHP = 0;
		died = true;
	}
}

void Player::Render()
{
}