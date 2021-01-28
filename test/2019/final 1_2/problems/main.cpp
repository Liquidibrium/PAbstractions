#include <iostream>
#include <string>
#include <fstream>
#include "simpio.h"
#include "random.h"
#include "console.h"
#include "foreach.h"
#include <time.h>
#include "lexicon.h"
#include "Vector.h"
#include "chunkvector.h"

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

void testChunkVector() {
	cout << "### Testing Cycle ###" << endl;
	int testNum = 0;
	int passed = 0;
	bool b;
	ChunkVector *v;
	//#1
	v = new ChunkVector;
	v->add(1);
	printTestResults(v->size() == 1 && 
					v->getChunkNumber() == 1 && 
					v->get(0) == 1, 
					testNum, passed);
	//#2
	v = new ChunkVector;
	v->add(1);
	v->add(2);
	v->add(3);
	printTestResults(v->size() == 3 && 
					v->getChunkNumber() == 1 && 
					v->get(0) == 1 && 
					v->get(1) == 2 && 
					v->get(2) == 3, 
					testNum, passed);
	//#3
	v = new ChunkVector;
	v->add(1);
	v->add(2);
	v->add(3);
	v->add(4);
	printTestResults(v->size() == 4 && 
					v->getChunkNumber() == 2 && 
					v->get(0) == 1 && 
					v->get(1) == 2 && 
					v->get(2) == 3 && 
					v->get(3) == 4, 
					testNum, passed);
	//#4
	v = new ChunkVector;
	v->add(1);
	v->remove(0);
	printTestResults(v->size() == 0 && 
					v->getChunkNumber() == 0, 
					testNum, passed);
	//#5
	v = new ChunkVector;
	v->add(1);
	v->add(2);
	v->add(3);
	v->add(4);
	v->remove(0);
	printTestResults(v->size() == 3 && 
					v->getChunkNumber() == 2 &&
					v->get(0) == 2 && 
					v->get(1) == 3 && 
					v->get(2) == 4,
					testNum, passed);
	//#6
	v = new ChunkVector;
	v->add(1);
	v->add(2);
	v->add(3);
	v->add(4);
	v->remove(0);
	v->remove(0);
	printTestResults(v->size() == 2 && 
					v->getChunkNumber() == 1 &&
					v->get(0) == 3 && v->get(1) == 4,
					testNum, passed);
	//#7
	v = new ChunkVector;
	v->add(1);
	v->add(2);
	v->add(3);
	v->add(4);
	b = v->size() == 4 && v->getChunkNumber() == 2;
	v->remove(3);
	v->remove(2);
	printTestResults(b && 
					v->size() == 2 && 
					v->getChunkNumber() == 1 &&
					v->get(0) == 1 && 
					v->get(1) == 2,
					testNum, passed);
	//#8
	v = new ChunkVector;
	v->add(1);
	v->add(2);
	v->add(3);
	v->add(4);
	v->add(5);
	v->add(6);
	v->add(7);
	v->add(8);
	b = v->size() == 8 && v->getChunkNumber() == 4;
	v->remove(7);
	v->remove(4);
	v->remove(4);
	b = b && v->size() == 5 && v->getChunkNumber() == 3;
	printTestResults(b && 
					v->get(0) == 1 && 
					v->get(1) == 2 && 
					v->get(2) == 3 && 
					v->get(3) == 4 && 
					v->get(4) == 7,
					testNum, passed);
	//#9
	v = new ChunkVector;
	v->add(1);
	v->add(2);
	v->add(3);
	v->add(4);
	v->add(5);
	v->add(6);
	v->add(7);
	v->add(8);
	b = v->size() == 8 && v->getChunkNumber() == 4;
	v->remove(7);
	v->remove(4);
	v->remove(2);
	v->remove(2);
	b = b && v->size() == 4 && 
			v->getChunkNumber() == 3;
	printTestResults(b && 
					v->get(0) == 1 && 
					v->get(1) == 2 && 
					v->get(2) == 6 && 
					v->get(3) == 7,
					testNum, passed);
	//#10
	v = new ChunkVector;
	v->add(1);
	v->add(2);
	v->add(3);
	v->add(4);
	v->add(5);
	v->add(6);
	v->add(7);
	v->add(8);
	b = v->size() == 8 && v->getChunkNumber() == 4;
	v->remove(0);
	v->remove(1);
	v->remove(1);
	v->remove(2);
	b = b && v->size() == 4 && v->getChunkNumber() == 3;
	printTestResults(b && 
					v->get(0) == 2 && 
					v->get(1) == 5 && 
					v->get(2) == 7 && 
					v->get(3) == 8,
					testNum, passed);

	//#11
	v = new ChunkVector;
	v->insert(0, 6);
	v->insert(0, 5);
	v->insert(0, 4);
	b = v->get(0) == 4 && v->get(1) == 5 && v->get(2) == 6;
	printTestResults(b && 
					v->getChunkNumber() == 1,
					testNum, passed);
	//#12
	v = new ChunkVector;
	v->insert(0, 6);
	v->insert(0, 5);
	v->insert(0, 4);
	v->insert(0, 3);
	v->insert(3, 2);
	v->insert(4, 1);
	v->insert(5, 0);
	b = v->get(0) == 3 && v->get(1) == 4 && 
			v->get(2) == 5 && v->get(3) == 2 && 
			v->get(4) == 1 && v->get(5) == 0 && 
			v->get(6) == 6;
	printTestResults(b && 
					v->getChunkNumber() == 3,
					testNum, passed);
	//#13
	v = new ChunkVector;
	v->insert(0, 0);
	v->insert(1, 2);
	v->insert(1, 1);
	v->insert(0, 5);
	v->insert(4, 6);
	v->insert(4, 7);
	v->insert(6, 8);
	v->insert(5, 9);
	v->insert(5, 10);
	v->remove(3);
	v->remove(1);
	v->remove(6);
	b = v->get(0) == 5 && v->get(1) == 1 && 
			v->get(2) == 7 && v->get(3) == 10 && 
			v->get(4) == 9 && v->get(5) == 6;
	printTestResults(b && 
					v->getChunkNumber() == 3,
					testNum, passed);

	cout << "passed: " << passed << endl;	
}

int main() {
	setRandomSeed(0);
	testChunkVector();
	return 0;
}