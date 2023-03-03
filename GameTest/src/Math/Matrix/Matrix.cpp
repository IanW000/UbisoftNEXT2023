#include "stdafx.h"
#include "Matrix.h"

Matrix::Matrix() : m{0}
{
}

int &Matrix::operator()(int row, int col) {
	return m[row + 24 * col];
}