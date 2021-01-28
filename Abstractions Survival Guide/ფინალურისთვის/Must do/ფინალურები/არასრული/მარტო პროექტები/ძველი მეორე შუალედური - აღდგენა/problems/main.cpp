#include <fstream>
#include <iostream>
#include <string>
#include "simpio.h"
#include "strlib.h"
#include "console.h"
#include "sub_tree.h"
#include <time.h>
#include "sum.h"
#include "random.h"


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

Cell * readList(ifstream &in) {
	int n;
	in >> n;
	Cell * list = new Cell;
	list->next = NULL;
	in >> list->d;
	Cell * curr = list;
	for (int i=1; i<n; i++) {
		curr->next = new Cell;
		curr = curr->next;
		curr->next = NULL;
		in >> curr->d;
	}
	return list;
}

void readSumTest(Cell * &num1, Cell * &num2, Cell * &answ, int testNum) {
	string testFileName = string("sum\\test") + integerToString(testNum) + ".txt";
	num1 = NULL;
	num2 = NULL;
	answ = NULL;
	ifstream in;
	in.open(testFileName.c_str());
	num1 = readList(in);
	num2 = readList(in);
	answ = readList(in);
	in.close();
}

bool equalsLists(Cell * l1, Cell * l2) {
	while (l1 != NULL && l2 != NULL) {
		if (l1->d != l2->d) {
			return false;
		}
		l1 = l1->next;
		l2 = l2->next;
	}
	return l1 == NULL && l2 == NULL;
}

void runSumTests() {
	cout << "### Run Sum tests ###" << endl;
	int testNum = 0;
	int passedCounter = 0;
	Cell * num1;
	Cell * num2;
	Cell * answ;
	Cell * res;
	for (int i=1; i<=15; i++) {
		readSumTest(num1, num2, answ, i);
		res = sum(num1, num2);
		printTestResults(equalsLists(answ, res), testNum, passedCounter);
	}
	
	cout << "###### passed " << passedCounter << " tests ######" << endl;

}

void insertIntoTree(Node * &root, int v) {
	if (root == NULL) {
		root = new Node;
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

Node * insertNode(Node * &root, int value, int weight) {
	if (root == NULL) {
		root = new Node;
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


void clearWeights(Node * root) {
	if (root == NULL) {
		return;
	}
	root->weight = 0;
	clearWeights(root->left);
	clearWeights(root->right);
}

void readBinaryTree(Node * &r, ifstream &in) {
	int n;
	in >> n;
	int w, v;
	for (int i=0; i<n; i++) {
		in >> v >> w;
		insertNode(r, v, w);
	}
}

void readMaxSubTreeTest(Node * &r1, Node * &r2, int testNum, int &answ) {
	string testFileName = string("subtree\\test") + integerToString(testNum) + ".txt";
	r1 = NULL;
	r2 = NULL;
	ifstream in;
	in.open(testFileName.c_str());
	readBinaryTree(r1, in);
	clearWeights(r1);
	readBinaryTree(r2, in);
	clearWeights(r2);
	in >> answ;
	in.close();
}
//###############################

int treeSize(Node * root) {
	if (root == NULL) {
		return 0;
	}
	return treeSize(root->left) + treeSize(root->right) + 1;
}

bool startsWith(Node * root1, Node * root2) {
	if (root2 == NULL) {
		return true;
	}
	if (root1 == NULL) {
		return false;
	}
	
	return	root1->v == root2->v && 
			startsWith(root1->left, root2->left) &&
			startsWith(root1->right, root2->right);
}

bool containsNode(Node * root1, Node * root2) {
	if (startsWith(root1, root2)) {
		return true;
	}
	if (root1 == NULL) {
		return false;
	}
	return	containsNode(root1->left, root2) ||
			containsNode(root1->right, root2);
}

void rec(Node *root1, Node * root2, int &res) {
	if (root1 == NULL || root2 == NULL) {
		return;
	}

	if (containsNode(root1, root2)) {
		int size = treeSize(root2);
		if (size > res) {
			res = size;
		}
		return;
	}
	
	rec(root1, root2->left, res);
	rec(root1, root2->right, res);
}


int maxSubTreeSol(Node * r1, Node * r2) {
	int res = 0;	
	rec(r1, r2, res);

	return res;
}
//####################################



void runSubTreeTests() {
	cout << "### Run Sub Tree tests ###" << endl;
	int testNum = 0;
	int passedCounter = 0;
	Node * r1;
	Node * r2;
	int answ, res;
	for (int i=1; i<=50; i++) {
		readMaxSubTreeTest(r1, r2, i, answ);
		res = maxSubTree(r1, r2);
		printTestResults(res == answ, testNum, passedCounter);
	}
	
	cout << "###### passed " << passedCounter << " tests ######" << endl;
}



int main() {
	setRandomSeed(0);
	//runSumTests();
	setRandomSeed(0);
	runSubTreeTests();
	return 0;
}