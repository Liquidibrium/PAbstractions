#include <iostream>
#include <string>
#include <fstream>
#include "simpio.h"
#include "random.h"
#include "console.h"
#include "vector.h"
#include <time.h>
#include "lexicon.h"
#include "ordered_map.h"


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

#define MAP_KEY_MAX_NUM 100

bool mapEquals(OrderedMap &map, Map<int, int> &orig, int maxNum) {
	if (map.size() != orig.size()) {
		return false;
	}
	for (int i=0; i<=maxNum; i++) {
		if (map.containsKey(i) != orig.containsKey(i)) {
			return false;
		}
		if (map.containsKey(i)) {
			if (map.get(i) != orig.get(i)) {
				return false;
			}
		}
	}
	return true;
}
void makeRandomMap(OrderedMap &map, Map<int, int> &orig, 
				   Vector<int> &keyList, int size)  {
	for (int i=0; i<size; i++) {
		int key = randomInteger(0, MAP_KEY_MAX_NUM);
		int value = randomInteger(0, MAP_KEY_MAX_NUM);
		if (!orig.containsKey(key))
			keyList.add(key);
		map.put(key, value);
		orig.put(key, value);
	}
}

bool mapRandomTest(bool withRemove, bool withIter) {
	OrderedMap map;
	Map<int, int> orig;
	Vector<int> keyList;

	makeRandomMap(map, orig, keyList, 100);
	if (!mapEquals(map, orig, MAP_KEY_MAX_NUM)) {
		return false;
	}

	if (withRemove) {
		for (int i=0; i<30; i++) {
			int key = randomInteger(0, MAP_KEY_MAX_NUM);
			map.remove(key);
			orig.remove(key);
		}	
	}

	if (!mapEquals(map, orig, MAP_KEY_MAX_NUM)) {
		return false;
	}

	if (withIter) {
		int indx = keyList.size()-1;
		while (map.hasNext()) {
			int key = map.next();
			//cout << keyList.toString() << endl;
			bool passed = false;
			while (indx >=0) {
				if (keyList[indx] == key) {
					passed = true;
					break;
				}
				indx--;
			}

			if (!passed) {
				return false;
			}
		}
	}
	
	return true;	
}

void runOrderedMapTests() {
	int testNum = 0;
	int passedCounter = 0;
	bool passed;
	
	OrderedMap * map;
	// #1
	map = new OrderedMap;
	map->put(2, 102);
	map->put(1, 101);
	map->put(3, 103);
	passed = map->size() == 3 && map->get(1) == 101	&& 
			map->get(2) == 102 && map->get(3) == 103; 
	printTestResults(passed, testNum, passedCounter);

	// #2
	map = new OrderedMap;
	map->put(2, 102);
	map->put(1, 101);
	map->put(3, 103);
	map->put(3, 203);
	map->put(4, 104);
	passed = map->size() == 4 && map->get(1) == 101	 && 
			map->get(2) == 102 && map->get(3) == 203 && map->get(4) == 104; 
	printTestResults(passed, testNum, passedCounter);

	// #3
	map = new OrderedMap;
	map->put(2, 102);
	map->put(1, 101);
	map->put(3, 103);
	passed = map->size() == 3 && map->containsKey(1) && 
			map->containsKey(2) && map->containsKey(3) &&
			!map->containsKey(0); 
	printTestResults(passed, testNum, passedCounter);

	// #4-20
	setRandomSeed(1);
	for (int i=4; i<=20; i++) {
		printTestResults(mapRandomTest(false, false), testNum, passedCounter);
	}

	// #21 test remove method
	map = new OrderedMap;
	map->put(2, 102);
	map->remove(2);
	passed = map->size() == 0 && !map->containsKey(2); 
	printTestResults(passed, testNum, passedCounter);
	// #22 test remove method
	map = new OrderedMap;
	map->put(2, 102);
	map->put(1, 101);
	map->remove(2);
	map->remove(2);
	passed = map->size() == 1 && !map->containsKey(2) && map->containsKey(1); 
	printTestResults(passed, testNum, passedCounter);
	// #23 - 30
	for (int i=23; i<=30; i++) {
		printTestResults(mapRandomTest(true, false), testNum, passedCounter);
	}
	// #31
	map = new OrderedMap;
	map->put(2, 102);
	map->put(1, 101);
	map->put(4, 104);
	map->put(3, 103);

	passed = map->hasNext() && map->next() == 3 && 
			map->next() == 4 && map->next() == 1 && map->next() == 2;
	printTestResults(passed, testNum, passedCounter);

	// #32
	map = new OrderedMap;
	map->put(2, 102);
	map->put(1, 101);
	map->put(4, 104);
	map->put(3, 103);
	map->put(4, 104);
	map->put(2, 102);
	passed = map->next() == 3 && map->next() == 4 && 
			map->next() == 1 && map->next() == 2;
	printTestResults(passed, testNum, passedCounter);

	// #33
	map = new OrderedMap;
	map->put(2, 102);
	map->put(1, 101);
	map->put(4, 104);
	map->put(3, 103);
	map->put(4, 104);
	map->put(2, 102);
	passed = map->next() == 3 && map->next() == 4 && 
			map->next() == 1 && map->next() == 2;
	printTestResults(passed, testNum, passedCounter);
	
	// #34
	map = new OrderedMap;
	map->put(2, 102);
	map->put(2, 102);
	passed = map->hasNext() && map->next() == 2 && !map->hasNext();
	printTestResults(passed, testNum, passedCounter);

	// #35
	map = new OrderedMap;
	map->put(2, 102);
	map->put(1, 101);
	passed = map->hasNext() && map->next() == 1 && 
			map->hasNext() && map->next() == 2 && !map->hasNext();
	map->resetIterator();
	passed = passed && map->hasNext() && map->next() == 1 && 
			map->hasNext() && map->next() == 2 && !map->hasNext();
	printTestResults(passed, testNum, passedCounter);

	// #36
	map = new OrderedMap;
	map->put(2, 102);
	map->put(1, 101);
	map->put(3, 103);
	passed = map->hasNext() && map->next() == 3 && 
			map->hasNext() && map->next() == 1;
	map->resetIterator();
	passed = passed && map->hasNext() && map->next() == 3 && 
			map->next() == 1 && map->next() == 2 && !map->hasNext();
	printTestResults(passed, testNum, passedCounter);
	// #37
	map = new OrderedMap;
	map->put(2, 102);
	map->put(1, 101);
	map->put(3, 103);
	map->remove(1);
	passed = map->hasNext() && map->next() == 3 && 
			map->hasNext() && map->next() == 2 && !map->hasNext();
	printTestResults(passed, testNum, passedCounter);
	
	for (int i=38; i<=50; i++) {
		printTestResults(mapRandomTest(false, true), testNum, passedCounter);
	}

//	for (int i=46; i<=50; i++) {
//		printTestResults(mapRandomTest(true, true), testNum, passedCounter);
//	}

	cout << "###### passed " << passedCounter << " tests ######" << endl;
}


int main() {
	runOrderedMapTests();
	return 0;
}