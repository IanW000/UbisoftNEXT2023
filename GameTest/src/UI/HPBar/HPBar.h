#pragma once
#include <Render/Color.h>
#include <Object/Player/Player.h>

struct HPBar {
public:

	HPBar();
	float rightAlign(int HP);
	void CreateHPBar(float x, float y, float dx, float dy, Colors bgColor, Colors innerColor, Colors hpLoseColor);

	void Init();
	void Update(float deltaTime, Player player);
	void Render();

private:
	const float interval = 0.005f;
	int currentHP;
	float percent;
	float x, y, dx, dy;
	Colors bgColor, innerColor, hpLoseColor;
};

