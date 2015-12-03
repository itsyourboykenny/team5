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
protected:
    map<LabelType,Vertex<LabelType>*> localList;
    typename map<LabelType,Vertex<LabelType>*>::iterator localIterator;
    ofstream *ptrOut;
    
public:
    Dijkstra(){ reset(); ptrOut = nullptr; }
    Dijkstra(ofstream &outFile){reset(); ptrOut = &outFile;}
    Dijkstra(const Dijkstra &source){/*\(. .\) to the windowww.. (/. .)/ to the walls*/; }
    ~Dijkstra(){ reset(); }
    bool add(LabelType start, LabelType end, int edgeWeight);
    vector<LabelType> findShortestPath(LabelType cityA, LabelType cityB);
    vector<LabelType> solve(LabelType start, LabelType end);
    void readPath(LabelType stuff);
    void reset(){ localList.clear(); this->numberOfVertices = this->numberOfEdges = 0; }
    void refresh(){} //Call this before calculation
};

template <class LabelType>
bool Dijkstra<LabelType>::add(LabelType start, LabelType end, int edgeWeight){
    
    //########### Create a new vertex if it doesnt exist ###########
    localIterator = localList.find(start);
    if (localIterator == localList.end()) {
        localList[start] = new Vertex<LabelType>(start);
        this->numberOfVertices++;
    }
    localIterator = localList.find(end);
    if (localIterator == localList.end()){
        localList[end] = new Vertex<LabelType>(end);
        this->numberOfVertices++;
    }
    
    //    ########### Connects the two vertex ###########
    localList[start]->connect(end,edgeWeight);
    localList[end]->connect(start,edgeWeight);
    
    this->numberOfEdges++;
    
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
    map<LabelType,int> weight;
    
    for (localIterator = localList.begin(); localIterator != localList.end(); localIterator++) {
        weight[localIterator->first] = inf;
    }

    int Totalweight = 0;
    int tempWeight = 0;
	vector<LabelType> returnThis;
    vector<LabelType> queue;
    
    localList[start]->visit();
    weight[start] = 0;

    returnThis.push_back(localList[start]->getLabel());
    queue.push_back(localList[start]->getLabel());
    localIterator = localList.find(queue.front());
    
    while(!localList[end]->isVisited() && !queue.empty())
	{
//        Some stuff needed to find smallest while
        Vertex<LabelType> * smallest = nullptr;
        int foo = inf;
        
//        Compare against all possible paths
        for (int y = 0; y < (localList[localIterator->first]->getNumberOfNeighbors()); y++)
		{
//            Gets initial crap
            LabelType temp = localList[localIterator->first]->getNextNeighbor();
            tempWeight = localList[localIterator->first]->getEdgeWeight(temp);

//            If current weight is lower than total weight, change it
//            Needs to also store originating node. But i'm too lazy to right now
            if (weight[temp] > Totalweight+tempWeight)
                if (!localList[temp]->isVisited())
                    weight[temp] = Totalweight+tempWeight;
//            Determine smallest weight. The easier way
            if (weight[temp]<foo){
                smallest = localList[temp];
                foo = weight[temp];
            }
        }
        
        //            Mark shortest distance as done
        if (smallest == nullptr)
            cout<<"Something is wrong" << endl;
        else
            smallest->visit();
        
        //        Bunch of crap to prep for the next iteration
        queue.push_back(smallest->getLabel());
        queue.erase(queue.begin());
        Totalweight += weight[queue.front()];
        localIterator = localList.find(queue.front());
        returnThis.push_back(localIterator->first);
    }
    
	cout << "Total Distance Traveled " << Totalweight << " miles" << endl;
	return returnThis;
}

#endif
