#include "sec_min_spanning_tree.h"
#include "strlib.h"
#include "pqueue.h"
#include "map.h"
#include "vector.h"
#include "set.h"
Vector<int> djkistra(Vector<Arc*> graph, const int n);
Map<int, Vector<int>> createAvailableNodes(Vector<Arc*> graph, const int n);
int findPriotity(int from, int to, Vector<Arc*> graph);

int findSecondMinSpanningTree(Vector<Arc*> graph, const int n) {
	
	return 0;
}

Vector<int> djkistra(Vector<Arc*> graph, const int n) {
	PriorityQueue<int> pqueue;
	Vector<int> path;
	Set<int> been;
	Map<int, Vector<int>> availNodes = createAvailableNodes(graph, n);
	int cur = graph[0]->from;
	pqueue.enqueue(cur, 0);
	while (!pqueue.isEmpty()) {
		cur = pqueue.dequeue();
		if (!been.contains(cur)) {
			been.add(cur);
			foreach (int next in availNodes[cur]) {
				path.add(next);
				int prior = findPriotity(cur, next, graph);
				pqueue.enqueue(next, prior);
			}
		}
	}
	return path;
}

Map<int, Vector<int>> createAvailableNodes(Vector<Arc*> graph, const int n) {
	Map<int, Vector<int>> availNodes;
	for (int i = 0; i < n; i++) {
		for (int i = 0; i < graph.size(); i++) {
			if (graph[i]->from == i)
				availNodes[graph[i]->from].add(graph[i]->to);
		}
	}
	return availNodes;
}

int findPriotity(int from, int to, Vector<Arc*> graph) {
	for (int i = 0; i < graph.size(); i++) {
		if (graph[i]->from == from && graph[i]->to == to) {
			return graph[i]->dist;
		}
	}
	return -1;
}