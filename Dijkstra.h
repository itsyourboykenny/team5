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

struct w{
    int lbs = 0;
    bool done = false;
    
    void isStart(){lbs = 0; done = true;}
    void init(){lbs = inf; done = false;}
};

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
    if (localIterator == localList.end()){
        cout << "Doesnt Exist" << endl;
        return vector<LabelType>();
    }
    
    localIterator = localList.find(cityB);
    if (localIterator == localList.end()){
        cout << "Doesnt Exist" << endl;
        return vector<LabelType>();
    }
    
    return solve(cityA, cityB);
}


template <class LabelType>
vector<LabelType> Dijkstra<LabelType>::solve(LabelType start, LabelType end)
{
    map<LabelType,w> weight;
    
    for (localIterator = localList.begin(); localIterator != localList.end(); localIterator++) {
        weight[localIterator->first].init();
    }

    int Totalweight = 0;
    int tempWeight = 0;
    vector<LabelType> visitList;
    vector<LabelType> queue;
    
    weight[start].isStart();

    queue.push_back(localList[start]->getLabel());
    localIterator = localList.find(start);
    
    while(!weight[end].done)
	{
//        Some stuff needed to find smallest weight
        LabelType smallest;
        int foo = inf;
        queue = localIterator->second->getNextNeighbor();
        bool isFound = false;
        
//        Compare against all possible paths
        for (int y = 0; y < queue.size(); y++)
        {
            //            Gets initial crap
            if (!weight[queue[y]].done) {
                
                LabelType temp = queue[y];
                tempWeight = localList[localIterator->first]->getEdgeWeight(temp);
                
                //            If current weight is lower than total weight, change it
                //            Needs to also store originating node. But i'm too lazy to right now
                if (weight[temp].lbs > Totalweight+tempWeight)
                    if (!weight[temp].done)
                        weight[temp].lbs = Totalweight+tempWeight;
                //            Determine smallest weight. The easier way
                if (weight[temp].lbs < foo){
                    smallest = temp;
                    foo = weight[temp].lbs;
                    isFound = true;
                }
            }
        }
        
        //            Mark shortest distance as done, if no path is found then backtrack
        if (!isFound){
            visitList.erase(visitList.end());
            smallest = visitList[visitList.size()];
        }
        else{
            weight[smallest].done = true;
            visitList.push_back(smallest);
            Totalweight += weight[smallest].lbs;
        }
        
        //        start iteration on next target
        localIterator = localList.find(smallest);
    }
    
	cout << "Total Distance Traveled " << Totalweight << " miles" << endl;
    for (int shit = 0; shit < visitList.size(); shit++) {
        cout << visitList[shit] << " -- " << visitList[shit+1] << " = " << localList[visitList[shit]]->getEdgeWeight(visitList[shit+1]) << endl;;
    }
	return visitList;
}

#endif
