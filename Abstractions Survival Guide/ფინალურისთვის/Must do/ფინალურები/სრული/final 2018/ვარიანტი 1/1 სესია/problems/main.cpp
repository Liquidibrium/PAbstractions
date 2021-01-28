#include <iostream>
#include "common.h"
#include <string>
#include <fstream>
#include "simpio.h"
#include "random.h"
#include "console.h"
#include "vector.h"
#include <time.h>
#include "lexicon.h"
#include "cache_map.h"


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

void readGraphFromFile(string fileName, Vector<Arc*> &graph, int &n, int &answ) {
	graph.clear();
	ifstream ifile;
	ifile.open(fileName.c_str());
	int m;
	ifile >> n >> m >> answ;
	for (int i=0; i<m; i++) {
		Arc * arc = new Arc;
		ifile >> arc->from >> arc->to >> arc->dist; 
		graph.add(arc);
	}
	ifile.close();
}

void fillMaps(CacheMap &map, Map<int, int> &mapOriginal, int num) {
	for (int i=0; i<num; i++) {
		int key = randomInteger(0, 100);
		int value = randomInteger(0, 100);
		map.put(key, value);
		mapOriginal.put(key, value);
	}
}

bool mapEquals(CacheMap &map, Map<int, int> &mapOriginal, int maxNum) {
	for (int i=0; i<maxNum; i++) {
		if (map.containsKey(i) != mapOriginal.containsKey(i)) {
			return false;
		}
		if (map.containsKey(i)) {
			if (map.get(i) != mapOriginal.get(i)) {
				return false;
			}
		}
	}
	return true;
}

bool mapRandomTest(int cacheSize = 1000) {
	CacheMap map(cacheSize);
	Map<int, int> mapOriginal;

	fillMaps(map, mapOriginal, 500);

	if (map.size() != mapOriginal.size()) {
		return false;
	}
	
	return mapEquals(map, mapOriginal, 110);
}

bool mapRemoveRandomTest(int cacheSize = 1000) {
	CacheMap map(1000);
	Map<int, int> mapOriginal;

	fillMaps(map, mapOriginal, 100);

	if (map.size() != mapOriginal.size()) {
		return false;
	}
	for (int i=0; i<20; i++) {
		int key = randomInteger(0, 100);
		map.remove(key);
		mapOriginal.remove(key);
	}


	return mapEquals(map, mapOriginal, 110);
}

bool mapCacheRandomTest(int cacheSize = 1000) {
	int maxVal = 300;
	CacheMap map(cacheSize);
	Map<int, int> mapOriginal;
	int num = 80;
	for (int i=0; i<num; i++) {
		int key = randomInteger(0, maxVal);
		int value = randomInteger(0, maxVal);
		if (map.containsKey(key)) {
			i--;
			continue;
		}
		map.put(key, value);
		if (num - i <= cacheSize){
			mapOriginal.put(key, value);
		}
	}
	return mapEquals(map, mapOriginal, maxVal);
}

