
#ifndef MY_UNDIRECTED_GRAPH_H_
#define MY_UNDIRECTED_GRAPH_H_

#include <string>
#include <utility>
#include "set.h"
#include "map.h"
using namespace std;

class MyUndirectedGraph {

	public:

		MyUndirectedGraph();
		~MyUndirectedGraph();
		void addNode(string name);
		int size();
		string* getNodes();
		bool addArc(string from, string to, int weight);
		int getArcWeight(string from, string to);
		void removeNode(string name);
		void removeArc(string from, string to);
		int getConnectedNodesCount(string name);
		string* getConnectedNodes(string name);

	private:

		struct Vertex;
		struct Edge;

		struct Vertex {
			string name;
			Set<Edge*> outgoing;
			Set<Edge*> incoming;
		};

		struct Edge {
			Vertex* from;
			Vertex* to;
			int weight;
		};

		Map<string, Vertex*> vertices;
		Map<pair<string, string>, Edge*> edges;

		void initEdge(string &from, string &to, int weight);
		void removeDirectedArc(string &from, string &to);

};

#endif
