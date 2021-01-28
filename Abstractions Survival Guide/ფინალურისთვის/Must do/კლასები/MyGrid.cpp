#include "MyGrid.h"
#include <iostream>
using namespace std;

MyGrid::MyGrid() {
	alocWidthSize = START_WIDTH_SIZE;
	alocHeightSize = START_HEIGHT_SIZE;
	int size = alocWidthSize * alocHeightSize;
	data = new double[size];
	for (int i = 0; i < size; i++)
		data[i] = 0;
}

MyGrid::~MyGrid() {
	delete[] data;
}

double MyGrid::getAt(int row, int col) {
	checkAlocSize(row, col);
	return data[row * alocWidthSize + col];
}

void MyGrid::setAt(int row, int col, double val) {
	checkAlocSize(row, col);
	data[row * alocWidthSize + col] = val;
}

void MyGrid::addAt(int row, int col, double val) {
	checkAlocSize(row, col);
	data[row * alocWidthSize + col] += val;
}

void MyGrid::checkAlocSize(int row, int col) {
	if (row < alocHeightSize && col < alocWidthSize) return;
	double* tmp = data;
	if (row >= alocHeightSize && col < alocWidthSize) {
		int new_size = alocWidthSize * (row + 1);
		data = new double[new_size];
		for (int i = 0; i <= row; i++) {
			for (int j = 0; j < alocWidthSize; j++) {
				int coordinate = i * alocWidthSize + j;
				if (i < alocHeightSize)
					data[coordinate] = tmp[coordinate];
				else
					data[coordinate] = 0;
			}
		}
		alocHeightSize = row + 1;
	}
	else if (row < alocHeightSize && col >= alocWidthSize) {
		int new_size = (col + 1) * alocHeightSize;
		data = new double[new_size];
		for (int i = 0; i < alocHeightSize; i++) {
			for (int j = 0; j <= col; j++) {
				int coordinate = i * (col + 1) + j;
				if (j < alocWidthSize)
					data[coordinate] = tmp[coordinate];
				else
					data[coordinate] = 0;
			}
		}
		alocWidthSize = col + 1;
	}
	else {
		int new_size = (col + 1) * (row + 1);
		data = new double[new_size];
		for (int i = 0; i <= row; i++) {
			for (int j = 0; j <= col; j++) {
				int coordinate = i * (col + 1) + j;
				if (i < alocHeightSize && j < alocWidthSize)
					data[coordinate] = tmp[coordinate];
				else
					data[coordinate] = 0;
			}
		}
		alocWidthSize = col + 1;
		alocHeightSize = row + 1;
	}
	delete[] tmp;
}
