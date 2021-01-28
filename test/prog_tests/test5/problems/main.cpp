#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
#include "vector.h"
#include "queue.h"
#include <time.h>
#include "lexicon.h"
#include "LangRank.h"


using namespace std;

void printTestResults(bool passed, int testNum, int & passedCounter) {
	if (passed) {
		cout << "test " << testNum << " passed" << endl;
		passedCounter++;
	} else {
		cout << "test " << testNum << " failed" << endl;
	}
}

void fillGrid(Grid<char> &g, string s) {
	int x = 0;
	int y = 0;
	for (int i=0; i<s.length(); i++) {
		if (s[i] == ',') {
			y = 0;
			x++;
			continue;
		}
		g[x][y] = s[i];
		y++;
	}
}

bool runLangRankTest(int testNum) {
	Grid<char> grid;
	Map<char, int> res;

	switch (testNum) {
	case 1:
		grid.resize(2, 2);
		fillGrid(grid, "aa,aa");
		res = getLangRanks(grid);
		return res.size() == 1 && res['a'] == 1;
	
	case 2:
		grid.resize(2, 2);
		fillGrid(grid, "ab,ba");
		res = getLangRanks(grid);
		return (res.size() == 2 && 
				res['b'] == 2 && res['a'] == 2);

	case 3:
		grid.resize(2, 2);
		fillGrid(grid, "aa,bb");
		res = getLangRanks(grid);
		return (res.size() == 2 && res['b'] == 1 && res['a'] == 1);

	case 4:
		grid.resize(4, 8);
		fillGrid(grid, "ttuuttdd,ttuuttdd,uuttuudd,uuttuudd");
		res = getLangRanks(grid);
		
		return (res.size() == 3 &&  res['t'] == 3 && res['u'] == 3 && res['d'] == 1);

	case 5:
		grid.resize(9, 9);
		fillGrid(grid, "bbbbbbbbb,aaaaaaaab,bbbbbbbab,baaaaacab,bacccccab,bacbbbcab,bacccccab,baaaaaaab,bbbbbbbbb");
		res = getLangRanks(grid);
		return (res.size() == 3 && res['b'] == 2 && res['a'] == 1 && res['c'] == 1);
	case 6:
		grid.resize(16, 19);
		fillGrid(grid, "abaaaaabaaaaaaaaaaa,abaaaabbaaaaaaaaaaa,abbbbbaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaabaaaaaaaaaaaaa,aaaaaabaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa");
		res = getLangRanks(grid);
		return (res.size() == 2 && res['b'] == 4 && res['a'] == 2);
	case 7:
		grid.resize(16, 19);
		fillGrid(grid, "abaaaaabaaaaaaaaaaa,abaaaabbaaaaaaaaaaa,abbbbbaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaabaaaaaaaaaaaaa,aaaaaabaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaakaaaaaaaaaaaa,aaaaakakaaaaaaaaaaa,aaaaaakaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa");
		res = getLangRanks(grid);
		return (res.size() == 3 && res['b'] == 4 && res['a'] == 3 && res['k'] == 4);
	case 8:
		grid.resize(16, 19);
		fillGrid(grid, "abaaaaabaaaaaaaaaaa,abaaaabbaaaaaaaaaaa,abbbbbaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaabaaaaaaaaaaaaa,aaaaaabaaaaaaaaaaaa,aaaaaakkkkaaaaaaaaa,aaaaaakaakkkaaaaaaa,aaaaakakaaakaaaaaaa,aaaaaakaaaakaaaaaaa,aaaaaakkkkkkaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa,aaaaaaaaaaaaaaaaaaa");
		res = getLangRanks(grid);
		return (res.size() == 3 && res['b'] == 4 && res['a'] == 4 && res['k'] == 3);
	case 9:
		grid.resize(1, 21);
		fillGrid(grid, "ababababababababababa");
		res = getLangRanks(grid);
		return (res.size() == 2 && res['b'] == 10 && res['a'] == 11);
	case 10:
		grid.resize(20, 1);
		fillGrid(grid, "a,b,a,b,a,b,a,b,a,b,a,b,a,b,a,b,a,b,a,b");
		res = getLangRanks(grid);
		return (res.size() == 2 && res['b'] == 10 && res['a'] == 10);

	}
	return false;
}

const int langRankTestsNum = 10;

void runLangRankTests() {
	cout << "### Run Lang Rank tests ###" << endl;
	int passedNum = 0;
	int testNum = 1;

	for (; testNum<=langRankTestsNum; testNum++) {
		bool res = runLangRankTest(testNum);
		printTestResults(res, testNum, passedNum);
	}

	cout << "###### passed " << passedNum << " tests ######" << endl;
}

int main() {
	runLangRankTests();
	return 0;
}