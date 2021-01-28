#include <iostream>
#include <string>
#include <fstream>
#include "simpio.h"
#include "random.h"
#include "console.h"
#include "vector.h"
#include "foreach.h"
#include <time.h>
#include "lexicon.h"
#include "Set.h"
#include "Map.h"
#include "sumLevel.h"
#include "linkedSet.h"
#include "strlib.h"



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

void readBinaryTree(nodeT * &r, ifstream &input, int &lvl, int &answ) {
	int n;
	input >> n >> lvl >> answ;
	int w, v;
	for (int i=0; i<n; i++) {
		input >> v >> w;
		nodeT * node = insertNode(r, v, w);
	}
}

void readTreeTest(nodeT * &root, int &lvl, int &answ, int testNum) {
	string testFileName = string("sumlevel\\test") + integerToString(testNum) + ".txt";
	root = NULL;
	ifstream input;
	input.open(testFileName.c_str());
	readBinaryTree(root, input, lvl, answ);
	clearWeights(root);
	input.close();
}


void testSumLevel() {
	cout << "### Testing Subtree ###" << endl;
	int testNum = 0;
	int passed = 0;

	nodeT * root;
	int res;
	int answ, lvl;
	for (int i=1; i<=10; i++) {
		readTreeTest(root, lvl, answ, i);
		res = sumLevel(root, lvl);
		bool isCorrect = res == answ;
		printTestResults(isCorrect, testNum, passed);
	}

	cout << "passed: " << passed << endl;
}

bool testAddContains(int size) {
	LinkedSet s1;
	Set<int> s2;
	
	for (int i=0; i<size; i++) {
		int v = randomInteger(0, 2*size);
		s1.add(v);
		s2.add(v);
	}
	
	if (s1.size() != s2.size()) {
		cout << "Error1: size is not equal!" << endl;	
		return false;
	}

	foreach (int v in s2) {
		if (!s1.contains(v)) {
			cout << "Error2: set doesn't cotain: " << v << endl;	
			return false;
		}
	}
	return true;
}

bool testRemove(int size) {
	LinkedSet s1;
	Set<int> s2;
	
	for (int i=0; i<size; i++) {
		int v = randomInteger(0, 2*size);
		s1.add(v);
		s2.add(v);
	}
	
	foreach (int v in s2) {
		if (randomChance(0.5)) {
			s1.remove(v);
			s2.remove(v);
		}
	}

	if (s1.size() != s2.size()) {
		cout << "Error3: size is not equal!" << endl;	
		return false;
	}

	foreach (int v in s2) {
		if (!s1.contains(v)) {
			cout << "Error4: set doesn't cotain: " << v << endl;	
			return false;
		}
	}
	return true;
}

bool testIterator(int size) {
	LinkedSet s1;
	Set<int> s2;
	
	for (int i=0; i<size; i++) {
		int v = randomInteger(0, 2*size);
		s1.add(v);
		s2.add(v);
	}
	
	s1.resetIterator();
	while (s1.hasNext()) {
		int v = s1.next();
		if (!s2.contains(v)) {
			cout << "Error5: value not found!" << endl;			
			return false;
		}
		s2.remove(v);
	}
	if (!s2.isEmpty()) {
		cout << "Error6: not all elements iterated!" << endl;
		return false;
	}
	return true;
}

void testLinkedSet() {
	cout << "### Testing Linked Set ###" << endl;
	int testNum = 0;
	int passed = 0;
	//test add, cotains, size
	for (int i=1; i<=8; i++) {
		bool isCorrect = testAddContains(i*2);
		printTestResults(isCorrect, testNum, passed);
	}

	//test remove
	for (int i=1; i<=4; i++) {
		bool isCorrect = testRemove(i*4);
		printTestResults(isCorrect, testNum, passed);
	}

	//test iterator
	for (int i=1; i<=8; i++) {
		bool isCorrect = testIterator(i*3);
		printTestResults(isCorrect, testNum, passed);
	}

	cout << "passed: " << passed << endl;
}

int main() {
	setRandomSeed(0);
	testSumLevel();
	testLinkedSet();
	return 0;
}