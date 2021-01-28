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
#include "passcode.h"
#include "vitamins.h"

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


string pass;
bool isCorrectCode(string code) {
	return pass == code;
}

void testPasscode() {
	cout << "### Testing Passcode ###" << endl;
	int testNum = 0;
	int passed = 0;
	string s;
	//# Test 1
	pass = "11111";
	s = crackCode("1", 5, isCorrectCode);
	printTestResults(s == pass, testNum, passed);
	
	//# Test 2
	pass = "4321";
	s = crackCode("1234", 4, isCorrectCode);
	printTestResults(s == pass, testNum, passed);

	//# Test 3
	pass = "311222";
	s = crackCode("213", 6, isCorrectCode);
	printTestResults(s == pass, testNum, passed);

	//# Test 4
	pass = "9001202";
	s = crackCode("9012", 7, isCorrectCode);
	printTestResults(s == pass, testNum, passed);

	//# Test 5
	pass = "1111111";
	s = crackCode("1", 7, isCorrectCode);
	printTestResults(s == pass, testNum, passed);

	//# Test 6
	pass = "11221";
	s = crackCode("21", 7, isCorrectCode);
	printTestResults(s == pass, testNum, passed);

	//# Test 7
	pass = "2111113";
	s = crackCode("321", 7, isCorrectCode);
	printTestResults(s == pass, testNum, passed);

	//# Test 8
	pass = "6612345";
	s = crackCode("654321", 7, isCorrectCode);
	printTestResults(s == pass, testNum, passed);

	//# Test 9
	pass = "0101019";
	s = crackCode("190", 7, isCorrectCode);
	printTestResults(s == pass, testNum, passed);

	//# Test 10
	pass = "1234567";
	s = crackCode("7654321", 7, isCorrectCode);
	printTestResults(s == pass, testNum, passed);

	cout << "passed: " << passed << endl;
}

Set<string> stringToSet(string vitamins) {
	Set<string> s;
	for (int i=0; i<vitamins.length(); i++) {
		s += vitamins.substr(i, 1);
	}
	return s;
}

bool coversAllVit(Set<string> &vitamins, Vector<int> &res, Vector< Set<string> > &fruits) {
	Set<string> tmp;
	for (int i = 0; i < res.size(); i++) {
		if (res[i] < 0 || res[i] >= fruits.size()) {
			cout << "returned index " << res[i] << "out of range,";
			cout << " fruits vector size is " << fruits.size() << endl;
			return false;
		}
		tmp += fruits[res[i]];
	}
	
	bool result = vitamins.isSubsetOf(tmp);
	if (!result) {
		cout << "given fruits do not cover all vitamins!" << endl;
	}
	return result;
}