void runCacheMapTests() {
	int testNum = 0;
	int passedCounter = 0;
	bool passed;
	
	CacheMap * map;
	// #1
	map = new CacheMap(100);
	map->put(2, 102);
	map->put(1, 101);
	map->put(3, 103);
	passed = map->size() == 3 && map->get(1) == 101	&& 
			map->get(2) == 102 && map->get(3) == 103; 
	printTestResults(passed, testNum, passedCounter);

	// #2
	map = new CacheMap(100);
	map->put(2, 102);
	map->put(1, 101);
	map->put(3, 103);
	map->put(3, 203);
	map->put(4, 104);
	passed = map->size() == 4 && map->get(1) == 101	 && 
			map->get(2) == 102 && map->get(3) == 203 && map->get(4) == 104; 
	printTestResults(passed, testNum, passedCounter);

	// #3
	map = new CacheMap(100);
	map->put(2, 102);
	map->put(1, 101);
	map->put(3, 103);
	passed = map->size() == 3 && map->containsKey(1) && 
			map->containsKey(2) && map->containsKey(3) &&
			!map->containsKey(0); 
	printTestResults(passed, testNum, passedCounter);

	// #4-20
	setRandomSeed(1);
	for (int i=0; i<17; i++) {
		printTestResults(mapRandomTest(1000), testNum, passedCounter);
	}

	// #21 test remove method
	map = new CacheMap(100);
	map->put(2, 102);
	map->remove(2);
	passed = map->size() == 0 && !map->containsKey(2); 
	printTestResults(passed, testNum, passedCounter);
	// #22 test remove method
	map = new CacheMap(100);
	map->put(2, 102);
	map->put(1, 101);
	map->remove(2);
	passed = map->size() == 1 && !map->containsKey(2) && map->containsKey(1); 
	printTestResults(passed, testNum, passedCounter);
	// #23 test remove method
	map = new CacheMap(100);
	map->put(2, 102);
	map->put(1, 101);
	map->remove(1);
	passed = map->size() == 1 && map->containsKey(2) && !map->containsKey(1); 
	printTestResults(passed, testNum, passedCounter);
	// #24 test remove method
	map = new CacheMap(100);
	map->put(2, 102);
	map->put(1, 101);
	map->put(3, 101);
	map->remove(2);
	map->remove(2);
	passed = map->size() == 2 && !map->containsKey(2);
	map->remove(3);
	passed = passed && !map->containsKey(3);
	map->remove(1);
	passed = passed && map->size() == 0 && !map->containsKey(1); 
	printTestResults(passed, testNum, passedCounter);
	// #25 test remove method
	map = new CacheMap(100);
	map->put(20, 120);
	map->put(10, 110);
	map->put(30, 130);
	map->put(40, 140);
	map->put(50, 150);
	map->put(60, 160);
	map->put(35, 135);
	map->put(38, 138);
	map->put(34, 134);
	map->put(32, 132);
	map->put(31, 131);
	map->put(25, 125);
	map->put(24, 124);
	map->put(23, 123);
	map->put(28, 128);
	map->remove(30);
	passed = map->size() == 14 && !map->containsKey(30) && 
			 map->containsKey(31);
	map->remove(50);
	passed = passed && map->size() == 13 && !map->containsKey(50);
	map->remove(20);
	passed = passed && map->size() == 12 && !map->containsKey(50);
	printTestResults(passed, testNum, passedCounter);

	//53, 37, 91, 9, 69, 6, 24, 46, 53
	map = new CacheMap(100);
	map->put(53, 153);
	map->put(37, 137);
	map->put(91, 191);
	map->put(9, 109);
	map->put(69, 169);
	map->put(6, 106);
	map->put(24, 124);
	map->put(46, 146);
	map->put(85, 153);
	map->remove(53);
	passed = map->size() == 8 && !map->containsKey(53) && 
			map->containsKey(85);
	printTestResults(passed, testNum, passedCounter);

	// #27 - 60
	for (int i=26; i<60; i++) {
		printTestResults(mapRemoveRandomTest(), testNum, passedCounter);
	}

	// test cache
	// # 61
	map = new CacheMap(2);
	map->put(2, 102);
	map->put(1, 101);
	map->put(3, 103);
	map->put(3, 104);
	passed = map->size() == 2 && !map->containsKey(2) &&
			map->containsKey(1) && map->containsKey(3); 
	printTestResults(passed, testNum, passedCounter);
	// # 62
	map = new CacheMap(2);
	map->put(2, 102);
	map->put(1, 101);
	map->put(3, 103);
	map->put(8, 108);
	map->put(4, 104);
	passed = map->size() == 2 && !map->containsKey(2) &&
			!map->containsKey(1) && !map->containsKey(3) && 	
			map->containsKey(8) && map->containsKey(4); 
	printTestResults(passed, testNum, passedCounter);
	// #63 - 100
	for (int i=63; i<=100; i++) {
		printTestResults(mapCacheRandomTest(10), testNum, passedCounter);
	}

	cout << "###### passed " << passedCounter << " tests ######" << endl;
}


int main() {
	runCacheMapTests();
	return 0;
}