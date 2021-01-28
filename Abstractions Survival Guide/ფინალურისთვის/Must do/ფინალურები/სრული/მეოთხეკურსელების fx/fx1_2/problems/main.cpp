#include <iostream>
#include <string>
#include <fstream>
#include "simpio.h"
#include "random.h"
#include "console.h"
#include "vector.h"
#include <time.h>
#include "lexicon.h"
#include "keyboard.h"
#include "connected_graph.h"


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

void generateRandomGraph(Vector<Arc*> &graph, int n) {
	graph.clear();
	int m = (int)(n * 3);
	int i = 0;
	Set<string> arcs;
	while (i < m) {
		int from = randomInteger(0, n-1);
		int to = randomInteger(0, n-1);
		if (from == to) {
			continue;
		}
		string arcS1 = integerToString(from) + string(":") + integerToString(to);
		string arcS2 = integerToString(to) + string(":") + integerToString(from);
		if (arcs.contains(arcS1) || arcs.contains(arcS2)) {
			continue;
		}
		i++;
		arcs.add(arcS1);
		Arc * arc = new Arc;
		arc->from = from;
		arc->to = to;
		arc->dist = randomInteger(1, 30);
		graph.add(arc);
	}
}

void writeGraphInFile(Vector<Arc*> &graph, int n, int answ, int num) {
	ofstream file;
	string fileName = "connected\\test" + integerToString(num) + ".txt";
	file.open(fileName.c_str());
	file << n << " " << graph.size() << " " << answ << endl;
	for (int i=0; i<graph.size(); i++) {
		file << graph[i]->from << " " << graph[i]->to << " " << graph[i]->dist << endl;
	}
	file.close();
}

void runKeyboardTests() {
	int testNum = 0;
	int passedCounter = 0;
	int res;
	Lexicon l("EnglishWords.dat");

	// #1
	res = getAllEncryptionCount("015", l);
	printTestResults(res == 0, testNum, passedCounter);
	// #2
	res = getAllEncryptionCount("105", l);
	printTestResults(res == 0, testNum, passedCounter);
	// #3
	res = getAllEncryptionCount("123", l);
	printTestResults(res == 1, testNum, passedCounter);
	// #4
	res = getAllEncryptionCount("135", l);//ace, 
	printTestResults(res == 2, testNum, passedCounter);
	// #5 
	res = getAllEncryptionCount("255", l);//me
	printTestResults(res == 2, testNum, passedCounter);
	// #6
	res = getAllEncryptionCount("1225", l);//abbe, aby, ave
	printTestResults(res == 3, testNum, passedCounter);
	// #7
	res = getAllEncryptionCount("1415", l);//ado, nae, no
	printTestResults(res == 3, testNum, passedCounter);
	// #8
	res = getAllEncryptionCount("122519", l);//ado, nae, no
	printTestResults(res == 3, testNum, passedCounter);
	// #9
	res = getAllEncryptionCount("191254", l);
	printTestResults(res == 3, testNum, passedCounter);
	// #10
	res = getAllEncryptionCount("211419", l);
	printTestResults(res == 3, testNum, passedCounter);
	// #11
	res = getAllEncryptionCount("112118", l);
	printTestResults(res == 2, testNum, passedCounter);
	// #12
	res = getAllEncryptionCount("161225", l);
	printTestResults(res == 2, testNum, passedCounter);
	// #13
	res = getAllEncryptionCount("315124", l);
	printTestResults(res == 2, testNum, passedCounter);
	// #14
	res = getAllEncryptionCount("139419", l);
	printTestResults(res == 2, testNum, passedCounter);
	// #15
	res = getAllEncryptionCount("131519", l);
	printTestResults(res == 2, testNum, passedCounter);	cout << "###### passed " << passedCounter << " tests ######" << endl;
}

void runMaxRemovedWeight() {
	int testNum = 0;
	int passedCounter = 0;
	for (int i=11; i<=50; i++) {
		Vector<Arc*> graph;
		int n = i + 4;
		int answ = 0;
		readGraphFromFile("connected\\test" + integerToString(i) + ".txt", graph, n, answ);
		//generateRandomGraph(graph, n);
		int res = maxRemovedWeight(graph, n);
		//cout << "sec. min: " << res << endl;
		//writeGraphInFile(graph, n, res, i);
		printTestResults(res == answ, testNum, passedCounter);
	}
	cout << "###### passed " << passedCounter << " tests ######" << endl;
}

int main() {
	runKeyboardTests();
	runMaxRemovedWeight();

	return 0;
}