
#include <iostream>
#include "set.h"
#include "map.h"
#include "stack.h"
#include "queue.h"
#include "grid.h"
using namespace std;

struct Node {
	int value;
	Node* left;
	Node* right;
};

void recDFS(int cur, Grid<bool>& g, Set<int>& been) {
	if (been.contains(cur)) return;
	cout << cur << endl;
	been.add(cur);
	for (int i=0; i<g.numCols(); i++)
		if (g[cur][i]) recDFS(i,g,been);
}

void DFS(Grid<bool>& g) {
	Set<int> been;
	recDFS(0, g, been);
}

void BFS(Grid<bool>& g) {
	Queue<int> q;
	Set<int> been;
	q.enqueue(0);
	been.add(0);
	while (!q.isEmpty()) {
		int tmp = q.dequeue();
		cout << tmp << endl;
		for (int i=0; i<g.numCols(); i++) {
			if (g[tmp][i] && !been.contains(i)) {
				q.enqueue(i);
				been.add(i);
			}
		}
	}
}

/* !!! */
int hopCount(Grid<bool>& g, int start, int finish) {
	Queue<int> q;
	Set<int> been;
	q.enqueue(start);
	been.add(start);
	int res = 0;
	while (!q.isEmpty()) {
		Queue<int> next_q;
		while (!q.isEmpty()) {
			int tmp = q.dequeue();
			if (tmp == finish) return res;
			for (int i=0; i<g.numCols(); i++) {
				if (g[tmp][i]) {
					next_q.enqueue(i);
					been.add(i);
				}
			}
		}
		q = next_q;
		res++;
	}
	return -1;
}

bool isCycle(Grid<bool>& g, int cur, int parent, Set<int>& been) {
	been.add(cur);
	for (int i=0; i<g.numCols(); i++) {
		if (g[cur][i]) {
			if (i!=parent) {
				if (been.contains(i)) return true;
				if (isCycle(g, i, cur, been)) return true;
			}
		}
	}
	return false;
}

bool isTree(Grid<bool>& g) {
	Set<int> been;
	if (isCycle(g, 0, -1, been))
		return false;
	return been.size() == g.numCols();
}

bool canBeColoredWith(int color, int cur, Grid<bool>& g, Vector<int>& colors) {
	for (int i=0; i<g.numCols(); i++) {
		if (g[cur][i]) {
			if (colors[i]==color) return false;
		}
	}
	return true;
}

bool recCanBeColoredWithNColor(int cur, int n, Grid<bool>& g, Vector<int>& colors, Set<int>& been) {
	if (cur==g.numCols()) return true;
	for (int i=0; i<n; i++) {
		if (canBeColoredWith(i,cur,g,colors)) {
			colors[cur] = i;
			been.add(cur);
			if (recCanBeColoredWithNColor(cur+1,n,g,colors,been)) return true;
			been.remove(cur);
			colors[cur] = -1;
		}
	}
	return false;
}

/* !!!!!! BMULISTVISAA ES */
// been-shi yris startis shesabamisi bmuli komponentis wveroebs.
bool canBeColoredWithNColor(int start, int n, Grid<bool>& g, Set<int>& been) {
	Vector<int> colors(g.numCols());
	for (int i=0; i<g.numCols(); i++) colors[i] = -1;
	return recCanBeColoredWithNColor(0,n,g,colors,been);
}

bool isBipartite(Grid<bool>& g) {
	Set<int> been;
	for (int i=0; i<g.numCols(); i++) {
		if (!been.contains(i)) {
			if (!canBeColoredWithNColor(i,2,g,been)) {
				return false;
			}
		}
	}
	return true;
}

bool isUndirected(Grid<bool>& g) {
	for (int i=0; i<g.numCols(); i++)
		for (int j=i; j<g.numRows(); j++)
			if (g[i][j] && !g[j][i]) return false;
	return true;
}

