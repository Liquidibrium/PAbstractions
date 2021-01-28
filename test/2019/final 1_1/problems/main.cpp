#include <iostream>
#include <string>
#include <fstream>
#include "simpio.h"
#include "random.h"
#include "console.h"
#include "foreach.h"
#include <time.h>
#include "lexicon.h"
#include "Vector.h"
#include "Set.h"
#include "Map.h"
#include "leftview.h"
#include "cyclemin.h"


using namespace std;

void printTestResults(bool passed, int & testNum, int & passedCounter) {
	testNum++;
	if (passed) {
		cout << "test " << testNum << " passed" << endl;
		passedCounter++;
	} else {
		cout << "test " << testNum << " failed" << endl;
	}
}

void clearWeights(nodeT * root) {
	if (root == NULL) {
		return;
	}
	root->weight = 0;
	clearWeights(root->left);
	clearWeights(root->right);
}

nodeT* insertNode(nodeT * &root, int value, int weight) {
	if (root == NULL) {
		root = new nodeT;
		root->v = value;
		root->weight = weight;
		root->left = NULL;
		root->right = NULL;
		return root;
	}

	if (root->weight < weight) {
		return insertNode(root->right, value, weight);
	} else {
		return insertNode(root->left, value, weight);
	}
}

void readBinaryTree(nodeT * &r, ifstream &input, Vector<nodeT *> &answ) {
	int n;
	input >> n;
	int w, v;
	for (int i=0; i<n; i++) {
		input >> v >> w;
		nodeT * node = insertNode(r, v, w);
		if (w % 10 == 1) {
			answ.add(node);
		}
	}
}

void readTreeTest(nodeT * &root, Vector<nodeT *> &answ, int testNum) {
	string testFileName = string("leftview\\test") + integerToString(testNum) + ".txt";
	root = NULL;
	ifstream input;
	input.open(testFileName.c_str());
	readBinaryTree(root, input, answ);
	clearWeights(root);
	input.close();
}

bool isEqualVector(Vector<nodeT *> v1, Vector<nodeT *> v2) {
	if (v1.size() != v2.size()) {
		return false;
	}
	for (int i=0; i<v1.size(); i++) {
		if (v1[i] != v2[i])
			return false;
	}
	return true;
}

void testLeftView() {
	cout << "### Testing Tree left view ###" << endl;
	int testNum = 0;
	int passed = 0;

	nodeT * root;
	Vector<nodeT *> res;
	Vector<nodeT *> answ;
	for (int i=1; i<=10; i++) {
		answ.clear();
		readTreeTest(root, answ, i);
		res = leftView(root);
		bool isCorrect = isEqualVector(res, answ);
		printTestResults(isCorrect, testNum, passed);
	}

	cout << "passed: " << passed << endl;
}

void readGraph(Vector<edgeT *> &g, ifstream &input, int &answ) {
	int n;
	input >> n >> answ;
	for (int i=0; i<n; i++) {
		int from, to, weight;
		input >> from >> to >> weight;
		edgeT * e = new edgeT;
		e->from = from;
		e->to = to;
		e->weight = weight;
		g.add(e);
	}
}

void readGraphTest(Vector<edgeT *> &g, int &answ, int testNum) {
	string testFileName = string("cycle\\test") + integerToString(testNum) + ".txt";
	ifstream input;
	input.open(testFileName.c_str());
	readGraph(g, input, answ);
	input.close();
}



void testCycle() {
	cout << "### Testing Cycle ###" << endl;
	int testNum = 0;
	int passed = 0;
	int answ;
	Vector<edgeT *> g;
	for (int i=1; i<=10; i++) {
		g.clear();
		readGraphTest(g, answ, i);
		int res = removeCycleMin(g);
		bool isCorrect = res == answ;
		printTestResults(isCorrect, testNum, passed);
	}
	cout << "passed: " << passed << endl;	
}

int main() {
	setRandomSeed(0);
	testLeftView();
	testCycle();
	return 0;
}