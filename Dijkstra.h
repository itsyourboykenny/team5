#ifndef _DIJKSTRA
#define _DIJKSTRA

#include <vector>
#include <map>
#include "LinkedGraph.h"
#include <math.h>
#include "Node.h"
#include "Vertex.h"
#include <fstream>
#include <iomanip>
using namespace std;
const int inf = 1 << 30;
template <class LabelType>
struct w{
    int lbs = 0;
    bool done = false;
    LabelType from;
    
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
    map<LabelType,w<LabelType>> weight;
    
    for (localIterator = localList.begin(); localIterator != localList.end(); localIterator++) {
        weight[localIterator->first].init();
    }

    int currWeight = 0;
    int tempWeight = 0;
    vector<LabelType> visitList;
    vector<LabelType> queue;
    
    weight[start].isStart();
    localIterator = localList.find(start);
    
    while(!weight[end].done)
	{
//        Some stuff needed to find smallest weight
        LabelType smallest;
        int foo = inf;
        queue = localIterator->second->getNextNeighbor();
//        Compare against all possible paths
        for (int y = 0; y < queue.size(); y++)
        {
            //            Gets initial crap
            if (!weight[queue[y]].done) {
                
                LabelType temp = queue[y];
                tempWeight = localList[localIterator->first]->getEdgeWeight(temp);
                
                if (weight[temp].lbs > tempWeight+currWeight){
                    weight[temp].lbs = tempWeight+currWeight;
                    weight[temp].from = localIterator->first;
                }
            }
        }
        
        //            Mark shortest distance as done, if no path is found then backtrack
        
        for (localIterator=localList.begin();localIterator!=localList.end();localIterator++) {
            if(weight[localIterator->first].lbs < foo && !weight[localIterator->first].done){
                smallest = localIterator->first;
                foo = weight[smallest].lbs;
            }
        }
        weight[smallest].done = true;

        currWeight = weight[smallest].lbs;
        //        start iteration on next target
        localIterator = localList.find(smallest);
    }
    
    localIterator = localList.find(end);
    while (localIterator != localList.find(start)){
        visitList.insert(visitList.begin(), localIterator->first);
        localIterator = localList.find((weight[localIterator->first]).from);
    }
    visitList.insert(visitList.begin(),start);
    
    for (int shit = (int)visitList.size(); shit > 0; shit--) {
        cout << visitList[shit] << " -> ";
    }
	return visitList;
}

#endif
