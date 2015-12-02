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

void graphTest(LinkedGraph<string>* testGraph)
{
	string A("A");
	string B("B");
	string C("C");
	string D("D");
	string E("E");
	string F("F");
	string G("G");
	string H("H");
	string I("I");
	string J("J");
	string K("K");
	string L("L");
	string M("M");
	string N("N");

	testGraph->add(A, B, 0);
	testGraph->add(A, C, 0);
	testGraph->add(A, D, 0);
	testGraph->add(B, E, 0);
	testGraph->add(B, F, 0);
	testGraph->add(C, G, 0);
	testGraph->add(D, H, 0);
	testGraph->add(D, I, 0);
	testGraph->add(F, J, 0);
	testGraph->add(G, K, 0);
	testGraph->add(G, L, 0);
	testGraph->add(H, M, 0);
	testGraph->add(I, M, 0);
	testGraph->add(I, N, 0);

	cout << "Vertices :" << testGraph->getNumVertices() << endl;
	cout << "Edges :" << testGraph->getNumEdges() << endl;

	cout << "\nDepth-first traversal (should be A B E F J C G K L D H M I N):" << endl;
	testGraph->depthFirstTraversal(A, display);

	cout << "\nBreadth-first traversal (should be A B C D E F G H I J K L M N):" << endl;
	testGraph->breadthFirstTraversal(A, display);
}  // end graphTest

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
		cin.ignore();
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
		case 4: undoRemoval(delivery);
			break;
		case 5: showPaths(delivery);
			break;
		case 6: findShortestPath(delivery);
			break;
		}
		cout << "Would you like to perform another action? (1 for yes, 0 for no): ";
		cin >> answer;
		cin.ignore();
		while (cin.fail())
		{
			cout << "ERROR: Please enter 1 or 0: ";
			cin >> answer;
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
	cout << "**" << endl;
	string cityA, cityB;
	int dist;
	path = new Dijkstra<string>;
	while (true)
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
		cout << cityA << " " << cityB << " " << dist << endl;
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
	cout << "City B : ";
	getline(cin, cityB);
	cout << "Distance between them : ";
	cin >> dist;
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
void undoRemoval(Dijkstra<string> *path)
{

}
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
/*
Testing Graph . . . .
Vertices :14
Edges :14
Depth-first traversal (should be A B E F J C G K L D H M I N):
Displaying item - A
Displaying item - B
Displaying item - E
Displaying item - F
Displaying item - J
Displaying item - C
Displaying item - G
Displaying item - K
Displaying item - L
Displaying item - D
Displaying item - H
Displaying item - M
Displaying item - I
Displaying item - N
Breadth-first traversal (should be A B C D E F G H I J K L M N):
Displaying item - A
Displaying item - B
Displaying item - C
Displaying item - D
Displaying item - E
Displaying item - F
Displaying item - G
Displaying item - H
Displaying item - I
Displaying item - J
Displaying item - K
Displaying item - L
Displaying item - M
Displaying item - N
*/