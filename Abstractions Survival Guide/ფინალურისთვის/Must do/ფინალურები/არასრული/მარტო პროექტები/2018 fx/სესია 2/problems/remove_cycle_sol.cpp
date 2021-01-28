#include "remove_cycle.h"
#include "stack.h"
#include "set.h"

bool hasCycle(Grid<bool> &g) {
	for (int i=0; i<g.numCols(); i++) {
		Stack<int> s;
		Set<int> visited;
		s.push(i);
		while (!s.isEmpty()) {
			int k = s.pop();
			if (visited.contains(k)) {
				if (k == i) {
					return true;
				}
				continue;
			}
			visited.add(k);
			for (int j=0; j<g.numCols(); j++) {
				if (g[k][j]) {
					s.push(j);
				}
			}
		}
	}
	return false;
}

int ramoveCycle(Grid<bool> &g) {
	if (!hasCycle(g)) {
		cout << "no cycle!" << endl;
		return -1;
	}
	for (int i=0; i<g.numCols(); i++) {
		for (int j=0; j<g.numCols(); j++) {
			if (g[i][j]) {
				g[i][j] = false;
				if (!hasCycle(g)) {
					g[i][j] = true;
					return i + j;
				}
				g[i][j] = true;
			}
		}
	}
	return -1;
}
