
#include <iostream>
#include <utility>
#include "vector.h"
#include "pqueue.h"
#include "map.h"
#include "set.h"
#include "grid.h"
#include "queue.h"
using namespace std;

struct Arc {
	int from;
	int to;
	int cost;
};

struct Node {
	int color;
	int distance;
	int parent;
	Set<int> neighbors;
};

Vector<int> getPath(int from, int to, Map<int, Node> &data) {
	Vector<int> path;
	int cur = to;
	while (cur != -1) {
		path.add(cur);
		cur = data[cur].parent;
	}
	for (int i = 0; i < path.size() / 2; i++) {
		int tmp = path[i];
		path[i] = path[path.size() - 1 - i];
		path[path.size() - 1 - i] = tmp;
	}
	return path;
}

Vector<int> shortestPath(int from, int to, Vector<Arc*> graph) {

	Map<int, Node> data;
	Map<pair<int,int>, int> weights;
	for (int i = 0; i < graph.size(); i++) {
		data[graph[i]->from].color = 0;
		data[graph[i]->to].color = 0;
		data[graph[i]->from].neighbors.add(graph[i]->to);
		weights[make_pair(graph[i]->from, graph[i]->to)] = graph[i]->cost;
	}

	data[from].distance = 0;
	data[from].parent = -1;
	PriorityQueue<int> pq;
	pq.enqueue(from, 0);

	while (!pq.isEmpty()) {
		int cur = pq.dequeue();
		if (cur == to) return getPath(from, to, data);
		data[cur].color = 2;
		foreach (int n in data[cur].neighbors) {
			int total_distance = data[cur].distance +
				weights[make_pair(cur, n)];
			if (data[n].color == 0) {
				data[n].color = 1;
				data[n].distance = total_distance;
				data[n].parent = cur;
				pq.enqueue(n, total_distance);
			}
			else if (data[n].color == 1
					  && data[n].distance > total_distance) {
				data[n].distance = total_distance;
				data[n].parent = cur;
				pq.enqueue(n, total_distance);
			}
		}
	}

	return Vector<int>();
}

Vector<Arc*> MST(Vector<Arc*> graph, int n) {
	Vector<Arc*> mst;
	Map<int, Set<int> > data;
	for (int i = 0; i < n; i++)
		data[i].add(i);
	PriorityQueue<Arc*> pq;
	for (int j = 0; j < graph.size(); j++)
		pq.enqueue(graph[j], graph[j]->cost);
	int numClusters = n;
	while (numClusters > 1) {
		if (pq.isEmpty()) return Vector<Arc*>();
		Arc* arc = pq.dequeue();
		if (data[arc->from] != data[arc->to]) {
			Set<int> combined = data[arc->from] + data[arc->to];
			foreach (int v in combined)
				data[v] = combined;
			mst.add(arc);
			numClusters--;
		} /* else remaining.add(arc); */
	}
	/* while (!pq.isEmpty()) remaining.add(pq.dequeue()); */
	return mst;
}

int hopCount(int from, int to, Grid<bool> graph) {
	Queue<int> q;
	Set<int> been;
	int result = 0;
	while (!q.isEmpty()) {
		Queue<int> next_q;
		while (!q.isEmpty()) {
			int cur = q.dequeue();
			if (cur == to) return result;
			for (int i = 0; i < graph.numCols(); i++) {
				if (graph[cur][i] && !been.contains(i)) {
					been.add(i);
					next_q.enqueue(i);
				}
			}
		}
		q = next_q;
		result++;
	}
	return -1;
}

struct Tree {
	int value;
	Vector<Tree*> children;
};

void reflectBreadth	(Vector<Tree*> &breadth) {
	for (int i = 0; i < breadth.size() / 2; i++) {
		int tmp = breadth[i]->value;
		breadth[i]->value = breadth[breadth.size() - 1 - i]->value;
		breadth[breadth.size() - 1 - i]->value = tmp;
	}
}

void reflectTree (Tree* t) {
	Queue<Tree*> q;
	q.enqueue(t);
	while (!q.isEmpty()) {
		Queue<Tree*> next_q;
		Vector<Tree*> breadth;
		while (!q.isEmpty()) {
			Tree* node = q.dequeue();
			breadth.add(node);
			for (int i = 0; i < node->children.size(); i++)
				next_q.enqueue(node->children[i]);
		}
		reflectBreadth(breadth);
		q = next_q;
	}
}

bool recIsIdealCube(int cur, int remaining, int n, Set<int> &cubes) {

	if (remaining == 0) return true;
	if (remaining < 0) return false;
	if (cur == n) return false;

	Set<int> without_cubes = cubes;
	bool without = recIsIdealCube(cur + 1, remaining, n, without_cubes);

	Set<int> with_cubes = cubes;
	with_cubes.add(cur);
	bool with = recIsIdealCube(cur + 1, remaining - cur*cur*cur, n, with_cubes);

	if (!with && !without) {
		return false;
	}

	if (without && !with) {
		cubes = without_cubes;
		return true;
	}

	if (!without && with) {
		cubes = with_cubes;
		return true;
	}

	if (without_cubes.size() < with_cubes.size()) {
		cubes = without_cubes;
	} else {
		cubes = with_cubes;
	}

	return true;
}

bool isIdealCube (int n, Set<int> &cubes) {
	return recIsIdealCube(1, n*n*n, n, cubes);
}

int main() {
	for (int i = 1; i <= 25; i++) {
		Set<int> cubes;
		cout << i << ' ' << isIdealCube(i, cubes) << ' ' << cubes << '\n';
	}
    return 0;
}
