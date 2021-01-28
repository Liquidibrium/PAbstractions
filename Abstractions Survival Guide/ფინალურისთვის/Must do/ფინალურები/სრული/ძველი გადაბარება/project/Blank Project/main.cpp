#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
#include "vector.h"
#include "queue.h"
#include <time.h>
#include "lexicon.h"
#include "..\..\problems\flattenlist.h"
#include "..\..\problems\allcombinations.h"
#include "..\..\problems\mindicethrows.h"

void printTestResults(bool passed, int & testNum, int & passedCounter) {
	testNum++;
	if (passed) {
		passedCounter++;
		cout << "test " << testNum << " passed, total passed " << passedCounter << endl;
	} else {
		cout << "test " << testNum << " failed, total passed " << passedCounter << endl;
	}
}


ListNode * newListNode(int v) {
	ListNode * n = new ListNode;
	n->down = NULL;
	n->next = NULL;
	n->value = v;

	return n;
}
#define START_NUM 10

bool testFlattenList(ListNode * list, int n) {
	bool passed = true;
	for (int i=START_NUM; i<START_NUM + n; i++) {
		if (list == NULL)
			return false;
		passed = passed && list->value == i && list->down == NULL;
		list = list->next;
	}

	return passed;
}

void runFlattenListTests() {
	cout << "### Run Flatten List tests ###" << endl;
	bool passed = false;
	int testNum = 0; 
	int passedCounter = 0;
	
	ListNode * list;
	ListNode * res;
	int count;
	//#1
	count = START_NUM;
	list = newListNode(count++);
	list->down = newListNode(count++);
	list->down->down = newListNode(count++);
	list->down->down->down = newListNode(count++);


	res = flattenList(list);
	printTestResults(testFlattenList(res, 4), testNum, passedCounter);

	//#2
	count = START_NUM;
	list = newListNode(count++);
	list->down = newListNode(count++);
	list->down->down = newListNode(count++);
	list->down->down->next = newListNode(count++);
	list->down->down->next->next = newListNode(count++);
	list->down->down->next->next->down = newListNode(count++);
	list->down->down->next->next->next = newListNode(count++);

	res = flattenList(list);
	printTestResults(testFlattenList(res, 7), testNum, passedCounter);

	//#3
	count = START_NUM;
	list = newListNode(count++);
	list->down = newListNode(count++);
	list->next = newListNode(count++);
	list->next->down = newListNode(count++);

	res = flattenList(list);
	printTestResults(testFlattenList(res, 4), testNum, passedCounter);

	//#4
	count = START_NUM;
	list = newListNode(count++);
	list->next = newListNode(count++);
	list->next->next = newListNode(count++);
	list->next->next->down = newListNode(count++);
	list->next->next->down->down = newListNode(count++);
	list->next->next->down->down->down = newListNode(count++);
	list->next->next->next = newListNode(count++);
	
	res = flattenList(list);
	printTestResults(testFlattenList(res, 7), testNum, passedCounter);

	//#5
	count = START_NUM;
	list = newListNode(count++);
	list->next = newListNode(count++);
	list->next->down = newListNode(count++);
	list->next->down->next = newListNode(count++);
	list->next->down->next->down = newListNode(count++);
	list->next->down->next->down->next = newListNode(count++);
	list->next->down->next->next = newListNode(count++);
	
	list->next->next = newListNode(count++);
	list->next->next->next = newListNode(count++);
	list->next->next->next->next = newListNode(count++);
	list->next->next->next->next->next = newListNode(count++);
	list->next->next->next->next->next->down = newListNode(count++);
	list->next->next->next->next->next->down->down = newListNode(count++);
	list->next->next->next->next->next->down->down->down = newListNode(count++);
	list->next->next->next->next->next->down->down->down->next = newListNode(count++);
	list->next->next->next->next->next->down->next = newListNode(count++);
	list->next->next->next->next->next->next = newListNode(count++);
	list->next->next->next->next->next->next->next = newListNode(count++);

	res = flattenList(list);
	printTestResults(testFlattenList(res, 18), testNum, passedCounter);


	cout << "###### passed " << passedCounter << " tests ######" << endl;
}

void cleanMovesArray(int arr[], int n) {
	for (int i=0; i<n; i++) {
		arr[i] = -1;
	}
}

