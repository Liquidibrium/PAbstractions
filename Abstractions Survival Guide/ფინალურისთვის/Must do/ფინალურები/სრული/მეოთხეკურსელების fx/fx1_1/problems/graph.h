#include <string>


using namespace std;

class Graph {
	public:
		Graph();
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
		//TODO: here goes your code

};