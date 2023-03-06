#pragma once
#include <UI/Color.h>
#include <Object/Player/Player.h>

struct HPBar {
public:

	HPBar();

	void Update(int HP);

	float rightAlign(int HP);
	void CreateHPBar(float x, float y, float dx, float dy, float Y, Colors bgColor, Colors innerColor, Colors hpLoseColor);

private:
	const float interval = 0.005f;
	int currentHP;
	float percent;
	float x, y, dx, dy;
	Colors bgColor, innerColor, hpLoseColor;
};

