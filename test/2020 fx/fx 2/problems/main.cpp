#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
#include "vector.h"
#include "queue.h"
#include <time.h>
#include "TreeWidth.h"
#include "Jump.h"
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

int answers[] = {972, 1007, 1170, 1361, 1513, 1566, 1569};
bool runTreeWidthTest(int testNum) {
	TreeNode *root = NULL;
	int answ = 0;
	string testFileName = string("treewidth\\test") + integerToString(testNum + 1) + ".txt";
	ifstream input;
	input.open(testFileName.c_str());
	readBinaryTree(root, input, answ);
	clearWeights(root);
	input.close();

	return treeMaxWidth(root) == answ;
}

const int treeWidthTestsNum = 20;

void runTreeWidthTests() {
	cout << "### Run Tree Width tests ###" << endl;
	int passedNum = 0;
	int testNum = 0;

	for (; testNum<treeWidthTestsNum; testNum++) {
		bool res = runTreeWidthTest(testNum);
		printTestResults(res, testNum, passedNum);
	}

	cout << "###### passed " << passedNum << " tests ######" << endl;
}

bool runJumpTest(int testNum) {
	string testFileName = string("jump\\test") + integerToString(testNum + 1) + ".txt";
	ifstream input;
	input.open(testFileName.c_str());
	int testsCount;
	input >> testsCount;
	for (int i=0; i<testsCount; i++) {
		int n, start;
		bool answ;
		input >> n >> start >> answ;
		int* arr = new int[n];
		for(int i = 0; i < n; i++)
			input >> arr[i];

		bool res = minJumps(arr, n, start);
		if (res != answ) {
			return false;
		}
	}
	input.close();
	return true;
}

const int jumpTestNum = 10;
void runJumpTests() {
	cout << "### Run Jump tests ###" << endl;
	int passedNum = 0;
	int testNum = 0;

	for (; testNum<jumpTestNum; testNum++) {
		bool res = runJumpTest(testNum);
		printTestResults(res, testNum, passedNum);
	}

	cout << "###### passed " << passedNum << " tests ######" << endl;
}

int main() {
	runTreeWidthTests();
	runJumpTests();
	return 0;
}