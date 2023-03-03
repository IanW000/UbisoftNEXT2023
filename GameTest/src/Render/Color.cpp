#include "stdafx.h"
#include "Color.h"
#include <Math/Utils.h>

Color::Color() : r(255), g(255), b(255) {

}

void Color::SetColor(Colors color) {

	switch (color) {

	case Colors::White:
		r = 255;
		g = 255;
		b = 255;
		break;

	case Colors::Blue:
		r = 0;
		g = 0;
		b = 255;
		break;

	case Colors::SkyBlue:
		r = 135;
		g = 206;
		b = 235;
		break;

	case Colors::DarkPink:
		r = 255;
		g = 100;
		b = 167;
		break;

	case Colors::Pink:
		r = 246;
		g = 120;
		b = 167;
		break;

	case Colors::Red:
		r = 255;
		g = 0;
		b = 0;

	case Colors::Yellow:
		r = 255;
		g = 255;
		b = 0;
		break;

	case Colors::Green:
		r = 0;
		g = 255;
		b = 0;
		break;

	case Colors::Black:
		r = 0;
		g = 0;
		b = 0;
		break;

	case Colors::Random:
		r = Utils::RandomInt(0, 255);
		g = Utils::RandomInt(0, 255);
		b = Utils::RandomInt(0, 255);
		break;
	}
}
float Color::ConvertToFloat(int Integer) {
	return (float)Integer / 255;
}
int Color::ConvertToInt(float Float) {
	return (int)Float * 255;
}