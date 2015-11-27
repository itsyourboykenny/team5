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
#include "LinkedGraph.h"
#include "Dijkstra.h"


using namespace std;

bool openInputFile(ifstream&ifs);
bool readInputFile(ifstream&ifs);
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
	ifstream inputFile;

	if (!readInputFile(inputFile))
	{
		cout << "Cannot open the files. Closing the program!" << endl;
		return 1;
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

bool readInputFile(ifstream&ifs)
{
	if (!openInputFile(ifs))
		return false;
	string cityA, cityB;
	double dist;
	Dijkstra<string> *path = 0;
	while (true)
	{		
		if (!getline(ifs, cityA,','))
			break;
		if (!getline(ifs, cityB,','))
			break;
		if (!(ifs >> dist))
			break;
		ifs.ignore();

		cout << cityA << " " << cityB << " " << dist << endl;
		convertTolower(cityA);
		convertTolower(cityB);
		cout << cityA << " " << cityB << " " << dist << endl;
		path->add(cityA, dist, cityB);
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
