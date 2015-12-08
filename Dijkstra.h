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
    vector<pair<pair<LabelType, LabelType>,int>> history;
    
public:
    Dijkstra(){ reset(); ptrOut = nullptr; }
    Dijkstra(ofstream &outFile){reset(); ptrOut = &outFile;}
    Dijkstra(const Dijkstra &source){/*\(. .\) to the windowww.. (/. .)/ to the walls*/; }
    ~Dijkstra(){ reset(); }
    bool add(LabelType start, LabelType end, int edgeWeight);
    vector<pair<LabelType,int>> findShortestPath(LabelType cityA, LabelType cityB);
    vector<pair<LabelType,int>> solve(LabelType start, LabelType end);
    bool remove(LabelType cityA, LabelType cityB);
    bool undoRemove();
    void readPath();
	LabelType getFirst();
	void writeFile(ofstream &ofs);
    void reset(){ localList.clear(); this->numberOfVertices = this->numberOfEdges = 0; }
    void refresh(){} //Call this before calculation
};

template <class LabelType>
bool Dijkstra<LabelType>::remove(LabelType cityA, LabelType cityB){
    
    localIterator = localList.find(cityA);
    if (localIterator == localList.end())
        return false;
    localIterator = localList.find(cityB);
    if (localIterator == localList.end())
        return false;
    
    pair<pair<LabelType, LabelType>, int> cities;
    cities = make_pair(make_pair(cityA, cityB),localList[cityA]->getEdgeWeight(cityB));
    
    localIterator = localList.find(cityA);
    localIterator->second->disconnect(cityB);
    if (localList[cityA]->getNumberOfNeighbors() == 0)
        localList.erase(localIterator);
    
    localIterator = localList.find(cityB);
    localIterator->second->disconnect(cityA);
    if (localList[cityB]->getNumberOfNeighbors() == 0)
        localList.erase(localIterator);
    
    history.insert(history.begin(), cities);
    
    return true;

}

template <class LabelType>
bool Dijkstra<LabelType>::undoRemove(){
    
    if (history.size() < 1){
        cout << "Error: Nothing to undo" << endl;
        return false;
    }
    else{
        add(history[0].first.first, history[0].first.second, history[0].second);
        history.erase(history.begin());
        return true;
    }

}

template <class LabelType>
void Dijkstra<LabelType>::readPath(){
    int l = 15;
    vector<LabelType> temp;
    cout << setw(l) << left << "City A" << setw(l) << left << "City B" << setw(l) << left << "Distance" << endl;
    for (int x = 0; x < l*3; x++) {cout << "*";}
    cout << endl;
    
    for (localIterator=localList.begin(); localIterator!=localList.end(); localIterator++) {
        temp = localIterator->second->getNextNeighbor();
        cout << left << setw(l) << localIterator->first <<
        setw(l) << left << temp[0] <<
        setw(l) << left << localIterator->second->getEdgeWeight(temp[0]) << endl;
        
        for (int f = 1; f < temp.size(); ++f) {
            cout << setw(l) << " " <<
            setw(l) << temp[f] <<
            setw(l) << left << localIterator->second->getEdgeWeight(temp[f]) << endl;
        }
        for (int x = 0; x < l*3; x++){cout << "-";}
        cout << endl;
    }
    
}

template <class LabelType>
LabelType Dijkstra<LabelType>::getFirst()
{
	localIterator = localList.begin();
	
	return localIterator->first;
}
template <class LabelType>
void Dijkstra<LabelType>::writeFile(ofstream &ofs)
{
	for (localIterator = localList.begin(); localIterator != localList.end(); localIterator++)
	{
		writeToFile(localIterator->first, ofs);
	}
	unvisitVertices();

	//int l = 15;
	//vector<LabelType> temp;
	//ofs << setw(l) << left << "City A" << setw(l) << left << "City B" << setw(l) << left << "Distance" << endl;
	//for (int x = 0; x < l * 3; x++) { ofs << "*"; }
	//ofs << endl;
	//for (localIterator = localList.begin(); localIterator != localList.end(); localIterator++) {
	//	temp = localIterator->second->getNextNeighbor();
	//	ofs << left << setw(l) << localIterator->first <<
	//		setw(l) << left << temp[0] <<
	//		setw(l) << left << localIterator->second->getEdgeWeight(temp[0]) << endl;

	//	for (int f = 1; f < temp.size(); ++f) {
	//		ofs << setw(l) << " " <<
	//			setw(l) << temp[f] <<
	//			setw(l) << left << localIterator->second->getEdgeWeight(temp[f]) << endl;
	//	}
	//	for (int x = 0; x < l * 3; x++){ ofs << "-"; }
	//	ofs << endl;
	//}
}

template <class LabelType>
bool Dijkstra<LabelType>::add(LabelType start, LabelType end, int edgeWeight){
    
	//this does not create the list in the linkedGraph thus the DFT and BFT are failing to display
    //########### Create a new vertex if it doesnt exist ###########
    //localIterator = localList.find(start);
    //if (localIterator == localList.end()) {
    //    localList[start] = new Vertex<LabelType>(start);
    //    this->numberOfVertices++;
    //}
    //localIterator = localList.find(end);
    //if (localIterator == localList.end()){
    //    localList[end] = new Vertex<LabelType>(end);
    //    this->numberOfVertices++;
    //}
    //
	Vertex<LabelType> *startCity = findOrCreateVertex(start);
	Vertex<LabelType> *endCity = findOrCreateVertex(end);

	localList[start] = startCity;
	localList[end] = endCity;

    //    ########### Connects the two vertex ###########
    localList[start]->connect(end,edgeWeight);
    localList[end]->connect(start,edgeWeight);
    
    this->numberOfEdges++;
    
    return true;
}

template <class LabelType>
vector<pair<LabelType,int>> Dijkstra<LabelType>::findShortestPath(LabelType cityA, LabelType cityB){
   
    localIterator = localList.find(cityA);
    if (localIterator == localList.end()){
        cout << "Doesnt Exist" << endl;
        return vector<pair<LabelType,int>>();
    }
    
    localIterator = localList.find(cityB);
    if (localIterator == localList.end()){
        cout << "Doesnt Exist" << endl;
        return vector<pair<LabelType,int>>();
    }
    
    return solve(cityA, cityB);
}


template <class LabelType>
vector<pair<LabelType,int>> Dijkstra<LabelType>::solve(LabelType start, LabelType end)
{
    map<LabelType,w<LabelType>> weight;
    
    for (localIterator = localList.begin(); localIterator != localList.end(); localIterator++) {
        weight[localIterator->first].init();
    }

    int currWeight = 0;
    int tempWeight = 0;
    vector<pair<LabelType,int>> visitList;
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
        LabelType origin = localIterator->first;
        localIterator = localList.find((weight[localIterator->first]).from);
        pair<LabelType,int> data(origin,localList[origin]->getEdgeWeight(localIterator->first));
        visitList.insert(visitList.begin(), data);
    }
    pair<LabelType,int> data(start,localList[start]->getEdgeWeight(visitList[0].first));
    visitList.insert(visitList.begin(),data);
    
	return visitList;
}

#endif
