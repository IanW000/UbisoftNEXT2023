#pragma once
#include <Graphics/Color.h>
#ifndef _BUTTON_H
#define _BUTTON_H

enum class ButtonType {
	START,
	CONTROLS,
	EXIT,
	BACK,
	PAUSE,
	RESUME
};

struct Button {
public:
	Button();
	void CreateButton(float x, float y, float dx, float dy, float textX, float textY, const char* text, Colors buttonColor, ButtonType buttonType);
	void Update(float deltaTime);
	void Render();

	bool gameScreen;
	bool controlsScreen;
	bool backToMainScreen;
	bool pause;
	bool resume;

private:
	float x, y, dx, dy, textX, textY;
	const char* text;
	Colors buttonColor;
	ButtonType buttonType;
	const float interval = 0.005f;
	//bool activated;
	bool hovering;
	bool clicked;
	bool hoverPlayedOnce;
	bool clickedPlayedOnce;
};
#endif
