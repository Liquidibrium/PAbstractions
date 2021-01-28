#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
#include "vector.h"
#include "my_string.h"
#include <time.h>
#include "lexicon.h"
#include "random.h"
#include "longest_path.h"
#include <fstream>

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

bool equalsMyString(string str, MyString *s) {
	if (s == NULL) {
		return false;
	}
	if (str.length() != s->length()) {
		return false;
	}
	for (int i=0; i<s->length(); i++) {
		if (str[i] != s->get(i)) {
			return false;
		}
	}
	return true;
}

MyString* initMyString(string str) {
	MyString* s = new MyString;
	for (int i=0; i<str.length(); i++) {
		s->insert(i, str[i]);
	}
	return s;
}



void randomLengthInsertGetTest(MyString * &s, string &res) {
	s = new MyString;
	res = "";
	int len = randomInteger(100, 1000);
	for (int i=0; i<len; i++) {
		size_t pos = randomInteger(0, s->length());
		char c = (char)('a' + randomInteger(0, 26)%26);
		s->insert(pos, c);
		res.insert(pos, string("") + c);
	}
}

void randomSetTest(MyString * &s, string &res) {
	int len = randomInteger(s->length()/2, s->length()) % s->length();
	for (int i=0; i<len; i++) {
		size_t pos = randomInteger(0, s->length()) % s->length();
		char c = (char)('a' + randomInteger(0, 26)%26);
		s->set(pos, c);
		res[pos] = c;
	}
}

MyString * randomSubstrTest(MyString * &s, string &res) {
	int start = randomInteger(0, s->length()) % s->length();
	int len = randomInteger(0, s->length()-start);
	res = res.substr(start, len);
	return s->substr(start, len);
}

bool randomFindTestPassed(MyString * &s, string &res) {
	int start = randomInteger(0, s->length()) % s->length();
	int len = randomInteger(0, s->length()-start);
	string substr = res.substr(start, start+len);
	return res.find(substr) == s->find(initMyString(substr));
}


