#include <stdafx.h>
#include "HPBar.h"
#include "App\app.h"
#include <string>

HPBar::HPBar() : currentHP(100), percent(1.0f), x(0.0f), y(0.0f), dx(0.0f), dy(0.0f), bgColor(Colors::White), innerColor(Colors::White), hpLoseColor(Colors::White)
{
}

void HPBar::Update(int HP)
{
	this->currentHP = HP;
}

float getPercentageHP(int currentHP) {
	return (float)currentHP / 100;
}

float HPBar::rightAlign(int HP) {
	float moveRight = 10.0f;
	while (HP > 0) {
		HP /= 10;
		moveRight += 5.0f;
	}
	return moveRight;
}

void HPBar::CreateHPBar(float x, float y, float dx, float dy,float Y, Colors bgColor, Colors innerColor, Colors hpLoseColor)
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

	//inner, green
	dx = x + (float)currentHP / 100 * 0.99f + 2 * interval;
	glBegin(GL_QUADS);
	col.SetColor(innerColor);
	col.r = (int)(255 - (float)currentHP / 100 * 255);
	col.g = (int)((float)currentHP / 100 * 255);
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
	App::Print(560 - rightAlign(currentHP), Y, std::to_string(currentHP).c_str(), (float)255 / 255, (float)0 / 255, (float)0 / 255, GLUT_BITMAP_HELVETICA_18);
	App::Print(570, Y, "/", (float)255 / 255, (float)0 / 255, (float)0 / 255, GLUT_BITMAP_HELVETICA_18);
	App::Print(580, Y, "100", (float)255 / 255, (float)0 / 255, (float)0 / 255, GLUT_BITMAP_HELVETICA_18);
}
