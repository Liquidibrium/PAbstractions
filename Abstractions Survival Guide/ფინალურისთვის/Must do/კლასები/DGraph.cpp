#include "DGraph.h"

DGraph::DGraph(int numVertices) {
	vertices = new Set<int>[numVertices];
	nVertices = numVertices;
	nEdges = 0;
}

DGraph::~DGraph() {
	delete[] vertices;
}

int DGraph::numVertices() {
	return nVertices;
}

int DGraph::numEdges() {
	return nEdges;
}

void DGraph::addEdge(int from, int to) {
	if (!hasEdge(from, to)) {
		vertices[from].add(to);
		nEdges++;
	}
}

void DGraph::removeEdge(int from, int to) {
	if (hasEdge(from, to)) {
		vertices[from].remove(to);
		nEdges--;
	}
}

bool DGraph::hasEdge(int from, int to) {
	return vertices[from].contains(to);
}

bool DGraph::recHasPath(int from, int to, Set<int>& visited) {
	if (from == to)
		return true;

	visited.add(from);
	foreach (int next in vertices[from]) {
		if (!visited.contains(next))
			if (recHasPath(next, to, visited))
				return true;
	}
	visited.remove(from);
	return false;
}

bool DGraph::hasPath(int from, int to) {
	Set<int> visited;
	return recHasPath(from, to, visited);
}

int DGraph::distance(int from, int to) {
	int d;

	Queue<int> bfsQueue;
	Set<int> visited;

	bfsQueue.enqueue(from);
	visited.add(from);


	//while(!bfsQueue.isEmpty()){
	//	int k = bfsQueue.size();
	//	for(int i = 0 ; i < k; i++){
	//		int curr = bfsQueue.dequeue();
	//		if(curr == to) return d;
	//		foreach(int v in vertices[curr]){
	//			if(!visited.contains(v)){
	//				bfsQueue.enqueue(v);
	//				visited.add(v);
	//			}
	//		}
	//	}
	//	d++;
	//}

	for (d=0; true; d++) {
		Queue<int> nextQueue;
		while (!bfsQueue.isEmpty()) {
			int curVert = bfsQueue.dequeue();
			if (curVert == to)
				return d;
			foreach (int nextVert in vertices[curVert]) {
				if (!visited.contains(nextVert)) {
					nextQueue.enqueue(nextVert);
					visited.add(nextVert);
				}
			}
		}
		bfsQueue = nextQueue;
	}

	return d;
}

int DGraph::numComponents() {
	int res = 0;
	Set<int> visited;
	for (int i = 0; i < numVertices(); i++) {
		if (!visited.contains(i)) {
			checkComponent(i, visited);
			res++;
		}
	}
	return res;
}

void DGraph::checkComponent(int v, Set<int> &visited) {
	if (!visited.contains(v)) {
		visited.add(v);
		foreach (int vertex in vertices[v])
			checkComponent(vertex, visited);
	}
}