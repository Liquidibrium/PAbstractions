
#ifndef DGPRAH_H_
#define DGPRAH_H_

#define INCREASE_SIZE_ 10

#include "set.h"
#include "queue.h"

class DGraph
{
private:
	int nVertices;
	int nEdges;
	Set<int>* vertices;
	bool recHasPath(int from, int to, Set<int>& visited);
	void checkComponent(int v, Set<int> &visited);

public:
	DGraph(int numVertices);
	~DGraph();
	int numVertices();
	int numEdges();
	void addEdge(int from, int to);
	void removeEdge(int from, int to);
	bool hasEdge(int from, int to);
	bool hasPath(int from, int to);
	int distance(int from, int to);
	int numComponents(); // undirected graph
};

#endif
