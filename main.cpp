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
#include "main.h"


using namespace std;
//map<string, vector<string>*> ourMap;
//map<string, vector<string>*>::iterator ourMapIterator;
//void newPath(Dijkstra<string> *path);
//void removePath(Dijkstra<string> *path);
//void undoRemoval(Dijkstra<string> *path);
//void showPaths(Dijkstra<string> *path);
//void findShortestPath(Dijkstra<string> *path);



//bool openInputFile(ifstream&ifs);
//bool readInputFile(ifstream&ifs, Dijkstra<string> *path);
//void convertTolower(string &s);
//void displayShortestPath(vector<string> list, string cityA, string cityB);

//************* I moved function definitions to a header file ***************

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
	if (!readInputFile(inputFile, test1))
    {
        cout << "Cannot open the files. Closing the program!" << endl;
        return 1;
    }
    //inputFile.open("/Users/itsyourboykenny/Desktop/Dijkstra/Team5 Dijkstra/airdistance.txt");
    //readInputFile(inputFile, test1);
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
        choice = input("menu");
        while (choice < 1 || choice > 7 || cin.fail())
        {
            cout << "ERROR: Please enter a choice between 1 and 6: ";
            choice = input("menu");
        }
        switch (choice)
        {
            case 1: if (false)
            {
                cout << "Cannot open the files. Closing the program!" << endl;
                return 1;
            }
                break;
            case 2: newPath(test1);
                break;
            case 3: removePath(test1);
                break;
//            case 4: undoRemoval(test1);
                break;
            case 5: showPaths(test1);
                break;
            case 6: findShortestPath(test1);
                break;
        }
        cout << "Would you like to perform another action? (1 for yes, 0 for no): ";
        answer = input("answer");
		while (answer != 0 || answer != 1)
		{
			cout << "ERROR: Please enter 1 or 0: ";
			answer = input("answer");

		}
        //while (cin.fail())
        //{
        //    cout << "ERROR: Please enter 1 or 0: ";
        //    input(answer);
        //}
    }
    
    /*
     Dijkstra<string>* myGraph = new Dijkstra<string>();
     cout << "Testing Graph . . . ." << endl << endl;
     graphTest(myGraph);*/
    
    system("PAUSE");
    return 0;
}  // end main