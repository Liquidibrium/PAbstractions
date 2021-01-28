/******************************************************************************
 * File: Trailblazer.h
 *
 * Exports functions that use Dijkstra's algorithm, A* search, and Kruskal's
 * algorithm as specified in the assignment handout.
 */

#ifndef Trailblazer_Included
#define Trailblazer_Included

#include "TrailblazerTypes.h"
#include "set.h"
#include "grid.h"

struct node{
	Loc parent;
	Color col;
	double weight;
	node(Loc par ,Color col = GRAY, double weight = INT_MAX){
		this->col =col;
		parent = par;
		this->weight = weight;
	}
	node(){
		 col = GRAY;
	}
};

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this function prototype and the
 * implementation inside of Trailblazer.cpp.
 */
Vector<Loc> shortestPath(	Loc start, Loc end,	Grid<double>& world, 
double costFn(	Loc one, Loc two,
Grid<double>& world), 
double heuristic(Loc start, Loc end, Grid<double>& world));
// get path using saved data from start to end;
void getPath(Vector<Loc>& result,Map<Loc,node>& data,Loc end);

/* Function: createMaze
 * 
 * Creates a maze of the specified dimensions using a randomized version of
 * Kruskal's algorithm, then returns a set of all of the edges in the maze.
 *
 * As specified in the assignment handout, the edges you should return here
 * represent the connections between locations in the graph that are passable.
 * Our provided starter code will then use these edges to build up a Grid
 * representation of the maze.
 */
Set<Edge> createMaze(int numRows, int numCols);

// finds cluster of location into the vector of clusters where   i's cluster is clusters[i] and i is row * numRows + col
int findCluster( Loc& loc,  Vector<int>& clusters, int &numRows);

#endif
