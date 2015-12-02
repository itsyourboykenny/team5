//  **** Team: 5 ****
//  - Benjamen Neduva
//  - Ye-Eun Myung
//  - Ken Ishiguro

//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

#include <iostream>
#include <string>
#include<fstream>
#include<string>
#include <vector>
#include "LinkedGraph.h"
#include "Dijkstra.h"


using namespace std;
map<string, vector<string>*> ourMap;
map<string, vector<string>*>::iterator ourMapIterator;
void newPath(Dijkstra<string> *path);
void removePath(Dijkstra<string> *path);
void undoRemoval(Dijkstra<string> *path);
void showPaths(Dijkstra<string> *path);
void findShortestPath(Dijkstra<string> *path);


bool openInputFile(ifstream&ifs);
bool readInputFile(ifstream&ifs, Dijkstra<string> *path);
void convertTolower(string &s);
void display(string& anItem)
{
	cout << "Displaying item - " << anItem << endl;
}


int main()
{
	Dijkstra<string>* delivery = new Dijkstra<string>;
	ifstream inputFile;
	/*
	7) Please indicate the file name you wish the route to have
	File Name: ____
	*/

	bool answer = 1;
	int choice;
	if (!readInputFile(inputFile, delivery))
	{
		cout << "Cannot open the files. Closing the program!" << endl;
		return 1;
	}
	while (answer)
	{
		cout << "Welcome to  the delivery simulation!" << endl
			<< "Please choose an option :" << endl
			<< "1. Open a new delivery route" << endl
			<< "2. add a new delivery path" << endl
			<< "3. remove a delivery path" << endl
			<< "4. undo removal of delivery path" << endl
			<< "5. Show possible delivery paths" << endl
			<< "6. find the shortest delivery route" << endl;
		cin >> choice;
		cin.ignore(80, '\n');
		while (choice < 1 || choice > 7 || cin.fail())
		{
			cout << "ERROR: Please enter a choice between 1 and 6: ";
			cin >> choice;
		}
		switch (choice)
		{
		case 1: if (!readInputFile(inputFile, delivery))
		{
			cout << "Cannot open the files. Closing the program!" << endl;
			return 1;
		}
				break;
		case 2: newPath(delivery);
			break;
		case 3: removePath(delivery);
			break;
		case 4: //undoRemoval(delivery);
			break;
		case 5: showPaths(delivery);
			break;
		case 6: findShortestPath(delivery);
			break;
		}
		cout << "Would you like to perform another action? (1 for yes, 0 for no): ";
		cin >> answer;
		cin.ignore(80, '\n');
		while (cin.fail())
		{
			cout << "ERROR: Please enter 1 or 0: ";
			cin >> answer;
			cin.ignore(80, '\n');
		}
	}

	/*
	LinkedGraph<string>* myGraph = new LinkedGraph<string>();
	cout << "Testing Graph . . . ." << endl << endl;
	graphTest(myGraph);*/

	system("PAUSE");
	return 0;
}  // end main

bool openInputFile(ifstream&ifs)
{
	string filename;
	cout << "Enter the input filename: ";

	getline(cin, filename);
	ifs.open(filename.c_str());
	return ifs.is_open();
} // end openInputFile

bool readInputFile(ifstream&ifs, Dijkstra<string> *path)
{
	if (!openInputFile(ifs))
		return false;
	string cityA, cityB;
	int dist;

	while (!(ifs.eof()))
	{
		if (!getline(ifs, cityA, ','))
			break;
		if (!getline(ifs, cityB, ','))
			break;
		if (!(ifs >> dist))
			break;
		ifs.ignore();

		cout << cityA << " " << cityB << " " << dist << endl;
		/*convertTolower(cityA);
		convertTolower(cityB);*/
		path->add(cityA, cityB, dist);
	}

	return true;

} // end readInputFile

void convertTolower(string &s)
{
	for (int i = 0; i < s.length(); i++)
	{
		s[i] = tolower(s[i]);
	}
}


void newPath(Dijkstra<string>* path)
{
	string cityA,
		cityB;
	int dist;
	cout << "Please indicate which two cities you wish to connect : " << endl
		<< "City A : ";
	getline(cin, cityA);
	cout << endl;
	cout << "City B : ";
	getline(cin, cityB);
	cout << endl;
	cout << "Distance between them : ";
	cin >> dist;
	cin.ignore(80, '\n');
	cout << endl;
	path->add(cityA, cityB, dist);
}
void removePath(Dijkstra<string>* path)
{
	string cityA,
		cityB;
	cout << "Please indicate which two cities you wish to disconnect : " << endl
		<< "City A : ";
	getline(cin, cityA);
	cout << "City B : ";
	getline(cin, cityB);
	path->remove(cityA, cityB);
}

/*void undoRemoval()
=======
void undoRemoval(Dijkstra<string> *path)
>>>>>>> 9d522bc87d863b88beecc375b0cb1527b9565215
{
}*/
void showPaths(Dijkstra<string>* path)
{
	cout << "City A    City B    distance" << endl
		<< " ------    ------    --------" << endl;
	for (ourMapIterator = ourMap.begin(); ourMapIterator != ourMap.end(); ourMapIterator++)
	{
		cout << ourMapIterator->first << endl;
	}
}
void findShortestPath(Dijkstra<string>* path)
{
	string cityA,
		cityB;
	double distance;
	cout << "Please indicate which two cities you wish to find the shortest path for : " << endl
		<< "City A : ";
	getline(cin, cityA);
	cout << "City B : ";
	getline(cin, cityB);
	path->findShortestPath(cityA, cityB);
}
