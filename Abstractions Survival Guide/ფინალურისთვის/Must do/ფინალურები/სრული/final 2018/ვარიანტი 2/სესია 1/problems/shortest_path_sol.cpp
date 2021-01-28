#include "shortest_path_sol.h"
#include "queue.h"
#include "set.h"
#include "grid.h"

int bfs(Grid<int> &table, int sign) {
	Queue<int> points;
	Set<int> visited;
	points.enqueue(0);
	Grid<int> path(table.numRows(), table.numCols());
	for (int i=0; i<path.numRows(); i++) {
		for (int j=0; j<path.numCols(); j++) {
			path[i][j] = 10000;
		}
	}
	path[0][0] = 0;

	while (!points.isEmpty()) {
		int p = points.dequeue();
		if (p == table.numCols()*table.numRows()-1) {
			return path[table.numRows()-1][table.numCols()-1];
		}

		if (visited.contains(p)) {
			continue;
		}
		visited.add(p);
		int row = p / table.numCols();
		int col = p -  row * table.numCols();
		if (table.inBounds(row+1, col) && 
			table[row][col]*sign < table[row+1][col]*sign &&
			path[row][col] + 1 < path[row+1][col]) {
			
			path[row+1][col] = path[row][col] + 1;
			points.enqueue(p+table.numCols());		
		}

		if (table.inBounds(row, col-1) && 
			table[row][col]*sign < table[row][col-1]*sign &&
			path[row][col] + 1 < path[row][col-1]) {
			
			path[row][col-1] = path[row][col] + 1;
			points.enqueue(p-1);		
		}
		
		if (table.inBounds(row, col+1) && 
			table[row][col]*sign < table[row][col+1]*sign &&
			path[row][col] + 1 < path[row][col+1]) {
			
			path[row][col+1] = path[row][col] + 1;
			points.enqueue(p+1);		
		}
	}
	return -1;
}

int getShortestPathSol(Grid<int> &table) {
	int v1 = bfs(table, 1);
	int v2 = bfs(table, -1);

	if (v1 == -1) {
		return v2;
	}
	if (v2 == -1) {
		return v1;
	}

	if (v1 < v2) {
		return v1;
	} else if (v2 < v1) {
		return v2;
	}

	return -1;
}