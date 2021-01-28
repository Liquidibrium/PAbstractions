
#include "MyGraph.h"

MyGraph::MyGraph() {
	
}

MyGraph::~MyGraph() {
	foreach (Vertex* v in vertices)
		delete v;
	foreach (Edge* e in edges)
		delete e;
}

void MyGraph::addVertex(int id) {
	if (vertex_map.containsKey(id)) return;
	Vertex* vertex = new Vertex;
	vertex->id = id;
	vertices.add(vertex);
	vertex_map[id] = vertex;
	nVertices++;
}

void MyGraph::removeVertex(int id) {
	
	if (!vertex_map.containsKey(id)) return;
	
	foreach (Vertex* v in vertices) {
		foreach (Edge* e in v->ways) {
			if (e->to->id == id) {
				v->ways.remove(e);
				edges.remove(e);
				delete e;
			}
		}
	}

	Vertex* vertex = vertex_map[id];

	foreach (Edge* e in vertex->ways) {
		edges.remove(e);
		delete e;
	}
	
	vertex_map.remove(id);
	vertices.remove(vertex);
	delete vertex;

	nVertices--;
}

int MyGraph::numVertices() {
	return nVertices;
}

void MyGraph::addEdge(int from, int to, double cost) {
	
	if (!vertex_map.containsKey(from)) return;
	if (!vertex_map.containsKey(to)) return;
	
	Vertex* start = vertex_map[from];
	Vertex* finish = vertex_map[to];
	
	Edge* edge = new Edge;
	edge->from = start;
	edge->to = finish;
	edge->cost = cost;

	start->ways.add(edge);

	edges.add(edge);
}

int MyGraph::costOfEdge(int from, int to, double cost) {

	if (!vertex_map.containsKey(from)) return -1;
	if (!vertex_map.containsKey(to)) return -1;

	Vertex* start = vertex_map[from];
	Vertex* finish = vertex_map[to];

	foreach (Edge* e in start->ways) {
		if (e->to == finish)
			return e->cost;
	}

	return -1;
}

Set<int> MyGraph::neighboursOf(int id) {

	if (!vertex_map.containsKey(id)) return Set<int>();

	Set<int> result;

	Vertex* vertex = vertex_map[id];
	foreach(Edge* e in vertex->ways)
		result.add(e->to->id);
	
	return result;
}

bool MyGraph::recIsPath(Vertex* from, Vertex* to, Set<Vertex*> &visited) {
	if (from == to) return true;
	if (visited.contains(from)) return false;
	visited.add(from);
	foreach (Edge* e in from->ways) {
		if (recIsPath(e->to, to, visited))
			return true;
	}
	return false;
}

bool MyGraph::isPath(int from, int to) {

	if (!vertex_map.containsKey(from)) return false;
	if (!vertex_map.containsKey(to)) return false;

	Set<Vertex*> visited;
	return recIsPath(vertex_map[from], vertex_map[to], visited);
}
