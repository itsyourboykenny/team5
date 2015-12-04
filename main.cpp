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
#include "GraphInterface.h"
#include "Dijkstra.h"


using namespace std;
map<string, vector<string>*> ourMap;
map<string, vector<string>*>::iterator ourMapIterator;
void newPath(Dijkstra<string> *path);
void removePath(Dijkstra<string> *path);
void undoRemoval(Dijkstra<string> *path);
void showPaths(Dijkstra<string> *path);
void findShortestPath(Dijkstra<string> *path);

template <class whatever>
void input(whatever &stuff){
    cin >> stuff;
    cin.ignore();
}


bool openInputFile(ifstream&ifs);
bool readInputFile(ifstream&ifs, Dijkstra<string> *path);
void convertTolower(string &s);
void displayShortestPath(vector<string> list, string cityA, string cityB);

void display(string& anItem)
{
    cout << "Displaying item - " << anItem << endl;
}


int main()
{
//    Dijkstra<string> *delivery = new Dijkstra<string>;
    Dijkstra<string> test1;
    ifstream inputFile;
    /* 
     7) Please indicate the file name you wish the route to have
     File Name: ____
     */
    
    bool answer = 1;
    int choice;
	if (!readInputFile(inputFile, &test1))
    {
        cout << "Cannot open the files. Closing the program!" << endl;
        return 1;
    }
    //inputFile.open("/Users/itsyourboykenny/Desktop/Dijkstra/Team5 Dijkstra/airdistance.txt");
    //readInputFile(inputFile, &test1);
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
        input(choice);
        while (choice < 1 || choice > 7 || cin.fail())
        {
            cout << "ERROR: Please enter a choice between 1 and 6: ";
            input(choice);
        }
        switch (choice)
        {
            case 1: if (false)
            {
                cout << "Cannot open the files. Closing the program!" << endl;
                return 1;
            }
                break;
            case 2: newPath(&test1);
                break;
            case 3: removePath(&test1);
                break;
            case 4: //undoRemoval(&test1);
                break;
            case 5: showPaths(&test1);
                break;
            case 6: findShortestPath(&test1);
                break;
        }
        cout << "Would you like to perform another action? (1 for yes, 0 for no): ";
        input(answer);
        while (cin.fail())
        {
            cout << "ERROR: Please enter 1 or 0: ";
            input(answer);
        }
    }
    
    /*
     Dijkstra<string>* myGraph = new Dijkstra<string>();
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
    
    //ifs.open("/Users/itsyourboykenny/Desktop/Dijkstra/Team5 Dijkstra/airdistance.txt");
    //return ifs.is_open();
    
} // end openInputFile

//bool readInputFile(ifstream &ifs, Dijkstra<string> *path)
//{
//   if (!openInputFile(ifs))
//     return false;
//    string  cityA,
//            cityB;
//    int     dist;
//    
//    while (ifs.peek() != EOF){
//        ifs >> cityA >> cityB;
//        ifs >> dist;
//        path->add(cityA, cityB, dist);
//    }
//    return true;
//}

bool readInputFile(ifstream&ifs, Dijkstra<string> *path){
    if (!openInputFile(ifs))
        return false;
    string cityA, cityB;
    int dist;
    
    while (true)
    {
        if (!getline(ifs, cityA, ','))
            break;
        if (!getline(ifs, cityB, ','))
            break;
        if (!(ifs >> dist))
            break;
        
        cout << cityA << " " << cityB << " " << dist << endl;
        /*convertTolower(cityA);
         convertTolower(cityB);*/
        path->add(cityA, cityB, dist);
		ifs.ignore();

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


void newPath(Dijkstra<string> *path)
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
void removePath(Dijkstra<string> *path)
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
 {
 }*/
void showPaths(Dijkstra<string> *path)
{
    cout << "City A    City B    distance" << endl
    << " ------    ------    --------" << endl;
    for (ourMapIterator = ourMap.begin(); ourMapIterator != ourMap.end(); ourMapIterator++)
    {
        cout << ourMapIterator->first << endl;
    }
}
void findShortestPath(Dijkstra<string> *path)
{
    string cityA,
    cityB;
    int distance;
    cout << "Please indicate which two cities you wish to find the shortest path for : " << endl
    << "City A : ";
    getline(cin, cityA);
    cout << "City B : ";
    getline(cin, cityB);
    vector<string> shortestlist = path->findShortestPath(cityA, cityB);

	int totalWeight = 0;
	int tempWeight;
	cout << "The shortest route from " << cityA << " to " << cityB << " is: \n";
	for (int i = 0; i < shortestlist.size(); i++)
	{
		cout << shortestlist[i].data();
		if ((i + 1) < shortestlist.size())
		{
			cout << " -> " << shortestlist[i + 1] << " = ";
			tempWeight = path->readWeight(shortestlist[i].data(), shortestlist[i + 1].data());
			cout << tempWeight << " miles" << endl;
			totalWeight += tempWeight;
		}
	}
	cout << "And the total distance is: " << totalWeight << " miles" << endl;
	
}