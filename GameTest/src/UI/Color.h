#pragma once

enum class Colors {
	White,
	Blue,
	SkyBlue,
	Pink,
	DarkPink,
	Red,
	Yellow,
	Black,
	Green,
	Random
};

struct Color {
	int r, g, b;

	Color();
	void SetColor(Colors color);
	float ConvertToFloat(int Integer);
	int ConvertToInt(float Float);
};
