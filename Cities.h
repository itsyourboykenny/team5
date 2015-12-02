//
//  Cities.h
//  Dijkstra
//
//  Created by Ken Ishiguro on 11/24/15.
//  Copyright © 2015 Ken Ishiguro. All rights reserved.
//

#ifndef Cities_h
#define Cities_h
#include <iostream>
#include <vector>
#include "Distance.h"
using namespace std;

class cities : public distance{
private:
	string name = "";
	vector<distance> point;


public:
	int cityCount = 0;

	cities(){}
	cities(string nm){ name = nm; }
	cities(string nm, cities* dst, double dist)
	{
		name = nm;
		point[cityCount++].setCity(dst);
		point[cityCount].setDist(dist);
	}
	~cities();

	string getName()const { return name; }
	void addCity(cities* dst, double dist);
	vector<distance> *getDestinations(){ return &point; }
};

void cities::addCity(cities* dst, double dist){
	if (cityCount < 1){
		point[cityCount].setCity(dst);
		point[cityCount++].setDist(dist);
	}
	else{
		point.push_back(distance(dst, dist));
		cityCount = (int)point.size();
	}
}


#endif /* Cities_h */