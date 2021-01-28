#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
#include "vector.h"
#include "queue.h"
#include <time.h>
#include "lexicon.h"
#include "ListSum.h"
#include "TreeDistance.h"


using namespace std;

void printTestResults(bool passed, int testNum, int & passedCounter) {
	if (passed) {
		cout << "test " << testNum << " passed" << endl;
		passedCounter++;
	} else {
		cout << "test " << testNum << " failed" << endl;
	}
}

Node * newNode(int val) {
	Node * node = new Node;
	node->left = NULL;
	node->right = NULL;
	node->value = val;
	return node;
}

bool runTreeDistanceTest(int testNum) {
	Set<int> res;
	Node * node;

	switch (testNum) {
		case 1:
			node = newNode(10);
			res = kDistance(node, 0);
			return res.size() == 1 && res.contains(10);

		case 2:
			node = newNode(10);
			node->left = newNode(20);
			node->left->left  = newNode(40);
			node->left->left->left = newNode(50);
			res = kDistance(node, 2);

			return (res.size() == 1 && res.contains(40));
		case 3:
			node = newNode(1);
			node->left = newNode(2);
			node->left->left  = newNode(3);
			node->left->left->left = newNode(4);
			node->left->left->right  = newNode(5);
			node->right = newNode(6);
			node->right->right = newNode(7);
			node->right->right->right = newNode(8);

			res = kDistance(node, 3);

			return (res.size() == 3 && res.contains(4) && res.contains(5) && res.contains(8));

		case 4:
			node = newNode(1);
			node->left = newNode(2);
			node->left->left  = newNode(3);
			node->left->left->left = newNode(4);
			node->left->left->right  = newNode(5);
			node->right = newNode(6);
			node->right->right = newNode(7);
			node->right->right->right = newNode(8);

			node->right->right->right->right = newNode(9);
			node->right->right->right->left = newNode(10);
			node->left->left->left->left = newNode(11);
			node->left->left->right->left  = newNode(12);
			node->left->left->right->right  = newNode(13);

			node->left->left->right->left->left  = newNode(14);
			node->left->left->right->right->right  = newNode(15);
			node->left->left->left->left->right = newNode(16);

			res = kDistance(node, 4);

			return (res.size() == 5 && res.contains(9) && res.contains(10) && 
					res.contains(11) && res.contains(12) && res.contains(13));

		case 5:
			node = newNode(1);
			node->left = newNode(2);
			node->left->left  = newNode(3);
			node->left->left->left = newNode(4);
			node->left->left->left->left  = newNode(5);
			node->left->left->left->left->left = newNode(6);
			node->left->left->left->left->left->left = newNode(7);
			node->left->left->left->left->left->left->left = newNode(8);
			node->left->left->left->left->left->left->left->left = newNode(9);

			res = kDistance(node, 7);

			return (res.size() == 1 && res.contains(8));

		case 6:
			node = newNode(1);
			node->left = newNode(2);
			node->left->left  = newNode(3);
			node->left->left->left = newNode(4);
			node->left->left->left->left  = newNode(5);
			node->left->left->left->left->left = newNode(6);
			node->left->left->left->left->left->left = newNode(7);
			node->left->left->left->left->left->left->left = newNode(8);

			node->right = newNode(9);
			node->right->right = newNode(10);
			node->right->right->left = newNode(11);
			node->right->right->left->left = newNode(12);
			node->right->right->left->left->left = newNode(13);
			node->right->right->left->left->left->right = newNode(14);
			node->right->right->left->left->left->right->left = newNode(15);
			
			node->right->right->left->left->left->right->left->left = newNode(16);

			res = kDistance(node, 7);

			return (res.size() == 2 && res.contains(8) && res.contains(15));

		case 7:
			node = newNode(1);
			node->left = newNode(2);
			node->left->left  = newNode(3);
			node->left->left->left = newNode(4);
			node->left->left->left->left  = newNode(5);
			node->left->left->left->left->left = newNode(6);
			node->left->left->left->left->left->left = newNode(7);
			node->left->left->left->left->left->left->left = newNode(8);

			node->right = newNode(9);
			node->right->right = newNode(10);
			node->right->right->left = newNode(11);
			node->right->right->left->left = newNode(12);
			node->right->right->left->left->left = newNode(13);
			node->right->right->left->left->left->right = newNode(14);
			node->right->right->left->left->left->right->left = newNode(15);
			
			node->right->right->left->left->left->right->left->left = newNode(16);

			res = kDistance(node, 12);

			return (res.size() == 0);

		case 8: 
			node = newNode(1);
			node->left = newNode(2);
			node->right = newNode(3);

			node->left->left = newNode(4);
			node->left->right = newNode(5);
			node->right->left = newNode(6);
			node->right->right = newNode(7);

			node->left->left->left = newNode(8);
			node->left->left->right = newNode(9);
			node->left->right->left = newNode(10);
			node->left->right->right = newNode(11);
			node->right->left->left = newNode(12);
			node->right->left->right = newNode(13);
			node->right->right->left = newNode(14);
			node->right->right->right = newNode(15);

			res = kDistance(node, 3);

			return (res.size() == 8 && res.contains(8) && res.contains(9) && 
				res.contains(10) && res.contains(11) && res.contains(12) &&
				res.contains(13) && res.contains(14) && res.contains(15));
			
		case 9: 
			node = newNode(1);
			node->left = newNode(2);
			node->right = newNode(3);

			node->left->left = newNode(4);
			node->left->right = newNode(5);
			node->right->left = newNode(6);
			node->right->right = newNode(7);

			node->left->left->left = newNode(8);
			node->left->left->right = newNode(9);
			node->left->right->left = newNode(10);
			node->left->right->right = newNode(11);
			node->right->left->left = newNode(12);
			node->right->left->right = newNode(13);
			node->right->right->left = newNode(14);
			node->right->right->right = newNode(15);

			res = kDistance(node, 2);

			return (res.size() == 4 && res.contains(4) && res.contains(5) && 
				res.contains(6) && res.contains(7));

		case 10: 
			node = newNode(1);
			node->left = newNode(2);
			node->right = newNode(3);

			node->left->left = newNode(4);
			node->left->right = newNode(5);
			node->right->left = newNode(6);
			node->right->right = newNode(7);

			node->left->left->left = newNode(8);
			node->left->left->right = newNode(9);
			node->left->right->right = newNode(11);
			node->right->left->left = newNode(12);
			node->right->left->right = newNode(13);
			node->right->right->right = newNode(15);

			res = kDistance(node, 3);

			return (res.size() == 6 && res.contains(8) && res.contains(9) && 
				res.contains(11) && res.contains(12) &&
				res.contains(13) && res.contains(15));

	}
	return false;
}