void testVitamins() {
	cout << "### Testing Vitamins ###" << endl;
	int testNum = 0;
	int passed = 0;
	int answerSize = 0;
	Set<string> vitamins;
	Vector<int> res;
	Vector< Set<string> > fruits;
	bool result;
	
	// Test 1
	vitamins.clear();
	fruits.clear();
	answerSize = 1; // answer
	vitamins += "A", "B";
	fruits.push_back(stringToSet("A"));
	fruits.push_back(stringToSet("AB"));

	res = fruitList(vitamins, fruits);
	result = res.size() == answerSize && coversAllVit(vitamins, res, fruits);
	printTestResults(result, testNum, passed);
	
	// Test 2
	vitamins.clear();
	fruits.clear();
	answerSize = 2; // answer
	vitamins += "A", "B", "C";
	fruits.push_back(stringToSet("AB"));
	fruits.push_back(stringToSet("C"));

	res = fruitList(vitamins, fruits);
	result = res.size() == answerSize && coversAllVit(vitamins, res, fruits);
	printTestResults(result, testNum, passed);
	
	// Test 3
	vitamins.clear();
	fruits.clear();
	answerSize = 2; // answer
	vitamins += "A", "B", "C", "D";
	fruits.push_back(stringToSet("AD"));
	fruits.push_back(stringToSet("ABC"));
	fruits.push_back(stringToSet("BC"));


	res = fruitList(vitamins, fruits);
	result = res.size() == answerSize && coversAllVit(vitamins, res, fruits);
	printTestResults(result, testNum, passed);
	
	// Test 4
	vitamins.clear();
	fruits.clear();
	answerSize = 3; // answer
	vitamins += "A", "B", "C", "D";
	fruits.push_back(stringToSet("AC"));
	fruits.push_back(stringToSet("BC"));
	fruits.push_back(stringToSet("D"));
	fruits.push_back(stringToSet("CD"));
	

	res = fruitList(vitamins, fruits);
	result = res.size() == answerSize && coversAllVit(vitamins, res, fruits);
	printTestResults(result, testNum, passed);
	
	// Test 5
	vitamins.clear();
	fruits.clear();
	answerSize = 2; // answer
	vitamins += "A", "B", "C", "D", "E";
	fruits.push_back(stringToSet("CD"));
	fruits.push_back(stringToSet("ABD"));
	fruits.push_back(stringToSet("AB"));
	fruits.push_back(stringToSet("AD"));
	fruits.push_back(stringToSet("BCE"));
	

	res = fruitList(vitamins, fruits);
	result = res.size() == answerSize && coversAllVit(vitamins, res, fruits);
	printTestResults(result, testNum, passed);
	
	// Test 6
	vitamins.clear();
	fruits.clear();
	answerSize = 3; // answer
	vitamins += "A", "B", "C", "D", "E", "F";
	fruits.push_back(stringToSet("BC"));
	fruits.push_back(stringToSet("ADE"));
	fruits.push_back(stringToSet("CE"));
	fruits.push_back(stringToSet("BD"));
	fruits.push_back(stringToSet("C"));
	fruits.push_back(stringToSet("AF"));
	
	res = fruitList(vitamins, fruits);
	result = res.size() == answerSize && coversAllVit(vitamins, res, fruits);
	printTestResults(result, testNum, passed);
	
	// Test 7
	vitamins.clear();
	fruits.clear();
	answerSize = 4; // answer
	vitamins += "A", "B", "C", "D", "E", "F", "G";
	fruits.push_back(stringToSet("AE"));
	fruits.push_back(stringToSet("E"));
	fruits.push_back(stringToSet("C"));
	fruits.push_back(stringToSet("BDF"));
	fruits.push_back(stringToSet("AF"));
	fruits.push_back(stringToSet("AC"));
	fruits.push_back(stringToSet("G"));
	
	res = fruitList(vitamins, fruits);
	result = res.size() == answerSize && coversAllVit(vitamins, res, fruits);
	printTestResults(result, testNum, passed);
	
	// Test 8
	vitamins.clear();
	fruits.clear();
	answerSize = 3; // answer
	vitamins += "A", "B", "C", "D", "E", "F", "G", "H";
	fruits.push_back(stringToSet("CEFGH"));
	fruits.push_back(stringToSet("ADH"));
	fruits.push_back(stringToSet("BDFGH"));
	fruits.push_back(stringToSet("EH"));
	fruits.push_back(stringToSet("AG"));
	fruits.push_back(stringToSet("ADGH"));
	fruits.push_back(stringToSet("DH"));
	fruits.push_back(stringToSet("BFGH"));
	
	res = fruitList(vitamins, fruits);
	result = res.size() == answerSize && coversAllVit(vitamins, res, fruits);
	printTestResults(result, testNum, passed);
	
	// Test 9
	vitamins.clear();
	fruits.clear();
	answerSize = 2; // answer
	vitamins += "A", "B", "C", "D", "E", "F", "G", "H", "I";
	fruits.push_back(stringToSet("BEI"));
	fruits.push_back(stringToSet("ACEG"));
	fruits.push_back(stringToSet("ABGH"));
	fruits.push_back(stringToSet("DG"));
	fruits.push_back(stringToSet("BEH"));
	fruits.push_back(stringToSet("BDFHI"));
	fruits.push_back(stringToSet("BGH"));
	fruits.push_back(stringToSet("DFH"));
	fruits.push_back(stringToSet("DF"));
	
	res = fruitList(vitamins, fruits);
	result = res.size() == answerSize && coversAllVit(vitamins, res, fruits);
	printTestResults(result, testNum, passed);
	
	
	// Test 10
	vitamins.clear();
	fruits.clear();
	answerSize = 2; // answer
	vitamins += "A", "B", "C", "D", "E", "F", "G", "H", "I", "J";
	fruits.push_back(stringToSet("AGH"));
	fruits.push_back(stringToSet("CFI"));
	fruits.push_back(stringToSet("CG"));
	fruits.push_back(stringToSet("EF"));
	fruits.push_back(stringToSet("ADGH"));
	fruits.push_back(stringToSet("ABEH"));
	fruits.push_back(stringToSet("AGH"));
	fruits.push_back(stringToSet("I"));
	fruits.push_back(stringToSet("ABCFGJI"));
	fruits.push_back(stringToSet("DEJH"));

	
	res = fruitList(vitamins, fruits);
	result = res.size() == answerSize && coversAllVit(vitamins, res, fruits);
	printTestResults(result, testNum, passed);
	
	// Test 11
	vitamins.clear();
	fruits.clear();
	answerSize = 4; // answer
	vitamins += "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O";
	fruits.push_back(stringToSet("CFHN"));
	fruits.push_back(stringToSet("ADEGHKLM"));
	fruits.push_back(stringToSet("BEHIKMN"));
	fruits.push_back(stringToSet("CDFGKMO"));
	fruits.push_back(stringToSet("ABCFHL"));
	fruits.push_back(stringToSet("BCEFGN"));
	fruits.push_back(stringToSet("DJLMN"));
	fruits.push_back(stringToSet("AFHJ"));
	fruits.push_back(stringToSet("BDFILMNO"));
	fruits.push_back(stringToSet("CGIKMNO"));
	fruits.push_back(stringToSet("EHIO"));
	fruits.push_back(stringToSet("BEHIM"));
	fruits.push_back(stringToSet("BDHILO"));
	
	res = fruitList(vitamins, fruits);
	result = res.size() == answerSize && coversAllVit(vitamins, res, fruits);
	printTestResults(result, testNum, passed);
	
	
	// Test 12
	vitamins.clear();
	fruits.clear();
	answerSize = 6; // answer
	vitamins += "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O";
	fruits.push_back(stringToSet("CEH"));
	fruits.push_back(stringToSet("CFGLO"));
	fruits.push_back(stringToSet("ADHIR"));
	fruits.push_back(stringToSet("ABT"));
	fruits.push_back(stringToSet("CKO"));
	fruits.push_back(stringToSet("FILMOR"));
	fruits.push_back(stringToSet("BDFHIOR"));
	fruits.push_back(stringToSet("JMR"));
	fruits.push_back(stringToSet("BDILOS"));
	fruits.push_back(stringToSet("IJOP"));
	fruits.push_back(stringToSet("DKN"));
	fruits.push_back(stringToSet("CF"));
	fruits.push_back(stringToSet("ABFR"));
	
	res = fruitList(vitamins, fruits);
	result = res.size() == answerSize && coversAllVit(vitamins, res, fruits);
	printTestResults(result, testNum, passed);
	

	cout << "passed: " << passed << endl;
}


int main() {
	setRandomSeed(0);
	testPasscode();
	testVitamins();
	return 0;
}