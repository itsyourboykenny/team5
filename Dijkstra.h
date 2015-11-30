#ifndef _DIJKSTRA
#define _DIJKSTRA

#include <vector>
#include <map>
#include "LinkedGraph.h"
#include <math.h>
#include "CRC.h"
#include "Node.h"
#include "Vertex.h"
using namespace std;
const double inf = 1 << 30;


template <class LabelType>
class Dijkstra: public LinkedGraph<LabelType>{
    
private:
    
    double Totalweight = 0;
    
//    Using this to make chart
//    alternative is to use vector<vector Vertex>
    class Var{
    public:
        Vertex<LabelType> city;
        double weight = inf;
        
        Var(const Vertex<LabelType> copy){city = copy;}
        ~Var();
    };
    
    vector<Var*> results;
    
public:
    Dijkstra(){results.resize(0);}
    Dijkstra(const Dijkstra &source){/*\(. .\) to the windowww.. (/. .)/ to the walls*/;}
    ~Dijkstra(){reset();}
    bool add(LabelType start, LabelType end, int edgeWeight = 0);
    bool findShortestPath(string cityA, string CityB);
    void solve();
    void readPath(LabelType stuff);
    void reset(){this->vertices.clear();results.clear();this->numberOfVertices=this->numberOfEdges=0;}
};

template <class LabelType>
bool Dijkstra<LabelType>::add(LabelType start, LabelType end, int edgeWeight){
    
    int tempA = performCyclic(start);
    int tempB = performCyclic(end);
    
    //########### Create a new vertex if it doesnt exist ###########
    this->pvertexIterator = this->vertices.begin();
    if (this->pvertexIterator.find(tempA)==this->vertices.end()){
        this->vertices[tempA] = new Vertex<LabelType>;
        this->numberOfthis->vertices++;
    }
    this->pvertexIterator = this->vertices.begin();
    if (this->pvertexIterator.find(tempB)==this->vertices.end()){
        this->vertices[tempB] = new Vertex<LabelType>;
        this->numberOfthis->vertices++;
    }
    
//    ########### Connects the two vertex ###########
    this->vertices[tempA]->connect(this->vertices[tempB],edgeWeight);
    this->vertices[tempB]->connect(this->vertices[tempA],edgeWeight);
    
    this->numberOfEdges++;
    
}

template <class LabelType>
void Dijkstra<LabelType>::readPath(LabelType stuff){
    int temp = performCyclic(stuff);
    results.push_back(new Var(*(this->vertices[temp])));
}

template <class LabelType>
bool Dijkstra<LabelType>::findShortestPath(string cityA, string cityB){
    int hashA, hashB;
    hashA = performCyclic(cityA);
    hashB = performCyclic(cityB);
    
//  ########### Make sure I'm not retarded ###########
    this->pvertexIterator = this->vertices.begin();
    if (this->pvertexIterator.find(hashA) == this->vertices.end())
        return false;
    this->pvertexIterator = this->vertices.begin();
    if (this->pvertexIterator.find(hashB) == this->vertices.end())
        return false;
    
//  ########### re-reads all cities starting at the selected city into vertices ###########
    this->breadthFirstTraversal(*(this->vertices[hashA]),&readPath); //breadthFirst because it gets it in order of adjacency
    
    
    solve();
    
    return true;
}


template <class LabelType>
void Dijkstra<LabelType>::solve(){
    
}



#endif