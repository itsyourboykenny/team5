#ifndef _DIJKSTRA
#define _DIJKSTRA

/*
 0. read in data to the appropriate variable (Two city nodes and it's distance)
 
 0. Use a hashtable to store the pointer address for each city?
 So we dont have to connect them manually, if a city that already
 has an address/variable is called, it'll automatically be connected to its
 corresponding city
 
 I've written a CRC hash algorithm already so we dont have to worry about collisions
 
 0. This class only takes city node as input/parameter
 Dijkstra(** Initial Node **)
 then Dijkstra Object -> insertNode(some crap) afterwards
 
 1. create chart (arrayptr -> morearrayptr) or (vector maybe?)
 ** it must expand in one direction
 
 point A | point B | point C | point D
 a   ________|_________|_________|________|
 b   ________|_________|_________|________|
 c   ________|_________|_________|________|
 poop                    ||
 more                    ||
 crap                    \/
 
 2. Always start at node A. Each node must have a linked list of it's connecting node
 
 ex.
 
 +--------+
 |        |
 +--------------+  B     |
 |              |        |
 3              +--+---+-+
 |                 |   |
 |                 |   |
 |                 |   |
 |                 |   |
 +------+                 |   5
 |      |                 |   |
 |A     |                 8   |      +-------+
 |      |                 |   |      |       |
 +--+---+                 |   +------+   C   |
 |                     |          |       |
 |                     |          +----+--+
 |                     |               |
 |                     |               |
 |                     |               |
 9                     |               |
 |                     |               |
 |            +--------++              |
 |            |         |              |
 |            |   D     |              |
 |            |         |              |
 |            +---------+              |
 |                                     |
 |                                     |
 |                                     |
 +-------------------------------------+
 
 *****************************************
 Example for Node A
 *****************************************
 
 class distance{ (or struct maybe?)
 private:
 string connectedTo("hell");
 int distance;
 Node *connectedTo ==> NodeBorC;(only one per distance class)
 public:
 getDistance();
 getNextNode();
 someCrap();
 };
 
 class Node{ (Cities in our case)
 string name("A");
 distance *crap ====> DisToB ====> DisToC;
 };
 
 *****************************************
 
 3. Algorithm T^T
 1. Determin all possible nodes that are adjacent to Node A
 2. Choose path with the shortest weight then input it in the chart for row A(it's marked done) (weight is 0 b/c distance A->A = 0).
 3. Keep a running count of the weight
 4. Say b is shortest and it's 3 miles away from A. Then 0+B = 3; [current weight: 3] (mark 3 for b in chart)
 5. Repeat 4: example b->c is 5 miles apart. weight 3+5=8 (mark 8 for c in chart)
 6. Repeat pattern (currentWeight + next shortest path to unvisited node)
 7. If an unvisited node cant be reached carry down the value of the unmarked node (I'll try and make a better graph)
 
 +-----------------+
 | |A   B   C   D  |
 +----+---+---+-+--+
 |A|0d| 3 | 9 | -  |
 |B|  | 3d| 14| 8  |
 |C|  |   | 14| 8d |
 | |  |   |d14|    |
 +-+--+---+---+----+
 
 8. Each element will contain the distance class
 ** The chart wont always be in order **
 8.5 We use this chart to find shortest distance between two arbitrary nodes from user,
 so I suppose thats why we need a user interface
 9. Make sure to pronounce Dijkstra correctly lol. Imagine him at school during roll call
 
 Sorry I tried to explain as best as I can.
 */

#include <vector>
#include "LinkedGraph.h"
#include <math.h>
#include "Cities.h"
#include "CRC.h"
using namespace std;
const unsigned int TABLE_SIZE = getMaxSize();

template <class ItemType>
class Dijkstra: public LinkedGraph<ItemType>{
    
private:
    cities **hashTable = new cities *[TABLE_SIZE];
    vector<cities> cache;
public:
    Dijkstra();
    bool insert(string cityA, double dist, string cityB);
    
    
};

template <class ItemType>
bool Dijkstra<ItemType>::insert(string cityA, double dist, string cityB){
    
    int tempA = performCyclic(cityA);
    int tempB = performCyclic(cityB);
    
    if ((hashTable)[tempB] == nullptr)
        (hashTable)[tempA] = new cities(cityA);
    
    if ((hashTable)[tempB] == nullptr)
        (hashTable)[tempB] = new cities(cityB);
    
    (*hashTable)[tempA].addCity((hashTable)[tempB], dist);
    (*hashTable)[tempB].addCity((hashTable)[tempA], dist);
    
}



#endif