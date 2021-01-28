//#pragma once

#ifndef Matrix_H_
#define Matrix_H_

class Matrix
{
private:
	int w, h;
	double* data;

public:
	Matrix(int width, int height);
	~Matrix(void);
	double getAt(int row, int colomn);
	void setAt(int row, int column, double value);
	void addAt(int row, int column, double value);
	Matrix add(Matrix& other);
	Matrix times(Matrix& other);
	void copy(Matrix& other);
};

#endif