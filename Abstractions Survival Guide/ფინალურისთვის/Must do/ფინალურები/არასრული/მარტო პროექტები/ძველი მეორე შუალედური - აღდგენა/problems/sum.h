#include "common.h"
#include <cstdio>

using namespace std;

struct Cell {
	int d;
	Cell * next;
};

Cell * sum(Cell * l1, Cell * l2);
