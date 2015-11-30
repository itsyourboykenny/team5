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
    struct item{
        int weight = 0;
        bool done = false;
    };
    map<LabelType, item> sortedList;
    vector<LabelType> chart;
    ofstream *ptrOut;
    void addToChart(LabelType name, int weight, bool done){}
    
public:
    Dijkstra(){ reset();ptrOut = nullptr; }
    Dijkstra(ofstream &outFile){reset();ptrOut = &outFile;}
    Dijkstra(const Dijkstra &source){/*\(. .\) to the windowww.. (/. .)/ to the walls*/; }
    ~Dijkstra(){ reset(); }
    bool add(LabelType start, LabelType end, int edgeWeight);
    Vertex<LabelType>* findShortestPath(LabelType cityA, LabelType cityB);
    Vertex<LabelType>* solve(LabelType end);
    void readPath(LabelType stuff);
    void reset(){ this->vertices.clear(); chart.clear(); sortedList.clear(); this->numberOfVertices = this->numberOfEdges = 0; }
    void refresh(){sortedList.clear();chart.clear();} //Call this before calculation
};

template <class LabelType>
bool Dijkstra<LabelType>::add(LabelType start, LabelType end, int edgeWeight){
    
    //########### Create a new vertex if it doesnt exist ###########
    if (this->vertices.contains(start)){
        this->vertices.add(start, new Vertex<LabelType>(start));
        this->numberOfVertices++;
    }
    if (this->vertices.contains(end)){
        this->vertices.add(end, new Vertex<LabelType>(end));
        this->numberOfVertices++;
    }
    
    //    ########### Connects the two vertex ###########
    (this->vertices.getMap())[start]->connect(end,edgeWeight);
    (this->vertices.getMap())[end]->connect(start,edgeWeight);
    
    this->numberOfEdges++;
    
    return true;
}

template <class LabelType>
void Dijkstra<LabelType>::readPath(LabelType stuff){
    item temp = {inf,false};
    chart.push_back(stuff);
    sortedList[stuff] = temp;
}

template <class LabelType>
Vertex<LabelType>* Dijkstra<LabelType>::findShortestPath(LabelType cityA, LabelType cityB){
    
    //  ########### Make sure I'm not retarded ###########
    if (!this->vertices.contains(cityA))
        return false;
    if (!this->vertices.contains(cityB))
        return false;
    
    //  ########### re-reads all cities starting at the selected city into vertices ###########
    this->breadthFirstTraversal(this->vertices.getMap()[cityA], &readPath); //breadthFirst because it gets it in order of adjacency
    
    return solve();
}


template <class LabelType>
Vertex<LabelType>* Dijkstra<LabelType>::solve(LabelType end){

    int Totalweight = 0;
    int tempWeight = 0;
    int x = 0;
    sortedList[chart[0]].done = true;
    sortedList[chart[0]].weight = 0;
    
    while(!sortedList[end].done && x < chart.size()) {
//        Compare against all possible paths
        for (int y = 0; y < (this->vertices.getMap()[chart[x]])->getNumberOfNeighbors(); y++) {
            LabelType temp = (this->vertices.getMap()[chart[x]])->getNextNeighbor();
            tempWeight = (this->vertices.getMap()[chart[x]])->getEdgeWeight(temp);
            if ((sortedList[temp]).weight > Totalweight+tempWeight)
                if (!sortedList[temp].done)
                    (sortedList[temp]).weight = Totalweight+tempWeight;
        }
//        Determines the lowest cost, assigns if it's smaller, but not if it's marked done
        int smallest = inf;
        int smallPos;
        for (int y = 0; y < chart.size(); y++) {
            if (sortedList[chart[y]].weight < smallest && !sortedList[chart[y]].done) {
                smallest = sortedList[chart[y]].weight;
                smallPos = y;
            }
        }
//        Mark shortest distance as done
        sortedList[chart[smallPos]].done = true;
        Totalweight += sortedList[chart[smallPos]].weight;
        x++;
    }
}



#endif