void runMinDiceThrowsTests() {
	cout << "### Run Min Dice Throws tests ###" << endl;
	bool passed = false;
	int testNum = 0; 
	int passedCounter = 0;
	
	int n;
	int * moves;
	//#1
    n = 300;
	moves = new int[n];
    cleanMovesArray(moves, n);
    // Ladders
    moves[2] = 21;
    moves[4] = 7;
    moves[10] = 25;
    moves[19] = 28;
    // Snakes
    moves[26] = 0;
    moves[20] = 8;
    moves[16] = 3;
    moves[18] = 6;
	printTestResults(getMinDiceThrows(moves, n) == 48, testNum, passedCounter);

	//#2
    n = 360;
	moves = new int[n];
    cleanMovesArray(moves, n);
    // Ladders
    moves[2] = 15;
    moves[4] = 6;
    moves[14] = 24;
    moves[17] = 19;
	moves[20] = 31;
    // Snakes
    moves[11] = 1;
    moves[13] = 10;
    moves[16] = 3;
    moves[30] = 18;
    moves[34] = 21;
	printTestResults(getMinDiceThrows(moves, n) == 57, testNum, passedCounter);

	//#3
    n = 240;
	moves = new int[n];
    cleanMovesArray(moves, n);
    // Ladders
    moves[4] = 16;
    moves[14] = 23;
    // Snakes
    moves[17] = 5;
    moves[18] = 5;
    moves[19] = 4;
    moves[20] = 3;
    moves[21] = 2;
    moves[22] = 1;
	printTestResults(getMinDiceThrows(moves, n) == 39, testNum, passedCounter);

	//#4
    n = 280;
	moves = new int[n];
    cleanMovesArray(moves, n);
    // Ladders
    moves[3] = 19;
    moves[15] = 26;
    // Snakes
    moves[20] = 7;
    moves[21] = 7;
    moves[22] = 4;
    moves[23] = 6;
    moves[24] = 6;
    moves[25] = 5;
	printTestResults(getMinDiceThrows(moves, n) == 46, testNum, passedCounter);

	//#5
    n = 1000;
	moves = new int[n];
	cleanMovesArray(moves, n);
    // Ladders
    moves[3] = 39;
    moves[38] = 46;
    moves[47] = 100;
    moves[55] = 300;

    // Snakes
    moves[40] = 10;
    moves[41] = 10;
    moves[42] = 10;
    moves[43] = 10;
    moves[44] = 10;
    moves[45] = 10;
	printTestResults(getMinDiceThrows(moves, n) == 126, testNum, passedCounter);

	//#6
    n = 1000;
	moves = new int[n];
	cleanMovesArray(moves, n);
    // Ladders
    moves[3] = 39;
    moves[38] = 46;
    // Snakes
    moves[40] = 10;
    moves[41] = 10;
    moves[42] = 10;
    moves[43] = 10;
    moves[44] = 10;
    moves[45] = 10;
	printTestResults(getMinDiceThrows(moves, n) == 166, testNum, passedCounter);

	//#7
    n = 1000;
	moves = new int[n];
	cleanMovesArray(moves, n);
    // Ladders
    moves[3] = 39;
    moves[38] = 46;
    moves[47] = 99;
    moves[55] = 299;
	moves[98] = 400;

    // Snakes
    moves[40] = 10;
    moves[41] = 10;
    moves[42] = 10;
    moves[43] = 10;
    moves[44] = 10;
    moves[45] = 10;

    moves[100] = 10;
    moves[101] = 10;
    moves[102] = 10;
    moves[103] = 10;
    moves[104] = 10;
    moves[105] = 10;
	moves[105] = 10;
	printTestResults(getMinDiceThrows(moves, n) == 116, testNum, passedCounter);

	//#8
    n = 1000;
	moves = new int[n];
	cleanMovesArray(moves, n);
    // Ladders
    moves[3] = 39;
    moves[38] = 46;
    moves[47] = 99;
    moves[55] = 299;
	moves[200] = 500;

    // Snakes
    moves[40] = 10;
    moves[41] = 10;
    moves[42] = 10;
    moves[43] = 10;
    moves[44] = 10;
    moves[45] = 10;

	printTestResults(getMinDiceThrows(moves, n) == 109, testNum, passedCounter);

	//#9
    n = 1000;
	moves = new int[n];
	cleanMovesArray(moves, n);
    // Ladders
    moves[3] = 39;
    moves[38] = 46;
    moves[47] = 99;
    moves[55] = 299;
	moves[200] = 500;
	moves[400] = 900;


    // Snakes
    moves[40] = 10;
    moves[41] = 10;
    moves[42] = 10;
    moves[43] = 10;
    moves[44] = 10;
    moves[45] = 10;

	printTestResults(getMinDiceThrows(moves, n) == 43, testNum, passedCounter);

	//#10
    n = 1000;
	moves = new int[n];
	cleanMovesArray(moves, n);
    // Ladders
    moves[3] = 39;
    moves[38] = 46;
    moves[47] = 99;
    moves[55] = 299;
	moves[200] = 500;
	moves[400] = 840;
	moves[499] = 990;

    // Snakes
    moves[40] = 10;
    moves[41] = 10;
    moves[42] = 10;
    moves[43] = 10;
    moves[44] = 10;
    moves[45] = 10;
	printTestResults(getMinDiceThrows(moves, n) == 45, testNum, passedCounter);

	cout << "###### passed " << passedCounter << " tests ######" << endl;


}

void runAllCombinationsTests() {
	cout << "### Run All Combinations Tests###" << endl;
	bool passed = false;
	int testNum = 0; 
	int passedCounter = 0;

	cout << allCombinations(5) << endl;
	int res;
	//#6
	res = allCombinations(6);
	printTestResults(res == 928, testNum, passedCounter);

	//#7
	res = allCombinations(7);
	printTestResults(res == 7100, testNum, passedCounter);

	//#8
	res = allCombinations(8);
	printTestResults(res == 58372, testNum, passedCounter);

	//#9
	res = allCombinations(9);
	printTestResults(res == 531448, testNum, passedCounter);

	cout << "###### passed " << passedCounter << " tests ######" << endl;
}



int main() {
	//runFlattenListTests();
	//runMinDiceThrowsTests();
	runAllCombinationsTests();
	return 0;
}
