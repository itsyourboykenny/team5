//  **** Team: 5 ****
//  - Benjamen Neduva
//  - Ye-Eun Myung
//  - Ken Ishiguro

/*
This program gets the airdistance input file from the user and displays the
menu to the user for seven options: open new delivery route, add, remove, undo,
show pathes, find the shortest path, and write the graph to the output file.
*/
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

int main()
{
	Dijkstra<string> delivery;
    ifstream inputFile;
    bool answer = 1;	// bool answer to ask the user for another answer
    int choice; // menu choice
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
			<< "6. find the shortest delivery route" << endl
			<< "7. Create an output file" << endl;
        choice = inputInt();
        while (choice < 1 || choice > 8 || cin.fail())
        {
            cout << "ERROR: Please enter a choice between 1 and 6: ";
            choice = inputInt();
        }
        switch (choice)
        {
            case 1: if (false)
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
			case 7: createOutput(delivery);
				break;
        }
        cout << "Would you like to perform another action? (Y for yes, N for no): ";
        answer = inputBool();
    }
    
    /*
     Dijkstra<string>* myGraph = new Dijkstra<string>();
     cout << "Testing Graph . . . ." << endl << endl;
     graphTest(myGraph);*/

	return 0;
}  // end main