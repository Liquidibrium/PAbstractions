#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
#include "vector.h"
#include "queue.h"
#include <time.h>
#include "lexicon.h"
#include "change.h"

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

void runChangeTests() {
	cout << "### Run Change tests ###" << endl;
	bool res;
	int testNum = 0;
	int passedNum = 0;
	Vector<int> cshBills;
	Vector<int> cstBills;
	//#1
	cstBills += 15, 30, 120, 1, 3;
	res = giveChange(cshBills, cstBills, 4);
	printTestResults(res, testNum, passedNum);
	//#2
	cshBills.clear();
	cstBills.clear();
	cstBills += 35, 30, 1, 3, 7;
	cshBills += 102, 2, 8;
	res = giveChange(cshBills, cstBills, 6);
	printTestResults(res, testNum, passedNum);
	//#3
	cshBills.clear();
	cstBills.clear();
	cstBills += 1, 3, 7;
	cshBills += 3;
	res = giveChange(cshBills, cstBills, 5);
	printTestResults(res, testNum, passedNum);
	//#4
	cshBills.clear();
	cstBills.clear();
	cstBills += 1, 13, 17, 22, 10;
	cshBills += 3, 7, 15;
	res = giveChange(cshBills, cstBills, 26);
	printTestResults(res, testNum, passedNum);
	//#5
	cshBills.clear();
	cstBills.clear();
	cstBills += 1, 13, 18, 22, 10;
	cshBills += 3, 7, 15, 27;
	res = giveChange(cshBills, cstBills, 39);
	printTestResults(res, testNum, passedNum);
	//#6
	cshBills.clear();
	cstBills.clear();
	cstBills += 100, 140, 160, 180, 200, 240, 340;
	cshBills += 3, 7, 15, 27, 30, 48;
	res = giveChange(cshBills, cstBills, 339);
	printTestResults(res, testNum, passedNum);
	//#7
	cshBills.clear();
	cstBills.clear();
	cstBills += 100, 140, 160, 180, 200, 240, 340;
	cshBills += 3, 7, 15, 27, 30, 48;
	res = giveChange(cshBills, cstBills, 339);
	printTestResults(res, testNum, passedNum);
	//#8
	cshBills.clear();
	cstBills.clear();
	cstBills += 107, 140, 160, 180, 200, 240, 340;
	cshBills += 3, 7, 15, 27, 30, 50;
	res = giveChange(cshBills, cstBills, 339);
	printTestResults(res, testNum, passedNum);
	//#9
	cshBills.clear();
	cstBills.clear();
	cstBills += 10, 140, 160, 180, 200, 240, 340, 400, 430, 32;
	cshBills += 7, 15, 27, 30, 50, 3;
	res = giveChange(cshBills, cstBills, 29);
	printTestResults(res, testNum, passedNum);
	//#10
	cshBills.clear();
	cstBills.clear();
	cstBills += 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2056;
	cshBills += 12, 14, 26, 48, 52, 1052;
	res = giveChange(cshBills, cstBills, 17);
	printTestResults(!res, testNum, passedNum);
	//#11
	cshBills.clear();
	cstBills.clear();
	cstBills += 1001, 1000, 120, 160, 180, 1, 1, 1, 1, 1, 1;
	cshBills += 102, 200, 300, 800, 2500, 2300, 1200, 1400, 1004;
	res = giveChange(cshBills, cstBills, 7);
	printTestResults(res, testNum, passedNum);
	//#12
	cshBills.clear();
	cstBills.clear();
	cstBills += 5, 5, 5, 5, 5, 5, 24;
	cshBills += 1, 1, 1, 1;
	res = giveChange(cshBills, cstBills, 50);
	printTestResults(res, testNum, passedNum);
	//#13
	cshBills.clear();
	cstBills.clear();
	cstBills += 13, 227, 38, 101, 180, 204, 288, 128, 208, 13;
	cshBills += 10000, 10011, 1, 1, 5, 5;
	res = giveChange(cshBills, cstBills, 20);
	printTestResults(res, testNum, passedNum);

	//#14
	cshBills.clear();
	cstBills.clear();
	cstBills += 1, 10, 17, 28, 58, 60, 35, 70, 75;
	cshBills += 1, 1, 3, 100, 20, 6, 102, 84, 56, 10, 5, 5, 5, 5, 5;
	res = giveChange(cshBills, cstBills, 310);
	printTestResults(res, testNum, passedNum);

	//#15
	cshBills.clear();
	cstBills.clear();
	cstBills += 1, 10, 17, 28, 40, 58, 60, 35, 70, 75;
	cshBills += 1, 1, 3, 100, 20, 6, 84, 56, 10, 5, 5;
	res = giveChange(cshBills, cstBills, 710);
	printTestResults(!res, testNum, passedNum);
	cout << "###### passed " << passedNum << " tests ######" << endl;
}

int main() {
	runChangeTests();
	return 0;
}