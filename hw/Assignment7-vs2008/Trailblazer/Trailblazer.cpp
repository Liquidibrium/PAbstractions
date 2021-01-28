/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "random.h"
#include <limits>
using namespace std;

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
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */

Vector<Loc> shortestPath(Loc start, Loc end,Grid<double>& world,double costFn(Loc one, Loc two,Grid<double>& world), 
						 double heuristic(Loc start, Loc end, Grid<double>& world)){
	TrailblazerPQueue<Loc> PQ;
	node startNode = node(start,YELLOW,0);
	PQ.enqueue(start,heuristic(start,end,world));
	colorCell(world,start,YELLOW);
	Map<Loc,node> data;
	data[start]=startNode;
	bool found=false;
	while(!PQ.isEmpty()){
		Loc currLoc = PQ.dequeueMin();
		data[currLoc].col = GREEN;
		colorCell(world,currLoc,GREEN);
		if(currLoc==end){
			found = true;
			break;
		}
		for(int i =-1; i<=1; i++){
			for(int j =-1; j<=1; j++){
				if(!(i==0&&j==0) && world.inBounds(currLoc.row+i,currLoc.col+j)){							
					Loc neighbour= makeLoc(currLoc.row+i,currLoc.col+j);
					if(data.containsKey(neighbour)){
						if(data[neighbour].col==YELLOW){
							double currWeight = data[currLoc].weight+ costFn(currLoc,neighbour,world);
							if(data[neighbour].weight>currWeight){
								data[neighbour].parent = currLoc;
								data[neighbour].weight = currWeight;
								PQ.decreaseKey(neighbour,data[neighbour].weight+heuristic(neighbour,end,world));
							}
						}
					}else{
						if(costFn(currLoc,neighbour,world)!=numeric_limits<double>::infinity()){// if neighbour is not wall( or diagonal)
							node newNode = node(currLoc,YELLOW,data[currLoc].weight + costFn(currLoc,neighbour,world));
							data[neighbour]=newNode;
							colorCell(world,neighbour,YELLOW);
							PQ.enqueue(neighbour,newNode.weight+heuristic(neighbour,end,world));
						}
					}
				}
			}
		}
	}
	if(!found)error(" No path found");
	Vector<Loc> res;
	getPath(res,data,end);
    return res;
}

void getPath(Vector<Loc>& result,Map<Loc,node>& data,Loc end){
	result.push_back(end);
	while(data[end].parent!=end){
		result.push_back(data[end].parent);
		end=data[end].parent;
	}
	//reverse path
	for(int i = 0; i < result.size()/2; i++){
		swap(result[i],result[result.size()-i-1]);
	}
}
int findCluster( Loc& loc,  Vector<int>& clusters, int &numRows){
	int curr = loc.row*numRows + loc.col;
	while( curr != clusters[curr]){ // find root of the clasters 
        clusters[curr]=clusters[clusters[curr]]; // change parent to parent's parent XD 
        curr = clusters[curr];
    }
    return curr;
}
Set<Edge> createMaze(int numRows, int numCols) {
		Vector<int> clusters;// vector to save clusters
		for(int i = 0; i < numRows * numCols; i++){
            clusters.push_back(i);
        }
		TrailblazerPQueue<Edge> PQ;
		for(int i = 0 ; i < numRows * numCols; i++){// make and put random weighted edges into PQueue  
			int currRow = i / numRows;
			int currCol = i % numRows;
			if(currRow != numRows-1){// range check 
				PQ.enqueue(makeEdge(makeLoc(currRow,currCol),makeLoc(currRow+1,currCol)),randomReal(0, 1));
			}
			if(currCol != numCols-1){// range check
				PQ.enqueue(makeEdge(makeLoc(currRow,currCol),makeLoc(currRow,currCol+1)),randomReal(0, 1));
			}
		}
		Set<Edge> spanningTree;
		int nClusters=numRows * numCols;// namber of culsters 
		while(nClusters>1){
			Edge currE =PQ.dequeueMin();
			int startCluster= findCluster(currE.start,clusters,numRows);
			int endCluster = findCluster(currE.end,clusters,numRows);
			if(startCluster!=endCluster){ // if locs dont have same clusters union them 
				nClusters--;
				clusters[startCluster]=endCluster;
				spanningTree.add(currE);
			}
		}
		return spanningTree;
}
