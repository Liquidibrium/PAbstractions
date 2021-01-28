
#include "MyUndirectedGraph.h"

MyUndirectedGraph::MyUndirectedGraph() {}

MyUndirectedGraph::~MyUndirectedGraph() {
	foreach (string v in vertices) delete vertices[v];
	pair<string, string> e;
	foreach (e in edges) delete edges[e];
}

void MyUndirectedGraph::addNode(string name) {
	if (vertices.containsKey(name)) return;
	Vertex* newVertex = new Vertex;
	newVertex->name = name;
	vertices[name] = newVertex;
}

int MyUndirectedGraph::size() {
	return vertices.size();
}

string* MyUndirectedGraph::getNodes() {
	if (size() == 0) return NULL;
	string* names = new string[size()];
	int index = 0;
	foreach (string v in vertices) {
		names[index] = v;
		index++;
	}
	return names;
}

bool MyUndirectedGraph::addArc(string from, string to, int weight) {
	if (!vertices.containsKey(from))
		return false;
	if (!vertices.containsKey(to))
		return false;
	if (edges.containsKey(make_pair(from, to))) {
		edges[make_pair(from, to)]->weight = weight;
		edges[make_pair(to, from)]->weight = weight;
		return true;
	}
	initEdge(from, to, weight);
	initEdge(to, from, weight);
	return true;
}

void MyUndirectedGraph::initEdge(string &from, string &to, int weight) {
	Edge* newEdge = new Edge;
	newEdge->from = vertices[from];
	newEdge->to = vertices[to];
	newEdge->weight = weight;
	vertices[from]->outgoing.add(newEdge);
	vertices[to]->incoming.add(newEdge);
	edges[make_pair(from, to)] = newEdge;
}

int MyUndirectedGraph::getArcWeight(string from, string to) {
	if (!edges.containsKey(make_pair(from, to))) return -1;
	return edges[make_pair(from, to)]->weight;
}

void MyUndirectedGraph::removeNode(string name) {
	if (!vertices.containsKey(name)) return;
	Vertex* toRemove = vertices[name];
	foreach (Edge* outgoing in toRemove->outgoing) {
		edges.remove(make_pair(name, outgoing->to->name));
		vertices[outgoing->to->name]->incoming.remove(outgoing);
		delete outgoing;
	}
	foreach (Edge* incoming in toRemove->incoming) {
		edges.remove(make_pair(incoming->from->name, name));
		vertices[incoming->from->name]->outgoing.remove(incoming);
		delete incoming;
	}
	vertices.remove(name);
	delete toRemove;
}

void MyUndirectedGraph::removeArc(string from, string to) {
	if (!edges.containsKey(make_pair(from, to))) return;
	removeDirectedArc(from, to);
	removeDirectedArc(to, from);
}

void MyUndirectedGraph::removeDirectedArc(string &from, string &to) {
	Edge* toRemove = edges[make_pair(from, to)];
	vertices[from]->outgoing.remove(toRemove);
	vertices[to]->incoming.remove(toRemove);
	edges.remove(make_pair(from, to));
	delete toRemove;
}

int MyUndirectedGraph::getConnectedNodesCount(string name) {
	if (!vertices.containsKey(name)) return -1;
	return vertices[name]->incoming.size() + vertices[name]->outgoing.size();
}

string* MyUndirectedGraph::getConnectedNodes(string name) {
	if (!vertices.containsKey(name)) return NULL;
	string* con_verts = new string[vertices[name]->outgoing.size()];
	int index = 0;
	foreach (Edge* outgoing in vertices[name]->outgoing) {
		con_verts[index] = outgoing->to->name;
		index++;
	}
	return con_verts;
}
