#pragma once

struct Matrix
{

	Matrix();

	int& operator()(int row, int col);

private:

	int m[768]; // the tilemap is made by 32x24 blocks

};

