
#include "graph.h"

Graph::Graph() {
	numVertices = 0;
}

Graph::~Graph() {
	foreach (Vertex* v in vertices) delete v;
	foreach (Edge* e in edges) delete e;
}

void Graph::addNode(string name) {
	if (vert_map.containsKey(name)) return;
	Vertex* v = new Vertex;
	v->name = name;
	vertices.add(v);
	vert_map[name] = v;
	numVertices++;
}

int Graph::size() {
	return numVertices;
}

string * Graph::getNodes() {
	if (size() == 0) return NULL;
	string* nodes = new string[numVertices];
	int index = 0;
	foreach (Vertex* v in vertices) {
		nodes[index] = v->name;
		index++;
	}
	return nodes;
}

bool Graph::addArc(string from, string to, int weight) {

	if (!vert_map.containsKey(from)) return false;
	if (!vert_map.containsKey(to)) return false;

	Vertex* v_from = vert_map[from];
	Vertex* v_to = vert_map[to];

	foreach (Edge* e in v_from->ways) {
		if (e->to == v_to) {
			e->weight = weight;
			return true;
		}
	}

	Edge* edge = new Edge;
	edge->from = v_from;
	edge->to = v_to;
	edge->weight = weight;

	edges.add(edge);
	v_from->ways.add(edge);

	return true;
}

int Graph::getArcWeight(string from, string to) {

	if (!vert_map.containsKey(from)) return -1;
	if (!vert_map.containsKey(to)) return -1;

	Vertex* v_from = vert_map[from];
	Vertex* v_to = vert_map[to];

	foreach (Edge* e in v_from->ways) {
		if (e->to == v_to) {
			return e->weight;
		}
	}

	return -1;
}

void Graph::removeNode(string name) {

	if (!vert_map.containsKey(name)) return;

	Vertex* v = vert_map[name];

	foreach (Edge* e in edges) {
		if (e->from == v) {
			edges.remove(e);
			delete e;
		}
		else if (e->to == v) {
			e->from->ways.remove(e);
			edges.remove(e);
			delete e;
		}
	}

	vertices.remove(v);
	vert_map.remove(name);

	numVertices--;

}

void Graph::removeArc(string from, string to) {

	if (!vert_map.containsKey(from)) return;
	if (!vert_map.containsKey(to)) return;

	Vertex* v_from = vert_map[from];
	Vertex* v_to = vert_map[to];

	foreach (Edge* e in v_from->ways) {
		if (e->to == v_to) {
			v_from->ways.remove(e);
			edges.remove(e);
			delete e;
			return;
		}
	}

}

int Graph::getConnectedNodesCount(string name) {
	if (!vert_map.containsKey(name)) return -1;
	return vert_map[name]->ways.size();
}

string * Graph::getConnectedNodes(string name) {
	if (!vert_map.containsKey(name)) return NULL;
	Vertex* v = vert_map[name];
	string* nodes = new string[v->ways.size()];
	int index = 0;
	foreach (Edge* e in v->ways) {
		nodes[index] = e->to->name;
		index++;
	}
	return nodes;
}
