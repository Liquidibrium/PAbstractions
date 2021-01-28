#include <iostream>
#include <string>
#include <fstream>
#include "simpio.h"
#include "random.h"
#include "console.h"
#include "vector.h"
#include <time.h>
#include "lexicon.h"
#include "graph.h"


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

Set<string> addRandomNodes(Graph * g, int n) {
	Set<string> nodes;
	for (int i=0; i<n; i++) {
		g->addNode(integerToString(i));
		nodes.add(integerToString(i));
	}
	for (int i=0; i<n/2; i++) {
		g->addNode(integerToString(i));
		nodes.add(integerToString(i));
	}
	return nodes;
}

Map<string, int> addRandomArcs(Graph * g) {
	int arcNum = randomInteger(g->size(), 3*g->size());
	Map<string, int> arcs;
	for (int i=0; i<arcNum; i++) {
		string from = integerToString(randomInteger(0, g->size()));
		string to = integerToString(randomInteger(0, g->size()));
		int w = randomInteger(1, 100);

		bool b = g->addArc(from, to, w);
		if (b) {
			arcs.put(":" + from + ">" + to + ":",  w);
		}
	}
	return arcs;
}

Set<string> graphNodes(Graph * g) {
	Set<string> nodes;
	string * elems = g->getNodes();
	for (int i=0; i<g->size(); i++) {
		nodes.add(elems[i]);
	}
	return nodes;
}

bool graphEquals(Graph * g, Set<string> nodes, Map<string, int> arcs) {
	Set<string> res = graphNodes(g);
	if (nodes != res) {
		return false;
	}
	for (int i=0; i<g->size(); i++) {
		for (int j=0; j<g->size(); j++) {
			string from = integerToString(i);
			string to = integerToString(j);
			int w = g->getArcWeight(from, to);
			string key = ":" + from + ">" + to + ":";
			if (w == -1 && arcs.containsKey(key) || 
				w != -1 && !arcs.containsKey(key)) {
				return false;
			} 
			if (arcs.containsKey(key) && w != arcs.get(key)) {
				return false;
			} 
		}
	}
	return true;
}
bool graphNodeAddTests() {
	int n = randomInteger(10, 100);
	Graph * g = new Graph();
	Set<string> nodes = addRandomNodes(g, n);

	Set<string> res = graphNodes(g);
	return nodes == res;
}

bool graphArcAddTests() {
	int n = randomInteger(100, 200);
	Graph * g = new Graph();
	Set<string> nodes = addRandomNodes(g, n);
	Map<string, int> arcs = addRandomArcs(g);
	return graphEquals(g, nodes, arcs);
}

bool graphNodeRemoveTests(bool graphWithArcs) {
	int n = randomInteger(10, 100);
	Graph * g = new Graph();
	Set<string> nodes = addRandomNodes(g, n);
	Map<string, int> arcs;
	
	//add arcs to graph
	if (graphWithArcs) {
		arcs = addRandomArcs(g);
	}

	//remove random nodes
	for (int i=0; i<n; i++) {
		if (randomChance(0.7)) {
			string node = integerToString(i);
			g->removeNode(node);
			nodes.remove(node);

			//remove all arcs connected to node
			if (graphWithArcs) {
				foreach (string key in arcs) {
					if (key.find(":" + node + ">") != string::npos || 
						key.find(">" + node + ":") != string::npos) {
							arcs.remove(key);
					}
				}
			}
		}
	}

	return graphEquals(g, nodes, arcs);
}

bool graphArcRemoveTests() {
	int n = randomInteger(10, 100);
	Graph * g = new Graph();
	Set<string> nodes = addRandomNodes(g, n);
	Map<string, int> arcs = addRandomArcs(g);
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if (randomChance(0.3)) {
				continue;
			}
			string from = integerToString(i);
			string to = integerToString(j);
			g->removeArc(from, to);
			arcs.remove(":" + from + ">" + to + ":");
		}
	}
	return graphEquals(g, nodes, arcs);;
}

bool graphConnectionsTests() {
	int n = randomInteger(10, 100);
	Graph * g = new Graph();
	Set<string> nodes = addRandomNodes(g, n);
	Map<string, int> arcs = addRandomArcs(g);

	for (int i=0; i<n; i++) {
		string from = integerToString(i);
		int size = g->getConnectedNodesCount(from);
		string * arr = g->getConnectedNodes(from);
		
		int count = 0;
		foreach (string key in arcs) {
			if (key.find(":" + from + ">") != string::npos) {
				count++;
			}
		}
		
		if (count != size) {
			return false;
		}
		for (int j=0; j<size; j++) {
			if (g->getArcWeight(from, arr[j]) == -1 || 
				!arcs.containsKey(":" + from + ">" + arr[j] + ":")) {
				return false;
			}
		}
	}
	return true;
}

