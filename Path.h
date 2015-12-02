/*
two nodes (city A and City B)
distance (weight of edge)
*/
#ifndef PATH_h
#define PATH_h
#include <string>
#include "Node.h"
using namespace std;

class Path
{
private:
	int distance;
	Node<City>* cityA;
	Node<City>* cityB;
	bool isLeaf;
public:
	getWeight();
	getEndVertex();
	
};
#endif


	