bool isPath(int start, int finish, Grid<bool>& g) {
	Queue<int> q;
	Set<int> been;
	q.enqueue(start);
	been.add(start);
	while (!q.isEmpty()) {
		int tmp = q.dequeue();
		if (tmp == finish) return true;
		for (int i=0; i<g.numCols(); i++) {
			if (g[tmp][i] && !been.contains(i)) {
				q.enqueue(i);
				been.add(i);
			}
		}
	}
	return false;
}

int numOfComponents(Grid<bool>& g) {
	int res = 0;
	Set<int> been;
	for (int i=0; i<g.numRows(); i++) {
		if (!been.contains(i)) {
			been.add(i);
			for (int j=i; j<g.numCols(); j++)
				if (isPath(i,j,g)) been.add(j);
			res++;
		}
	}
	return res;
}

// aramimartuli
bool isCompleteGraph(Grid<bool>& g) {
	for (int i=0; i<g.numRows(); i++)
		for (int j=i+1; j<g.numCols(); j++)
			if (!g[i][j]) return false;
	return true;
}

/* !!! */
bool isBmuli(Grid<bool>& g) {
	Queue<int> q;
	Set<int> b;
	q.enqueue(0);
	b.add(0);
	while (!q.isEmpty()) {
		int tmp = q.dequeue();
		for (int i=0; i<g.numCols(); i++) {
			if (g[tmp][i] && !b.contains(i)) {
				q.enqueue(i);
				b.add(i);
			}
		}
	}
	return b.size()==g.numRows();
}

int findDegreeOf(int node, Grid<bool>& g) {
	int res = 0;
	for (int i=0; i<g.numCols(); i++)
		if (g[node][i]) res++;
	return res;
}

// aramimartuli
bool isLineGraph(Grid<bool>& g) {
	if (!isBmuli(g)) return false;
	if (g.numCols()==1) return true; // shari rom ar momdon
	int numOfOneDegreeNodes = 0;
	for (int i=0; i<g.numRows(); i++) {
		int degree = findDegreeOf(i,g);
		if (degree>2) return false;
		if (degree==1) {
			if (numOfOneDegreeNodes==2)
				return false;
			numOfOneDegreeNodes++;
		}
	}
	return true;
}

bool recIsBST(node* root, int min, int max) {
	if (root == NULL) return true;
	if (root->value <= min) return false;
	if (root->value >= max) return false;
	int maxForLeft = root->value > max ? root->value : max;
	if (!recIsBST(root->left, min, maxForLeft)) return false;
	int minForRight = root->value < min ? root->value : min;
	return recIsBST(root->right, minForRight, max);
}

bool isBST(node* root) {
	return recIsBST(root, INT_MIN, INT_MAX);
}

int numOfElements(node* root) {
	if (root == NULL) return 0;
	return numOfElements(root->left)+numOfElements(root->right)+1;
}

int largestBST(node* root) {
	if (isBST(root)) return numOfElements(root);
	int left = largestBST(root->left);
	int right = largestBST(root->right);
	return left>right ? left:right;
}

int main()
{
	/* Bipartite Graph */
	Grid<bool> g(10,10);
	g[2][1]=true;
	g[1][2]=true;

	g[2][3]=true;
	g[3][2]=true;

	g[2][5]=true;
	g[5][2]=true;

	g[4][7]=true;
	g[7][4]=true;

	g[6][7]=true;
	g[7][6]=true;

	g[6][9]=true;
	g[9][6]=true;

	g[8][7]=true;
	g[7][8]=true;

	g[8][9]=true;
	g[9][8]=true;

	/* Line Graph */
	Grid<bool> g1(5,5);
	g1[0][1]=true;
	g1[1][0]=true;

	g1[1][2]=true;
	g1[2][1]=true;

	g1[2][3]=true;
	g1[3][2]=true;

	g1[3][4]=true;
	g1[4][3]=true;

    return 0;
}