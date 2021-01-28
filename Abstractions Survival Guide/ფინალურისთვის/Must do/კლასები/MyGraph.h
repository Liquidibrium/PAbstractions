
#ifndef MY_GPRAH_H_
#define MY_GPRAH_H_

#include "set.h"
#include "map.h"

class MyGraph {

	public:

		MyGraph();
		~MyGraph();

		void addVertex(int id);
		void removeVertex(int id);

		int numVertices();

		void addEdge(int from, int to, double cost);
		int costOfEdge(int from, int to, double cost);

		Set<int> neighboursOf(int id);

		bool isPath(int from, int to);

	private:

		struct Vertex;
		struct Edge;

		Set<Vertex*> vertices;
		Set<Edge*> edges;
		Map<int, Vertex*> vertex_map;

		struct Vertex {
			int id;
			Set<Edge*> ways;
		};
		
		struct Edge {
			Vertex* from;
			Vertex* to;
			double cost;
		};

		int nVertices;

		bool recIsPath(Vertex* from, Vertex* to, Set<Vertex*> &visited);
};

#endif
