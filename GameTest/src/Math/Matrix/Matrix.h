#pragma once
#include <vector>

struct Matrix
{

	Matrix();

	int& operator()(int row, int col);
	std::vector<int>& matrixFullList();

private:

	int m[768]; // the tilemap is made by 32x24 blocks

};

