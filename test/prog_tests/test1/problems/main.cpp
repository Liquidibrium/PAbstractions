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
#include "expression.h"
#include "keyboard.h"
#include "foreach.h"

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

void testExpression() {
	cout << "### Testing Expression ###" << endl;
	bool passed = false;
	int testNum = 0; 
	int passedCounter = 0;
	
	Set<int> nums;	
	int res;
	//#1
	nums.clear();
	nums += 4, 3, 6;
	res = getExpressionNum(7, nums);
	printTestResults(res == 2, testNum, passedCounter);
	//#2
	nums.clear();
	nums += 1000000, 2000000, 3000000, 4000000;
	res = getExpressionNum(4000000, nums);
	printTestResults(res == 5, testNum, passedCounter);
	//#3
	nums.clear();
	nums += 10000001, 20000002, 30000003, 40000004, 40000005, 40000006, 40000007, 40000008;
	res = getExpressionNum(4, nums);
	printTestResults(res == 21, testNum, passedCounter);
	//#4
	nums.clear();
	nums += 3, 4, 6, 5, 15, 7;
	res = getExpressionNum(8, nums);
	printTestResults(res == 15, testNum, passedCounter);
	//#5
	nums.clear();
	nums += 2, 4, 6, 8, 10;
	res = getExpressionNum(8, nums);
	printTestResults(res == 12, testNum, passedCounter);
	//#6
	nums.clear();
	nums += 2, 3, 7, 11;
	res = getExpressionNum(12, nums);
	printTestResults(res == 2, testNum, passedCounter);
	//#7
	nums.clear();
	nums += 5, 2, 3, 7, 11;
	res = getExpressionNum(14, nums);
	printTestResults(res == 5, testNum, passedCounter);
	//#8
	nums.clear();
	nums += 5, 2, 3, 7, 11;
	res = getExpressionNum(5, nums);
	printTestResults(res == 6, testNum, passedCounter);
	//#9
	nums.clear();
	nums += 90;
	res = getExpressionNum(5, nums);
	printTestResults(res == 0, testNum, passedCounter);
	//#9
	nums.clear();
	nums += 190;
	res = getExpressionNum(-190, nums);
	printTestResults(res == 1, testNum, passedCounter);

	cout << "###### passed " << passedCounter << " tests ######" << endl;
}

void testGetAllEncryption(){
	cout << "### Testing Keyboard ###" << endl;
	bool passed = false;
	int testNum = 0; 
	int passedCounter = 0;
	Set<string> res, answ;
	Lexicon lex("EnglishWords.dat");
	//#1
	res.clear();
	answ.clear();
	answ += "ado", "nae", "no";
	getAllEncryption("1415", res, lex);
	printTestResults(res == answ, testNum, passedCounter);
	//#2
	res.clear();
	answ.clear();
	answ += "abbe", "aby", "ave";
	getAllEncryption("1225", res, lex);
	printTestResults(res == answ, testNum, passedCounter);
	//#3
	res.clear();
	answ.clear();
	answ += "abbes", "abys", "aves";
	getAllEncryption("122519", res, lex);
	printTestResults(res == answ, testNum, passedCounter);
	//#4
	res.clear();
	answ.clear();
	answ += "ailed", "sabed", "sled";
	getAllEncryption("191254", res, lex);
	printTestResults(res == answ, testNum, passedCounter);
	//#5
	res.clear();
	answ.clear();
	answ += "bans", "unai", "uns";
	getAllEncryption("211419", res, lex);
	printTestResults(res == answ, testNum, passedCounter);
	//#6
	res.clear();
	answ.clear();
	answ += "bura", "vara";
	getAllEncryption("221181", res, lex);
	printTestResults(res == answ, testNum, passedCounter);
	//#7
	res.clear();
	answ.clear();
	answ += "tae", "to";
	getAllEncryption("2015", res, lex);
	printTestResults(res == answ, testNum, passedCounter);
	//#8
	res.clear();
	answ.clear();
	answ += "thae", "tho";
	getAllEncryption("20815", res, lex);
	printTestResults(res == answ, testNum, passedCounter);
	//#9
	res.clear();
	answ.clear();
	answ += "bob";
	getAllEncryption("2152", res, lex);
	printTestResults(res == answ, testNum, passedCounter);
	//#10
	res.clear();
	answ.clear();
	answ += "web";
	getAllEncryption("2352", res, lex);
	printTestResults(res == answ, testNum, passedCounter);
	//#11
	res.clear();
	answ.clear();
	answ += "weed";
	getAllEncryption("23554", res, lex);
	printTestResults(res == answ, testNum, passedCounter);
	//#12
	res.clear();
	answ.clear();
	getAllEncryption("01234", res, lex);
	printTestResults(res == answ, testNum, passedCounter);
	//#13
	res.clear();
	answ.clear();
	answ += "bee", "ye";
	getAllEncryption("255", res, lex);
	printTestResults(res == answ, testNum, passedCounter);

	cout << "###### passed " << passedCounter << " tests ######" << endl;
}

int main() {
	setRandomSeed(0);
	testExpression();
	testGetAllEncryption();
	return 0;
}