void runStringTests() {
	cout << "### Run String tests ###" << endl;
	int testNum = 0;
	int passedCounter = 0;
	MyString * s;
	bool passed;
	//#1
	passed = false;
	s = new MyString;
	printTestResults(s->length() == 0, testNum, passedCounter);
	//#2
	s = new MyString;
	s->insert(0, 'c');
	passed = s->length() == 1 && s->get(0) == 'c';
	printTestResults(passed, testNum, passedCounter);
	//#3
	s = new MyString;
	s->insert(0, 'w');
	s->insert(0, 'q');
	s->insert(2, 'e');
	passed = s->length() == 3 && equalsMyString("qwe", s);
	printTestResults(passed, testNum, passedCounter);
	//#4
	s = new MyString;
	s->insert(0, 'b');
	s->insert(0, '1');
	s->insert(2, 'c');
	s->insert(1, 'c');
	s->insert(2, 'd');
	passed = s->length() == 5 && equalsMyString("1cdbc", s);
	printTestResults(passed, testNum, passedCounter);
	//#5
	s = new MyString;
	s->insert(0, 'b');
	s->insert(0, '1');
	s->insert(2, 'c');
	s->insert(1, 'c');
	s->insert(2, 'd');
	s->set(0, 't');
	passed = s->length() == 5 && equalsMyString("tcdbc", s);
	printTestResults(passed, testNum, passedCounter);
	//#6
	s = new MyString;
	s->insert(0, '1');
	s->insert(1, 'c');
	s->insert(1, 'c');
	s->insert(2, 'd');
	s->set(0, 't');
	s->set(s->length()-1, 't');
	passed = s->length() == 4 && equalsMyString("tcdt", s);
	printTestResults(passed, testNum, passedCounter);
	//#7
	s = new MyString;
	s->insert(0, '1');
	s->insert(1, 'c');
	s->insert(1, 'c');
	s->insert(2, 'd');
	s->set(0, 't');
	s->insert(0, '1');
	s->set(s->length()-1, 't');
	s->insert(s->length(), 'k');
	passed = s->length() == 6 && equalsMyString("1tcdtk", s);
	printTestResults(passed, testNum, passedCounter);
	//#8
	s = new MyString;
	s->insert(0, '1');
	s = s->substr(0, 1);
	passed = equalsMyString("1", s);
	printTestResults(passed, testNum, passedCounter);
	//#9
	s = new MyString;
	s->insert(0, '1');
	s = s->substr(0, 0);
	passed = equalsMyString("", s);
	printTestResults(passed, testNum, passedCounter);
	//#10
	s = new MyString;
	s->insert(0, '1');
	s->insert(1, 'b');
	s->insert(2, 'c');
	s->insert(3, 'd');
	s->insert(4, 'e');
	s = s->substr(3, 2);
	passed = equalsMyString("de", s);
	printTestResults(passed, testNum, passedCounter);
	//#11
	s = new MyString;
	s->insert(0, '1');
	s->insert(1, 'b');
	s->insert(2, 'c');
	s->insert(3, 'd');
	s->insert(4, 'e');
	s = s->substr(0, s->length());
	passed = equalsMyString("1bcde", s);
	printTestResults(passed, testNum, passedCounter);
	//#12
	s = new MyString;
	s->insert(0, '1');
	s->insert(1, 'b');
	s->insert(2, 'c');
	s->insert(3, 'd');
	s->insert(4, 'e');
	s = s->substr(0, s->length());
	passed = equalsMyString("1bcde", s);
	printTestResults(passed, testNum, passedCounter);
	//#13
	s = new MyString;
	s->insert(0, '1');
	s->insert(1, 'b');
	s->insert(2, 'c');
	s->insert(3, 'd');
	s->insert(4, 'e');
	passed = s->find(initMyString("1bcdef")) == -1;
	printTestResults(passed, testNum, passedCounter);
	//#14
	s = new MyString;
	s->insert(0, '1');
	s->insert(1, 'b');
	s->insert(2, 'c');
	s->insert(3, 'd');
	s->insert(4, 'e');
	passed = s->find(initMyString("1bcde")) == 0;
	printTestResults(passed, testNum, passedCounter);
	//#15
	s = new MyString;
	s->insert(0, '1');
	s->insert(1, 'b');
	s->insert(2, 'c');
	s->insert(3, 'd');
	s->insert(4, 'e');
	passed = s->find(initMyString("de")) == 3;
	printTestResults(passed, testNum, passedCounter);
	//#16
	s = new MyString;
	s->insert(0, '1');
	s->insert(1, 'b');
	s->insert(2, 'c');
	s->insert(3, 'd');
	s->insert(4, 'e');
	passed = s->find(initMyString("1bcc")) == -1;
	printTestResults(passed, testNum, passedCounter);

	int num = 84;
	string res;
	//insert, get, length
	for (int i=0; i<num*0.5; i++) {
		randomLengthInsertGetTest(s, res);
		printTestResults(equalsMyString(res, s), testNum, passedCounter);
	}
	//set
	for (int i=0; i<num*0.1; i++) {
		randomLengthInsertGetTest(s, res);
		randomSetTest(s, res);
		printTestResults(equalsMyString(res, s), testNum, passedCounter);
	}
	//substr
	for (int i=0; i<num*0.2; i++) {
		randomLengthInsertGetTest(s, res);
		printTestResults(equalsMyString(res, randomSubstrTest(s, res)), testNum, passedCounter);
	}
	//find
	for (int i=0; i<num*0.2; i++) {
		randomLengthInsertGetTest(s, res);
		printTestResults(randomFindTestPassed(s, res), testNum, passedCounter);
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

Node* buildTree(Vector<int> &v) {
	Node * root = NULL;
	for (int i=0; i<v.size(); i++) {
		insertIntoTree(root, v[i]);
	}
	return root;
}

void insertNode(Node * &root, int value, int weight) {
	if (root == NULL) {
		root = new Node;
		root->v = value;
		root->weight = weight;
		root->left = NULL;
		root->right = NULL;
		return;
	}

	if (root->weight < weight) {
		insertNode(root->right, value, weight);
	} else {
		insertNode(root->left, value, weight);
	}
}

Node * randomBT(bool bst) {
	Node * r = NULL;
	int n = randomInteger(100, 1000);
	int v, w;
	Set<int> weights;
	for (int i=0; i<n; i++) {
		v = randomInteger(0, 1000);
		w = randomInteger(0, 1000);
		if (bst) {
			w = v;
		}
		if (weights.contains(w)) {
			continue;
		}
		insertNode(r, v, w);
	}
	return r;
}

void runLongestPathTests() {
	cout << "### Run Longest Path tests ###" << endl;
	int testNum = 0;
	int passedCounter = 0;
	int res;
	Node * root = NULL;
	Vector<int> v;
	//#1
	res = getLongestPath(root);
	printTestResults(res == 0, testNum, passedCounter);
	//#2
	v.clear();
	v += 1;
	root = buildTree(v);
	res = getLongestPath(root);
	printTestResults(res == 1, testNum, passedCounter);
	//#3
	v.clear();
	v += 1, 2, 3, 4, 5;
	root = buildTree(v);
	res = getLongestPath(root);
	printTestResults(res == 5, testNum, passedCounter);
	//#4
	v.clear();
	v += 10, 1, 2, 9, 14, 15;
	root = buildTree(v);
	res = getLongestPath(root);
	printTestResults(res == 6, testNum, passedCounter);
	//#5
	v.clear();
	v += 10, 5, 18, 16, 15, 12, 20, 19;
	root = buildTree(v);
	res = getLongestPath(root);
	printTestResults(res == 6, testNum, passedCounter);
	//#6
	v.clear();
	v += 20, 5, 1, 10, 30, 25, 40, 36, 35, 34, 33, 41, 42, 43;
	root = buildTree(v);
	res = getLongestPath(root);
	printTestResults(res == 9, testNum, passedCounter);
	//#7
	v.clear();
	v += 30, 50, 1, 25, 27, 29, 4, 14, 15, 16, 17, 18, 19, 20, 13, 12, 11, 10, 9, 8;
	root = buildTree(v);
	res = getLongestPath(root);
	printTestResults(res == 13, testNum, passedCounter);
	//#8
	v.clear();
	v += 30, 50, 1, 25, 27, 29, 4, 14, 15, 16, 17, 18, 19, 20, 10, 12, 11, 9, 8, 7, 6, 5;
	root = buildTree(v);
	res = getLongestPath(root);
	printTestResults(res == 13, testNum, passedCounter);
	//#9
	v.clear();
	v += 30, 50, 1, 25, 27, 29, 4, 14, 15, 16, 17, 18, 19, 20, 10, 12, 11, 9, 8, 7, 6, 5, 55, 60, 57;
	root = buildTree(v);
	res = getLongestPath(root);
	printTestResults(res == 15, testNum, passedCounter);
	//#10
	v.clear();
	v += 34, 50, 1, 25, 27, 29, 4, 14, 15, 16, 17, 18, 19, 20, 10, 12, 11, 9, 8, 7, 6, 5, 30, 31, 32, 33;
	root = buildTree(v);
	res = getLongestPath(root);
	printTestResults(res == 15, testNum, passedCounter);
	
	int answ[50] = {34, 29, 42, 31, 34, 32, 29, 34, 36, 30, 36, 33, 27, 28, 21, 49, 35, 36, 35, 35, 40, 45, 37, 37, 33, 33, 26, 38, 40, 36, 34, 42, 39, 34, 38, 28, 22, 37, 39, 30, 41, 31, 30, 35, 28, 36, 42, 30, 22, 36};
	//ofstream o;
	//o.open("1.txt");
	for (int i=0; i<50; i++) {
		root = randomBT(i<20);
		res = getLongestPath(root);
		//o << v << ", ";
		printTestResults(res == answ[i], testNum, passedCounter);
	}
//	o.close();
	cout << "###### passed " << passedCounter << " tests ######" << endl;
}

int main() {
	setRandomSeed(1);
	runStringTests();
	setRandomSeed(1);
	runLongestPathTests();
	return 0;
}