
#include <string>
#include "set.h"
#include "map.h"
using namespace std;

class Graph {

	public:

		Graph();
		~Graph();

		void addNode(string name);
		int size();
		string * getNodes();

		bool addArc(string from, string to, int weight);
		int getArcWeight(string from, string to);

		void removeNode(string name);
		void removeArc(string from, string to);

		int getConnectedNodesCount(string name);
		string * getConnectedNodes(string name);

	private:

		struct Vertex;
		struct Edge;

		struct Vertex {
			string name;
			Set<Edge*> ways;
		};

		struct Edge {
			Vertex* from;
			Vertex* to;
			int weight;
		};

		Set<Vertex*> vertices;
		Set<Edge*> edges;
		Map<string, Vertex*> vert_map;

		int numVertices;

};