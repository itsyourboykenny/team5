#ifndef _DIJKSTRA
#define _DIJKSTRA

#include <vector>
#include <map>
#include <bootstrap.h>
#include "LinkedGraph.h"
#include <math.h>
#include "CRC.h"
#include "Node.h"
#include "Vertex.h"
using namespace std;
const double inf = 1 << 30;


template <class ItemType>
class Dijkstra: public LinkedGraph<ItemType>{
    
private:
    
//  Decided to use maps instead since it seems cleaner than tables. This wont affect DACmap at all
    map<int, Vertex<ItemType>*> theList;
    map<int, Vertex<ItemType>*> theListIterator;
    
    vector<Vertex<ItemType>> results;
    vector<double> weight;
public:
    Dijkstra(){results.resize(0);}
    Dijkstra(const Dijkstra &source){/*\(. .\) to the windowww.. (/. .)/ to the walls*/;}
    ~Dijkstra(){reset();}
    bool insert(string cityA, double dist, string cityB);
    bool findShortestPath(string cityA, string CityB);
    void solve(int hashA, int hashB);
    void readPath(ItemType stuff);
    void reset(){theList.clear();results.resize(0);}
};

template <class ItemType>
void Dijkstra<ItemType>::solve(int hashA, int hashB){

}

template <class ItemType>
bool Dijkstra<ItemType>::insert(string cityA, double dist, string cityB){ //CHANGE THIS TO ADD()
    
    int tempA = performCyclic(cityA);
    int tempB = performCyclic(cityB);
    
    //########### Create a new vertex if it doesnt exist ###########
    theListIterator = theList.begin();
    if (theListIterator.find(tempA)==theList.end()){
        theList[tempA] = new Vertex<ItemType>;
        this->numberOfVertices++;
    }
    theListIterator = theList.begin();
    if (theListIterator.find(tempB)==theList.end()){
        theList[tempB] = new Vertex<ItemType>;
        this->numberOfVertices++;
    }
    
//    ########### Connects the two vertex ###########
    theList[tempA]->connect(theList[tempB],dist);
    theList[tempB]->connect(theList[tempA],dist);
    
    this->numberOfEdges++;
    
}

template <class ItemType>
void Dijkstra<ItemType>::readPath(ItemType stuff){
    int temp = performCyclic(stuff);
    results.push_back(*(theList[temp]));
}

template <class ItemType>
bool Dijkstra<ItemType>::findShortestPath(string cityA, string cityB){
    int hashA, hashB;
    hashA = performCyclic(cityA);
    hashB = performCyclic(cityB);
    
//  ########### Make sure I'm not retarded ###########
    theListIterator = theList.begin();
    if (theListIterator.find(hashA) == theList.end())
        return false;
    theListIterator = theList.begin();
    if (theListIterator.find(hashB) == theList.end())
        return false;
    
//  ########### re-reads all cities starting at the selected city ###########
    this->breadthFirstTraversal(*(theList[hashA]),&readPath);
    
//    ########### Initialize all weight to inf ###########
    for (int x = 0; x < results.size(); x++) {
        weight.push_back(inf);
    }
    
    
//    Recalculate weight
//    Choose lightest
//    Mark Done
    
    bool found = false;
    
    return true;
}



#endif