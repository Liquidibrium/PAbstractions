
#ifndef MY_GRID_H_
#define MY_GRID_H_

#define START_WIDTH_SIZE 5
#define START_HEIGHT_SIZE 5

class MyGrid {

	public:

		MyGrid();
		~MyGrid();

		double getAt(int row, int col);
		void setAt(int row, int col, double val);
		void addAt(int row, int col, double val);

	private:

		int alocWidthSize;
		int alocHeightSize;

		double* data;

		void checkAlocSize(int row, int col);

};

#endif
