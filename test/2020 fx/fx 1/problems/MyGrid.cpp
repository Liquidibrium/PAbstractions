#include "MyGrid.h"


MyGrid::MyGrid(int numRows, int numCols) {
	this->numRows = numRows;
	this->numCols = numCols;
	grid = NULL;
	for (int i=0; i<numRows; i++) {
		Cell * row = NULL;
		for (int j=0; j<numCols; j++) {
			Cell * newCell = new Cell;
			newCell->v = 0;
			newCell->down = NULL;
			newCell->right = row;
			row = newCell;
		}
		row->down = grid;
		grid = row;
	}
}

int MyGrid::NumRows() {
	return numRows;
}

int MyGrid::NumColumns() {
	return numCols;
}

void MyGrid::SetValue(int i, int j, int value) {
	Cell * curr = grid;
	while (i > 0) {
		curr = curr->down;
		i--;
	}
	while (j > 0) {
		curr = curr->right;
		j--;
	}
	curr->v = value;
}

int MyGrid::GetValue(int i, int j) {
	Cell * curr = grid;
	while (i > 0) {
		curr = curr->down;
		i--;
	}
	while (j > 0) {
		curr = curr->right;
		j--;
	}
	return curr->v;
}

void MyGrid::RemoveRow(int indx) {
	numRows--;
	if (numRows == 0) {
		grid = NULL;
		numCols = 0;
		return;
	}
	if (indx == 0) {
		grid = grid->down;
		return;
	}

	Cell * row = grid;
	while (indx > 1) {
		row = row->down;
		indx--;
	}
	row->down = row->down->down;
}

void MyGrid::RemoveColumn(int indx) {
	numCols--;
	if (numCols == 0) {
		grid = NULL;
		numRows = 0;
		return;
	}
	if (indx == 0) {
		Cell * savedGrid = grid->down;
		grid = grid->right;

		Cell * row = grid;
		for (int i=0; i<numRows-1; i++) {
			row->down = savedGrid->right;
			savedGrid = savedGrid->down;
			row = row->down;
		}
		return;
	}

	Cell * row = grid;
	for (int i=0; i<numRows; i++) {
		Cell * cell = row;
		while (indx > 1) {
			cell = cell->right;
			indx--;
		}
		cell->right = cell->right->right;
		row = row->down;
	}
}

void MyGrid::InsertRow(int indx) {
	numRows++;

	Cell * row = NULL;
	for (int i=0; i<numCols; i++) {
		Cell * newCell = new Cell;
		newCell->v = 0;
		newCell->down = NULL;
		newCell->right = row;
		row = newCell;
	}

	if (indx == 0) {
		row->down = grid;
		grid = row;
		return;
	}
	Cell * curr = grid;
	while (indx > 1) {
		curr = curr->down;
		indx--;
	}
	row->down = curr->down;
	curr->down = row;
}

void MyGrid::InsertColumn(int indx) {
	numCols++;
	if (indx == 0) {
		Cell * col = NULL;
		for (int i=0; i<numRows; i++) {
			Cell * newCell = new Cell;
			newCell->v = 0;
			newCell->down = col;
			newCell->right = NULL;
			col = newCell;
		}
		
		Cell * curr = col;
		for (int i=0; i<numRows; i++) {
			curr->right = grid;
			curr = curr->down;
			grid = grid->down;	
		}
		grid = col;
		return;
	}

	Cell * row = grid;	
	for (int i=0; i<numRows; i++) {
		Cell * col = row;
		for (int i=0; i<indx-1; i++) {
			col = col->right;
		}
		Cell * newCell = new Cell;
		newCell->v = 0;
		newCell->down = NULL;
		newCell->right = col->right;
		col->right = newCell;
		row = row->down;
	}
}