const int treeDistanceTestNum = 10;
void runTreeDistanceTests() {
	cout << "### Run Tree Distance tests ###" << endl;
	int passedNum = 0;
	int testNum = 1;

	for (; testNum<=treeDistanceTestNum; testNum++) {
		bool res = runTreeDistanceTest(testNum);
		printTestResults(res, testNum, passedNum);
	}

	cout << "###### passed " << passedNum << " tests ######" << endl;
}

digit * buildNumbList(string num) {
	digit * list = NULL;
	for (int i=num.length()-1; i>=0; i--) {
		digit * d = new digit;
		d->d = num[i] - '0';
		d->next = list;
		list = d;
	}
	return list;
}

bool isEqual(digit * num1, digit * num2) {
	while (num1 != NULL && num2 != NULL) {
		if (num1->d != num2->d)
			return false;
		num1 = num1->next;
		num2 = num2->next;
	}

	return num1 == num2;
}

const int sumTestNum = 10;
string tests[sumTestNum][3] = {
	{"1", "5", "6"},
	{"11", "9", "20"}, 
	{"57", "184", "241"},
	{"99999", "1", "100000"},
	{"1", "999999999", "1000000000"},
	{"23745276", "12374512772", "12398258048"},
	{"9034872384", "1238719237918273912739", "1238719237927308785123"},
	{"234234234234234623457645765324", "53432453464563523454535", "234234287666688088021169219859"},
	{"2", "53432453464563523454312323453899", "53432453464563523454312323453901"},
	{"22938742922342234347299023497996", "14", "22938742922342234347299023498010"},
};


bool runSumTest(int testNum) {
	digit * num1 = buildNumbList(tests[testNum-1][0]);
	digit * num2 = buildNumbList(tests[testNum-1][1]);
	digit * answ = buildNumbList(tests[testNum-1][2]);
	
	digit * res = sum(num1, num2);
	return isEqual(res, answ);
}

void runSumTests() {
	cout << "### Run Sum tests ###" << endl;
	int passedNum = 0;
	int testNum = 1;

	for (; testNum<=sumTestNum; testNum++) {
		bool res = runSumTest(testNum);
		printTestResults(res, testNum, passedNum);
	}

	cout << "###### passed " << passedNum << " tests ######" << endl;
}

int main() {
	runTreeDistanceTests();
	runSumTests();
	return 0;
}