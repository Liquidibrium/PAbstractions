#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
#include "vector.h"
#include "queue.h"
#include <time.h>
#include "Palindromic.h"
#include "Orange.h"
#include "random.h"


using namespace std;

void printTestResults(bool passed, int testNum, int & passedCounter) {
	if (passed) {
		cout << "test " << testNum << " passed" << endl;
		passedCounter++;
	} else {
		cout << "test " << testNum << " failed" << endl;
	}
}

void clearWeights(TreeNode * root) {
	if (root == NULL) {
		return;
	}
	root->weight = 0;
	clearWeights(root->left);
	clearWeights(root->right);
}

TreeNode* insertNode(TreeNode * &root, int value, int weight) {
	if (root == NULL) {
		root = new TreeNode;
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

void readBinaryTree(TreeNode * &r, ifstream &input, int &answ) {
	int n;
	input >> n >> answ;
	int w, v;
	for (int i=0; i<n; i++) {
		input >> v >> w;
		TreeNode * node = insertNode(r, v, w);
	}
}

int answers[] = {848, 906, 938, 1080, 1180};
//int answers[] = {809, 949, 1003, 1063, 1109};
bool runPalindromicTest(int testNum) {
	TreeNode *root = NULL;
	int answ = 0;
	string testFileName = string("palindromic\\test") + integerToString(testNum + 1) + ".txt";
	ifstream input;
	input.open(testFileName.c_str());
	readBinaryTree(root, input, answ);
	clearWeights(root);
	input.close();
/*
	if (testNum > 9) {
		root = NULL;
		string testFile = string("test") + integerToString(testNum+1) + ".txt";
		ofstream outf(testFile.c_str());
		answ = answers[testNum - 10];
		setRandomSeed(testNum + 1); 
		int treeSize = testNum * 500;
		outf << treeSize << " " << answers[testNum - 10] << endl;
		for (int i=0; i<treeSize; i++) {
			outf << randomInteger(1,3) << " " << randomInteger(0, 10000) << endl;
		}
		outf << endl << endl;
		outf.close();
	}
*/	
	return pseudoPalindromicPaths(root) == answ;
}

const int palindromicTestsNum = 15;

void runPalindromicTests() {
	cout << "### Run Browser tests ###" << endl;
	int passedNum = 0;
	int testNum = 0;

	for (; testNum<palindromicTestsNum; testNum++) {
		bool res = runPalindromicTest(testNum);
		printTestResults(res, testNum, passedNum);
	}

	cout << "###### passed " << passedNum << " tests ######" << endl;
}

bool runOrangeTest(int testNum) {
	string testFileName = string("orange\\test") + integerToString(testNum + 1) + ".txt";
	ifstream input;
	input.open(testFileName.c_str());
	int rows,cols,x,y,answ;
	input >> rows >> cols >> x >> y >> answ;

	int** grid = new int*[rows];
	for(int i = 0; i < rows; ++i)
		grid[i] = new int[cols];

	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {
			input >> grid[i][j];
		}
	}
	input.close();
	
	int res = orangesRotting(grid, cols, rows, x, y);
	
	return res == answ;
}

const int orangeTestNum = 13;
void runOrangeTests() {
	cout << "### Run Orange tests ###" << endl;
	int passedNum = 0;
	int testNum = 0;

	for (; testNum<orangeTestNum; testNum++) {
		bool res = runOrangeTest(testNum);
		printTestResults(res, testNum, passedNum);
	}

	cout << "###### passed " << passedNum << " tests ######" << endl;
}

int main() {
	runPalindromicTests();
	runOrangeTests();
	
	return 0;
}