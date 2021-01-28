#include <iostream>
#include <string>
#include <fstream>
#include "simpio.h"
#include "random.h"
#include "console.h"
#include "vector.h"
#include <time.h>
#include "lexicon.h"
#include "tree_edges.h"
#include "remove_cycle.h"


using namespace std;

void printTestResults(bool passed, int & testNum, int & passedCounter) {
	testNum++;
	if (passed) {
		passedCounter++;
		cout << "test " << testNum << " passed, total passed tests: " << passedCounter << endl;
	} else {
		cout << "test " << testNum << " failed, total passed tests: " << passedCounter << endl;
	}
}

void clearGrid(Grid<bool> &g, int n) {
	g.resize(n, n);
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			g[i][j] = false;
		}
	}
}

void readGraphFromFile(string fileName, Grid<bool> &g, int &answ) {
	ifstream ifile;
	ifile.open(fileName.c_str());
	int n, m;
	ifile >> n >> m >> answ;
	clearGrid(g, n);
	int from, to;
	for (int i=0; i<m; i++) {
		ifile >> from >> to; 
		g[from][to] = true;
	}
	ifile.close();
}

int generateRandomGraph(Grid<bool> &g, int n) {
	clearGrid(g, n);
	int m = (int)(n*1.2);
	int i = 0;
	Set<string> arcs;
	while (i < m) {
		int from = randomInteger(0, n-1);
		int to = randomInteger(0, n-1);
		string arc1 = integerToString(from) + string(":") + integerToString(to);
		string arc2 = integerToString(to) + string(":") + integerToString(from);
		if (arcs.contains(arc1) || arcs.contains(arc2) || from == to) {
			continue;
		}
		i++;
		arcs.add(arc1);
		g[from][to] = true;
	}
	return m-1;
}

void writeGraphInFile(Grid<bool> &g, int m, int answ, int num) {
	ofstream file;
	string fileName = "cycle\\test" + integerToString(num) + ".txt";
	file.open(fileName.c_str());
	file << g.numCols() << " " << m << " " << answ << endl;
	for (int i=0; i<g.numCols(); i++) {
		for (int j=0; j<g.numCols(); j++) {
			if (g[i][j]) {
				file << i << " " << j << endl;
			}
		}
	}
	file.close();
}

void insertIntoTree(Cell * &root, int v) {
	if (root == NULL) {
		root = new Cell;
		root->left = NULL;
		root->right = NULL;
		root->v = v;
		return;
	}
	if (root->v < v) {
		insertIntoTree(root->right, v);
	} else {
		insertIntoTree(root->left, v);
	}
}

Cell* buildBinaryTree(Vector<int> &v) {
	Cell * root = NULL;
	for (int i=0; i<v.size(); i++) {
		insertIntoTree(root, v[i]);
	}
	return root;
}

Cell* generateRandomBinaryTree() {
	Vector<int> v;
	Set<int> s;
	for (int i=0; i<100; i++) {
		int k = randomInteger(0, 1000);
		if (s.contains(k)) {
			continue;
		}
		s.add(k);
		v.add(k);
	}
	return buildBinaryTree(v);
}

