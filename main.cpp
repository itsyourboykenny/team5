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

int main()
{
	Dijkstra<string> delivery;
    ifstream inputFile;
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
			<< "6. find the shortest delivery route" << endl
			<< "7.Please indicate the file name you wish the route to have" << endl;
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
    
    system("PAUSE");
    return 0;
}  // end main