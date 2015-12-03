//
//  Distance.h
//  Dijkstra
//
//  Created by Ken Ishiguro on 11/24/15.
//  Copyright © 2015 Ken Ishiguro. All rights reserved.
//

#ifndef Distance_h
#define Distance_h
#include "Cities.h"

class cities;

class distance{
private:
	double dist = 0;
	cities *nextCity = nullptr;
public:
	distance();
	distance(cities *cit, double dis){ dist = dis; nextCity = cit; }
	//    ~distance();
	double getdist()const { return dist; }
	cities *getCity()const { return nextCity; }
	void setDist(double crap){ dist = crap; }
	void setCity(cities *stuff){ nextCity = stuff; }
};


#endif /* Distance_h */