void runGraphTests() {
	int testNum = 0;
	int passedCounter = 0;
	bool passed;
	
	Graph * g;
	// #1
	g = new Graph();
	passed = g->size() == 0;
	printTestResults(passed, testNum, passedCounter);
	// #2
	g = new Graph();
	g->addNode("1");
	passed = g->size() == 1 && g->getNodes()[0] == "1";
	printTestResults(passed, testNum, passedCounter);
	// #3
	g = new Graph();
	g->addNode("1");
	g->addNode("1");
	g->addNode("1");
	passed = g->size() == 1 && *g->getNodes() == "1";
	printTestResults(passed, testNum, passedCounter);
	// #4-10
	for (int i=4; i<=10; i++) {
		printTestResults(graphNodeAddTests(), testNum, passedCounter);
	}
	// #11
	g = new Graph();
	g->addNode("1");
	g->addNode("2");
	g->addArc("1", "2", 10);
	g->addArc("1", "3", 15);
	passed = g->size() == 2 && g->getArcWeight("1", "2") == 10 &&
			g->getArcWeight("2", "1") == -1 && g->getArcWeight("1", "3") == -1;
	printTestResults(passed, testNum, passedCounter);
	for (int i=12; i<=20; i++) {
		printTestResults(graphArcAddTests(), testNum, passedCounter);
	}	
	// #remove node tests
	// #21 
	g = new Graph();
	g->addNode("1");
	g->removeNode("1");
	passed = g->size() == 0 && g->getNodes() == NULL;
	printTestResults(passed, testNum, passedCounter);
	// #22
	g = new Graph();
	g->addNode("1");
	g->removeNode("1");
	g->addNode("2");
	g->addNode("2");
	g->addNode("3");
	g->addNode("4");
	g->removeNode("4");
	g->removeNode("4");
	g->removeNode("2");
	passed = g->size() == 1 && *g->getNodes() == "3";
	printTestResults(passed, testNum, passedCounter);
	// #23-30
	for (int i=23; i<=30; i++) {
		printTestResults(graphNodeRemoveTests(false), testNum, passedCounter);
	}
	// #remove arc tests
	// #31
	g = new Graph();
	g->addNode("1");
	g->addNode("2");
	g->addNode("3");
	g->addArc("1", "3", 10);
	g->addArc("2", "3", 11);
	g->addArc("1", "2", 12);
	g->removeArc("1", "2");
	g->removeArc("1", "3");
	passed = g->size() == 3 && g->getArcWeight("1", "2") == -1 && 
			g->getArcWeight("1", "3") == -1 && g->getArcWeight("2", "3") == 11;
	printTestResults(passed, testNum, passedCounter);
	for (int i=32; i<=40; i++) {
		printTestResults(graphArcRemoveTests(), testNum, passedCounter);
	}
	// #41
	g = new Graph();
	g->addNode("1");
	g->addNode("2");
	g->addNode("3");
	g->addArc("1", "3", 13);
	g->addArc("3", "1", 31);
	g->addArc("2", "3", 23);
	g->addArc("1", "2", 12);
	g->removeNode("1");
	passed = g->size() == 2 && g->getArcWeight("2", "3") == 23 && 
			g->getArcWeight("1", "3") == -1 && g->getArcWeight("1", "2") == -1;
	printTestResults(passed, testNum, passedCounter);
	for (int i=42; i<=50; i++) {
		printTestResults(graphNodeRemoveTests(true), testNum, passedCounter);
	}
	// #remove getConnectedNodes
	// #51
	g = new Graph();
	g->addNode("1");
	g->addNode("2");
	g->addNode("3");
	g->addArc("1", "3", 13);
	g->addArc("3", "1", 31);
	g->addArc("2", "3", 23);
	g->addArc("1", "2", 12);
	passed = g->size() == 3 && g->getConnectedNodesCount("1") == 2 &&
		g->getConnectedNodesCount("2") == 1 && g->getConnectedNodes("2")[0] == "3" &&
		g->getConnectedNodesCount("3") == 1 && g->getConnectedNodes("3")[0] == "1";
	printTestResults(passed, testNum, passedCounter);
	for (int i=52; i<=60; i++) {
		printTestResults(graphConnectionsTests(), testNum, passedCounter);
	}
	cout << "###### passed " << passedCounter << " tests ######" << endl;
}


int main() {
	setRandomSeed(0);
	runGraphTests();
	return 0;
}