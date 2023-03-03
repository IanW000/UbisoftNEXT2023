#include "stdafx.h"
#include "App\app.h"
#include "Button.h"
#include <GameManager/GameManager.h>


Button::Button() : x(0), y(0), dx(0), dy(0), textX(0), textY(0), text("INIT"), buttonColor(Colors::Pink), buttonType(ButtonType::START), hovering(false), clicked(false), hoverPlayedOnce(false), clickedPlayedOnce(false), gameScreen(false), controlsScreen(false), backToMainScreen(false), pause(false), resume(false)
{
}

void Button::CreateButton(float x, float y, float dx, float dy, float textX, float textY, const char* text, Colors buttonColor, ButtonType buttonType)
{
	this->x = x;
	this->y = y;
	this->dx = dx;
	this->dy = dy;
	this->textX = textX;
	this->textY = textY;
	this->text = text;
	this->buttonColor = buttonColor;
	this->buttonType = buttonType;

	Color col;


	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glBegin(GL_QUADS);
	col.SetColor(Colors::White);
	glColor3ub(col.r, col.g, col.b);
	glVertex2f(x - interval, y - interval);
	glVertex2f(x - interval, dy + interval);
	glVertex2f(dx + interval, dy + interval);
	glVertex2f(dx + interval, y - interval);
	glEnd();

	//draw buttons
	glBegin(GL_QUADS);
	col.SetColor(buttonColor);
	glColor3ub(col.r, col.g, col.b);
	glVertex2f(x, y);
	glVertex2f(x, dy);
	glVertex2f(dx, dy);
	glVertex2f(dx, y);
	glEnd();


	//button text
	App::Print(textX, textY, text, (float)0 / 255, (float)191 / 255, (float)255 / 255, GLUT_BITMAP_HELVETICA_18);

}

void Button::Update(float deltaTime)
{
	if (GameManager::getMousePosition().x > x && GameManager::getMousePosition().y < -y && GameManager::getMousePosition().x < dx && GameManager::getMousePosition().y > -dy) {
		hovering = true;
		if (App::IsKeyPressed(VK_LBUTTON)) {
			clicked = true;
			switch (buttonType) {

			case ButtonType::START:
				gameScreen = true;
				break;

			case ButtonType::CONTROLS:
				controlsScreen = true;
				break;

			case ButtonType::EXIT:
				exit(0);
				break;

			case ButtonType::BACK:
				backToMainScreen = true;
				break;

			case ButtonType::PAUSE:
				pause = true;
				break;

			case ButtonType::RESUME:
				resume = true;
				break;
			}
		}
	}
	else {
		hovering = false;
		hoverPlayedOnce = false;
		clickedPlayedOnce = false;
		clicked = false;
	}
}

void Button::Render()
{
	if (!hovering) {
		CreateButton(x, y, dx, dy, textX, textY, text, buttonColor, buttonType);
	}
	else {

		if (!hoverPlayedOnce) {
			App::PlaySound(".\\res\\Sound\\hover.wav");
			hoverPlayedOnce = true;
		}

		if (!clicked) {
			CreateButton(x - 0.01f, y - 0.01f, dx + 0.01f, dy + 0.01f, textX, textY, text, Colors::DarkPink, buttonType);
		}

		if (clicked && !clickedPlayedOnce) {
			CreateButton(x, y, dx, dy, textX, textY, text, buttonColor, buttonType);
			App::PlaySound(".\\res\\Sound\\click.wav");
			clickedPlayedOnce = true;
		}
	}
}
