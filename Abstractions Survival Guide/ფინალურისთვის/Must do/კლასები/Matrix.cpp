
#include "Matrix.h"

Matrix::Matrix(int width, int height)
{
	w = width;
	h = height;
	data = new double[w * h];
	for (int i = 0; i < w * h; i++) {
		data[i] = 0;
	}
}

Matrix::~Matrix(void)
{
	delete [] data;
}

double Matrix::getAt(int row, int column) {
	return data[row * w + column];
}

void Matrix::setAt(int row, int column, double value) {
	data[row * w + column] = value;
}

void Matrix::addAt(int row, int column, double value) {
	data[row * w + column] += value;
}

Matrix Matrix::add(Matrix& other) {
	Matrix m(w, h);
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			m.addAt(i, j, other.getAt(i, j));
		}
	}
	return m;
}

Matrix Matrix::times(Matrix& other) {
	Matrix m(other.w, h);
	for (int i = 0; i < other.w; i++) {
		for (int j = 0; j < h; j++) {
			for (int k = 0; k < other.w; k++) {
				m.addAt(i, j, getAt(i, j) * other.getAt(i, j));
			}
		}
	}
	return m;
}