void runTreeEdgeTests() {
	setRandomSeed(0);
	int testNum = 0;
	int passedCounter = 0;
	int left, right;
	bool passed;
	Vector<int> v;
	Cell * root;
	//#1
	v.clear();
	v += 2;
	root = buildBinaryTree(v);
	getTreeEdges(root, left, right);
	passed = left == 2 && right == 2;
	printTestResults(passed, testNum, passedCounter);
	//#2
	v.clear();
	v += 11, 21, 31;
	root = buildBinaryTree(v);
	getTreeEdges(root, left, right);
	passed = left == 11 && right == 31;
	printTestResults(passed, testNum, passedCounter);
	//#3
	v.clear();
	v += 14, 12, 15, 17;
	root = buildBinaryTree(v);
	getTreeEdges(root, left, right);
	passed = left == 12 && right == 17;
	printTestResults(passed, testNum, passedCounter);
	//#4
	v.clear();
	v += 11, 17, 18, 16, 15;
	root = buildBinaryTree(v);
	getTreeEdges(root, left, right);
	passed = left == 15 && right == 18;
	printTestResults(passed, testNum, passedCounter);
	//#5
	v.clear();
	v += 12, 11, 17, 18, 16, 15, 14, 13;
	root = buildBinaryTree(v);
	getTreeEdges(root, left, right);
	passed = left == 13 && right == 18;
	printTestResults(passed, testNum, passedCounter);
	//#6
	v.clear();
	v += 118, 18, 112, 111, 110, 113, 114, 115, 120, 122;
	root = buildBinaryTree(v);
	getTreeEdges(root, left, right);
	passed = left == 110 && right == 115;
	printTestResults(passed, testNum, passedCounter);
	//#7
	v.clear();
	v += 1100, 160, 140, 180, 1120, 1140, 1130, 1129, 1128, 1127, 1126;
	root = buildBinaryTree(v);
	getTreeEdges(root, left, right);
	passed = left == 1126 && right == 1140;
	printTestResults(passed, testNum, passedCounter);
	//#8
	v.clear();
	v += 1100, 1200, 1300, 1400, 190, 180, 170;
	root = buildBinaryTree(v);
	getTreeEdges(root, left, right);
	passed = left == 170 && right == 1400;
	printTestResults(passed, testNum, passedCounter);
	//#9
	v.clear();
	v += 100, 90, 80, 140, 160, 120, 119, 118, 121, 122;
	root = buildBinaryTree(v);
	getTreeEdges(root, left, right);
	passed = left == 80 && right == 122;
	printTestResults(passed, testNum, passedCounter);
	//#10
	v.clear();
	v += 1100, 160, 140, 150, 145, 149, 148, 147, 151, 152;
	root = buildBinaryTree(v);
	getTreeEdges(root, left, right);
	passed = left == 147 && right == 152;
	printTestResults(passed, testNum, passedCounter);


	setRandomSeed(2);
	//ofstream o;
	//o.open("1.txt");
	//int answ[] = {28, 938, 35, 555, 10, 605, 193, 855, 24, 851, 15, 881, 609, 334, 24, 999, 24, 999, 4, 708, 7, 464, 91, 685, 1, 974, 0, 998, 173, 643, 3, 684, 1, 639, 219, 815, 0, 1000, 15, 989};
	int answ[] = {120, 987, 18, 675, 118, 586, 92, 657, 44, 870, 36, 997, 369, 975, 2, 931, 149, 620, 24, 986, 26, 901, 266, 828, 44, 975, 0, 970, 1, 999, 0, 623, 124, 954, 154, 950, 45, 825, 8, 502};
	for (int i=0; i<20; i++) {
		root = generateRandomBinaryTree();
		getTreeEdges(root, left, right);
		passed = left == answ[2*i] && right == answ[2*i+1];
		printTestResults(passed, testNum, passedCounter);
		//o << left << ", " << right << ", ";
	}
	//o.close();

	cout << "###### passed " << passedCounter << " tests ######" << endl;
}

void runRemoveCycleTests() {
	setRandomSeed(0);
	int testNum = 0;
	int passedCounter = 0;	
	int from = 0, to = 0;


	int index = 26;
	for (int i=1; i<=50; i++) {		
		Grid<bool> g;
		int n = 19;
		int answ = 0;
		readGraphFromFile("cycle\\test" + integerToString(i) + ".txt", g, answ);
		//int m = generateRandomGraph(g, n);
		int res = ramoveCycle(g);
		//if (res > 0) {
		//	writeGraphInFile(g, m, res, index);
		//	index++;	
		//}
		printTestResults(res == answ, testNum, passedCounter);
	}

	cout << "###### passed " << passedCounter << " tests ######" << endl;
}

int main() {
	runTreeEdgeTests();
	runRemoveCycleTests();
	return 0;
}