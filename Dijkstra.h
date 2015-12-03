#ifndef _DIJKSTRA
#define _DIJKSTRA

#include <vector>
#include <map>
#include "LinkedGraph.h"
#include <math.h>
#include "Node.h"
#include "Vertex.h"
#include <fstream>
using namespace std;
const int inf = 1 << 30;

template <class LabelType>
class Dijkstra : public LinkedGraph<LabelType>{
private:
	map<LabelType, Vertex<LabelType>*> localList;
	typename map<LabelType, Vertex<LabelType>*>::iterator localIterator;
	ofstream *ptrOut;

public:
	Dijkstra(){ reset(); ptrOut = nullptr; }
	Dijkstra(ofstream &outFile){ reset(); ptrOut = &outFile; }
	Dijkstra(const Dijkstra &source){/*\(. .\) to the windowww.. (/. .)/ to the walls*/; }
	~Dijkstra(){ reset(); }
	bool add(LabelType start, LabelType end, int edgeWeight);
	vector<LabelType> findShortestPath(LabelType cityA, LabelType cityB);
	vector<LabelType> solve(LabelType start, LabelType end);
	void readPath();
	void reset(){ localList.clear(); this->numberOfVertices = this->numberOfEdges = 0; }
	void refresh(){} //Call this before calculation
};

template <class LabelType>
bool Dijkstra<LabelType>::add(LabelType start, LabelType end, int edgeWeight)
{
	Vertex<LabelType> *startCity = findOrCreateVertex(start);
	Vertex<LabelType> *endCity = findOrCreateVertex(end);
	
	localList[start] = startCity;
	localList[end] = endCity;

	localList[start]->connect(end, edgeWeight);
	localList[end]->connect(start, edgeWeight);

	this->numberOfEdges++;

	//this->LinkedGraph<LabelType>::add(start, end, edgeWeight);
	return true;
}

template <class LabelType>
vector<LabelType> Dijkstra<LabelType>::findShortestPath(LabelType cityA, LabelType cityB){

	localIterator = localList.find(cityA);
	if (localIterator == localList.end())
		cout << "Doesnt Exist" << endl;
		
	localIterator = localList.find(cityB);
	if (localIterator == localList.end())
		cout << "Doesnt Exist" << endl;

	return solve(cityA, cityB);
}


template <class LabelType>
vector<LabelType> Dijkstra<LabelType>::solve(LabelType start, LabelType end)
{
	map<LabelType, int> weight;
	map<LabelType, Vertex<LabelType>*> prev;
	int Totalweight = 0;
	int tempWeight = 0;
	vector<LabelType> returnThis;
	vector<LabelType> queue;
	localList[start]->visit();
	weight[start] = 0;
	prev[start] = 0;
	string previous;
	// not working
	//for (localIterator = localList.begin(); localIterator != localList.end(); localIterator++) 
	//{
	//	weight[localIterator->first] = inf;
	//}
	returnThis.push_back(localList[start]->getLabel());
	queue.push_back(localList[start]->getLabel());
	localIterator = localList.find(queue.front());
	while (!localList[end]->isVisited() && !queue.empty())
	{
		//        Some stuff needed to find smallest while
		Vertex<LabelType> * smallest = nullptr;
		int foo = inf;
		localList[localIterator->first]->resetNeighbor();

		//        Compare against all possible paths		
		for (int y = 0; y < (localList[localIterator->first]->getNumberOfNeighbors()); y++)
		{
			previous = localList[localIterator->first]->getLabel();
			LabelType temp = localList[localIterator->first]->getNextNeighbor();
			if (temp != previous || temp != start)
			{
				tempWeight = localList[localIterator->first]->getEdgeWeight(temp);
				if (weight[temp] == 0)
					weight[temp] = inf;

				if (weight[temp] > weight[previous] + tempWeight)
				{
					//if (!localList[temp]->isVisited())
					Totalweight = 0; // set total to 0
					weight[temp] = weight[previous] + tempWeight; // new short distance
					prev[temp] = localList[localIterator->first]; //change the previous
				}
				localList[temp]->visit();
				//            Determine smallest weight. The easier way
				if (weight[temp] < foo){
					smallest = localList[temp];
					foo = weight[temp];
				}
				//            Mark shortest distance as done
				if (smallest == nullptr)
					cout << "Something is wrong" << endl;
				else
					smallest->visit();
			}
		}
		queue.push_back(smallest->getLabel());
		queue.erase(queue.begin());
		Totalweight += weight[queue.front()]; // this total is only good for one time.
		localIterator = localList.find(queue.front());
		returnThis.push_back(localIterator->first);
	}   
	Totalweight = 0;
	vector<LabelType> returnThisOne;

	Vertex<LabelType>* endCity = localList[end];
	returnThisOne.push_back(end);
	Vertex<LabelType>* previ = localList[end];
	string gettingDist;
	gettingDist = previ->getLabel();
	while (previ != 0)
	{
		gettingDist = previ->getLabel();
		Totalweight += weight[gettingDist];
		returnThisOne.push_back(gettingDist);
		previ = prev[gettingDist];
	}
	//cout << getDist << endl;
	
	
	cout << "Total Distance Traveled " << Totalweight << " miles" << endl;
	return returnThis;
}


#endif