//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
//  Modified by C. Lee-Klawender

/** @file Vertex.h */

// This class does a lot of the work for the graph!

#ifndef _VERTEX
#define _VERTEX

#include "Edge.h"

// The following ADT choices can vary according to how you want
// to implement the adjacency list, and they can be different from
// those used in class Graph.
//#include "DACmap.h" // ADT for Adjacency List

using namespace std;

template<class LabelType>
class Vertex
{
private:
	LabelType vertexLabel;
	bool      visited;  // True if the vertex is visited
    
//    DACmap<LabelType, Edge<LabelType> >  adjacencyList;
//    map<LabelType, Edge<LabelType>> *adjacentIterator = adjacencyList.getIterator();
//    

    map<LabelType, Edge<LabelType>> adjacencyList;
    typename map<LabelType, Edge<LabelType>>::iterator adjacentIterator = adjacencyList.begin();
    
//    DACmapIterator<LabelType, Edge<LabelType>> *adjacentIterator = adjacencyList.iterator();
    // Helper method for finding a specific neighbor
    int getNeighborPosition(const LabelType& neighborVertex) const;
    
public:
	/** Creates an unvisited vertex, gives it a label, and clears its
	adjacency list.
	NOTE: A vertex must have a unique label that cannot be changed. */
	Vertex(LabelType label);

	/** @return  The label of this vertex. */
	LabelType getLabel() const;

	/** Marks this vertex as visited. */
	void visit();

	/** Marks this vertex as not visited. */
	void unvisit();

	/** Returns the visited status of this vertex.
	@return  True if the vertex has been visited, otherwise
	returns false/ */
	bool isVisited() const;

	/** Adds an edge between this vertex and the given vertex.
	@return  True if the connection is successful. */
	bool connect(const LabelType& endVertex, const int edgeWeight = 0);

	/** Removes the edge between this vertex and the given one.
	@return  True if the removal is successful. */
	bool disconnect(const LabelType& endVertex);

	/** Gets the weight of the edge between this vertex and the given vertex.
	@return  The edge weight. This value is zero for an unweighted graph and
	is negative if the .edge does not exist */
	int getEdgeWeight(const LabelType& endVertex);

	/** Calculates how many neighbors this vertex has.
	@return  The number of the vertex's neighbors. */
	int getNumberOfNeighbors() const;

	/** Sets current neighbor to first in adjacency list. */
	void resetNeighbor();

	/** Gets this vertex's next neighbor in the adjacency list.
	@return  The label of the vertex's next neighbor. */
	vector<LabelType> getNextNeighbor();

	/** Sees whether this vertex is equal to another one.
	Two vertices are equal if they have the same label. */
	bool operator==(const Vertex<LabelType>& rightHandItem) const;
}; // end Vertex

template<class LabelType>
Vertex<LabelType>::
Vertex(LabelType label) : vertexLabel(label), visited(false)
{
	adjacentIterator = adjacencyList.begin();
}  // end constructor

template<class LabelType>
LabelType Vertex<LabelType>::getLabel() const
{
	return vertexLabel;
}  // end getLabel

template<class LabelType>
void Vertex<LabelType>::visit()
{
	visited = true;
}  // end visit

template<class LabelType>
void Vertex<LabelType>::unvisit()
{
	visited = false;
}  // end unvisit

template<class LabelType>
bool Vertex<LabelType>::isVisited() const
{
	return visited;
}  // end isVisited

template<class LabelType>
bool Vertex<LabelType>::connect(const LabelType& endVertex, const int edgeWeight)
{
	Edge<LabelType> thisEdge(endVertex, edgeWeight);
    adjacentIterator = adjacencyList.find(endVertex);
    if (adjacentIterator != adjacencyList.end()){
        cout << vertexLabel << " and " << endVertex << " are already connected" << endl;
        return false;
    }
    else{
        adjacencyList[endVertex] = thisEdge;
        return true;
    }
}  // end connect

template<class LabelType>
bool Vertex<LabelType>::disconnect(const LabelType& endVertex)
{
    adjacentIterator = adjacencyList.find(endVertex);
    if (adjacentIterator == adjacencyList.end()){
        return false;
    }
    else{
        adjacencyList.erase(adjacentIterator);
        return true;
    }
}  // end disconnect

template<class LabelType>
int Vertex<LabelType>::getEdgeWeight(const LabelType& endVertex)
{
    int weight = adjacencyList[endVertex].getWeight();
    return weight;
}  // end getEdgeWeight

template<class LabelType>
int Vertex<LabelType>::getNumberOfNeighbors() const
{
	return (int)adjacencyList.size();
}  // end getNumberOfNeighbors

template<class LabelType>
void Vertex<LabelType>::resetNeighbor()
{
	adjacentIterator = adjacencyList.begin();
}  // end resetNeighbor

template<class LabelType>
vector<LabelType> Vertex<LabelType>::getNextNeighbor()
{
    vector<LabelType> returnThis;
    for (adjacentIterator = adjacencyList.begin(); adjacentIterator != adjacencyList.end(); adjacentIterator++) {
        returnThis.push_back(adjacentIterator->first);
    }
    return returnThis;
}  // end getNextNeighbor

template<class LabelType>
bool Vertex<LabelType>::operator==(const Vertex<LabelType>& rightHandItem) const
{
	return (vertexLabel == rightHandItem.vertexLabel);
}  // end operator==

template<class LabelType>
int Vertex<LabelType>::getNeighborPosition(const LabelType& neighborVertex) const
{
    adjacentIterator = adjacencyList.find(neighborVertex);
    if (adjacentIterator == adjacencyList.end()) {
        return -1;
    }
    else{
        return adjacentIterator.getWeight();
    }
}  // end getNeighborPosition


#endif
