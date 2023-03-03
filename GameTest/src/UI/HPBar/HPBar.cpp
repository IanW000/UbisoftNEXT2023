#include <stdafx.h>
#include "HPBar.h"
#include "App\app.h"
#include <string>

HPBar::HPBar() : currentHP(100), percent(1.0f), x(0.0f), y(0.0f), dx(0.0f), dy(0.0f), bgColor(Colors::White), innerColor(Colors::White), hpLoseColor(Colors::White)
{
}

float testApproach(float flGoal, float flCurrent, float dt) {
	float flDifference = flGoal - flCurrent;

	if (flDifference > dt)
		return flCurrent + dt;
	if (flDifference < -dt)
		return flCurrent - dt;

	return flGoal;
}


float HPBar::rightAlign(int HP) {
	float moveRight = -5.0f;
	while (HP > 0) {
		HP /= 10;
		moveRight += 10.0f;
	}
	return moveRight;
}

void HPBar::CreateHPBar(float x, float y, float dx, float dy, Colors bgColor, Colors innerColor, Colors hpLoseColor)
{

	this->x = x;
	this->y = y;
	this->dx = dx;
	this->dy = dy;
	this->bgColor = bgColor;
	this->innerColor = innerColor;
	this->hpLoseColor = hpLoseColor;

	Color col;

	//background, white
	glBegin(GL_QUADS);
	col.SetColor(bgColor);
	glColor3ub(col.r, col.g, col.b);
	glVertex2f(x, y);
	glVertex2f(x, dy);
	glVertex2f(dx, dy);
	glVertex2f(dx, y);
	glEnd();

	//inner, pink
	dx = x + (float)currentHP / 100 * 0.99f + 2 * interval;
	glBegin(GL_QUADS);
	col.SetColor(innerColor);
	col.r = 255 - currentHP / 100 * 255;
	col.g = currentHP / 100 * 255;
	glColor3ub(col.r, col.g, col.b);
	glVertex2f(x + interval, y + interval);
	glVertex2f(x + interval, dy - interval);
	glVertex2f(dx - interval, dy - interval);
	glVertex2f(dx - interval, y + interval);
	glEnd();

	//lose hp, yellow
	glBegin(GL_QUADS);
	col.SetColor(hpLoseColor);
	glColor3ub(col.r, col.g, col.b);
	glVertex2f(dx - interval, y + interval);
	glVertex2f(dx - interval, dy - interval);
	glVertex2f(this->dx - interval, dy - interval);
	glVertex2f(this->dx - interval, y + interval);
	glEnd();

	//HP Text
	App::Print(590 - rightAlign(currentHP), 705, std::to_string(currentHP).c_str(), (float)255 / 255, (float)0 / 255, (float)0 / 255, GLUT_BITMAP_HELVETICA_18);
	App::Print(600, 705, "/", (float)255 / 255, (float)0 / 255, (float)0 / 255, GLUT_BITMAP_HELVETICA_18);
	App::Print(610, 705, "100", (float)255 / 255, (float)0 / 255, (float)0 / 255, GLUT_BITMAP_HELVETICA_18);
}


void HPBar::Init()
{

}

void HPBar::Update(float deltaTime, Player player)
{
	this->currentHP = player.currentHP;
}

float getPercentageHP(int currentHP) {
	return (float)currentHP / 100;
}

void HPBar::Render()
{
	//CreateHPBar(x, y, dx, dy, bgColor,innerColor);
}
