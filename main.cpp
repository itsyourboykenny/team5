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

/*
Enter the input filename: airdistance.txt
Welcome to  the delivery simulation!
Please choose an option :
1. Open a new delivery route
2. add a new delivery path
3. remove a delivery path
4. undo removal of delivery path
5. Show possible delivery paths
6. find the shortest delivery route
7. Create an output file
0
ERROR: Please enter a choice between 1 and 6: 8
ERROR: Please enter a choice between 1 and 6: 5
City A         City B         Distance
*********************************************
Brasilia       MexicoCity     4244
Paris          5369
Pretoria       4888
---------------------------------------------
MexicoCity     Brasilia       4244
Washington     1874
---------------------------------------------
Moscow         NewDelhi       2708
Paris          1552
Seoul          4134
---------------------------------------------
NewDelhi       Moscow         2708
Paris          4111
Seoul          2927
Sydney         6459
---------------------------------------------
Ottawa         Paris          3510
Washington     471
---------------------------------------------
Paris          Brasilia       5369
Moscow         1552
NewDelhi       4111
Ottawa         3510
Pretoria       5354
Washington     3848
---------------------------------------------
Pretoria       Brasilia       4888
Paris          5354
Sydney         6907
---------------------------------------------
Seoul          Moscow         4134
NewDelhi       2927
Sydney         5138
---------------------------------------------
Sydney         NewDelhi       6459
Pretoria       6907
Seoul          5138
---------------------------------------------
Washington     MexicoCity     1874
Ottawa         471
Paris          3848
---------------------------------------------
How would you like to view the list of the cities?
1. Depth-First Traversal
2. Breadth-First Traversal
3
ERROR: Please enter a choice between 1 and 2: 0
ERROR: Please enter a choice between 1 and 2: 1
Displaying city - Brasilia
Displaying city - MexicoCity
Displaying city - Washington
Displaying city - Ottawa
Displaying city - Paris
Displaying city - Moscow
Displaying city - NewDelhi
Displaying city - Seoul
Displaying city - Sydney
Displaying city - Pretoria
Would you like to perform another action? (Y for yes, N for no):

ERROR: Please enter 'Y' or 'y' for yes and 'N' or 'n' for no: p

ERROR: Please enter 'Y' or 'y' for yes and 'N' or 'n' for no: 0

ERROR: Please enter 'Y' or 'y' for yes and 'N' or 'n' for no: y

Welcome to  the delivery simulation!
Please choose an option :
1. Open a new delivery route
2. add a new delivery path
3. remove a delivery path
4. undo removal of delivery path
5. Show possible delivery paths
6. find the shortest delivery route
7. Create an output file
2
Please indicate which two cities you wish to connect :
City A : SanFrancisco

City B : Washington

Distance between them : 2442

Would you like to perform another action? (Y for yes, N for no): y

Welcome to  the delivery simulation!
Please choose an option :
1. Open a new delivery route
2. add a new delivery path
3. remove a delivery path
4. undo removal of delivery path
5. Show possible delivery paths
6. find the shortest delivery route
7. Create an output file
5
City A         City B         Distance
*********************************************
Brasilia       MexicoCity     4244
Paris          5369
Pretoria       4888
---------------------------------------------
MexicoCity     Brasilia       4244
Washington     1874
---------------------------------------------
Moscow         NewDelhi       2708
Paris          1552
Seoul          4134
---------------------------------------------
NewDelhi       Moscow         2708
Paris          4111
Seoul          2927
Sydney         6459
---------------------------------------------
Ottawa         Paris          3510
Washington     471
---------------------------------------------
Paris          Brasilia       5369
Moscow         1552
NewDelhi       4111
Ottawa         3510
Pretoria       5354
Washington     3848
---------------------------------------------
Pretoria       Brasilia       4888
Paris          5354
Sydney         6907
---------------------------------------------
SanFrancisco   Washington     2442
---------------------------------------------
Seoul          Moscow         4134
NewDelhi       2927
Sydney         5138
---------------------------------------------
Sydney         NewDelhi       6459
Pretoria       6907
Seoul          5138
---------------------------------------------
Washington     MexicoCity     1874
Ottawa         471
Paris          3848
SanFrancisco   2442
---------------------------------------------
How would you like to view the list of the cities?
1. Depth-First Traversal
2. Breadth-First Traversal
2
Displaying city - Brasilia
Displaying city - MexicoCity
Displaying city - Paris
Displaying city - Pretoria
Displaying city - Washington
Displaying city - Moscow
Displaying city - NewDelhi
Displaying city - Ottawa
Displaying city - Sydney
Displaying city - SanFrancisco
Displaying city - Seoul
Would you like to perform another action? (Y for yes, N for no): y

Welcome to  the delivery simulation!
Please choose an option :
1. Open a new delivery route
2. add a new delivery path
3. remove a delivery path
4. undo removal of delivery path
5. Show possible delivery paths
6. find the shortest delivery route
7. Create an output file
3
Please indicate which two cities you wish to disconnect :
City A : Seoul
City B : Sydney
Would you like to perform another action? (Y for yes, N for no): y

Welcome to  the delivery simulation!
Please choose an option :
1. Open a new delivery route
2. add a new delivery path
3. remove a delivery path
4. undo removal of delivery path
5. Show possible delivery paths
6. find the shortest delivery route
7. Create an output file
5
City A         City B         Distance
*********************************************
Brasilia       MexicoCity     4244
Paris          5369
Pretoria       4888
---------------------------------------------
MexicoCity     Brasilia       4244
Washington     1874
---------------------------------------------
Moscow         NewDelhi       2708
Paris          1552
Seoul          4134
---------------------------------------------
NewDelhi       Moscow         2708
Paris          4111
Seoul          2927
Sydney         6459
---------------------------------------------
Ottawa         Paris          3510
Washington     471
---------------------------------------------
Paris          Brasilia       5369
Moscow         1552
NewDelhi       4111
Ottawa         3510
Pretoria       5354
Washington     3848
---------------------------------------------
Pretoria       Brasilia       4888
Paris          5354
Sydney         6907
---------------------------------------------
SanFrancisco   Washington     2442
---------------------------------------------
Seoul          Moscow         4134
NewDelhi       2927
---------------------------------------------
Sydney         NewDelhi       6459
Pretoria       6907
---------------------------------------------
Washington     MexicoCity     1874
Ottawa         471
Paris          3848
SanFrancisco   2442
---------------------------------------------
How would you like to view the list of the cities?
1. Depth-First Traversal
2. Breadth-First Traversal
1
Displaying city - Brasilia
Displaying city - MexicoCity
Displaying city - Washington
Displaying city - Ottawa
Displaying city - Paris
Displaying city - Moscow
Displaying city - NewDelhi
Displaying city - Seoul
Displaying city - Sydney
Displaying city - Pretoria
Displaying city - SanFrancisco
Would you like to perform another action? (Y for yes, N for no): y

Welcome to  the delivery simulation!
Please choose an option :
1. Open a new delivery route
2. add a new delivery path
3. remove a delivery path
4. undo removal of delivery path
5. Show possible delivery paths
6. find the shortest delivery route
7. Create an output file
4
Would you like to perform another action? (Y for yes, N for no): y

Welcome to  the delivery simulation!
Please choose an option :
1. Open a new delivery route
2. add a new delivery path
3. remove a delivery path
4. undo removal of delivery path
5. Show possible delivery paths
6. find the shortest delivery route
7. Create an output file
5
City A         City B         Distance
*********************************************
Brasilia       MexicoCity     4244
Paris          5369
Pretoria       4888
---------------------------------------------
MexicoCity     Brasilia       4244
Washington     1874
---------------------------------------------
Moscow         NewDelhi       2708
Paris          1552
Seoul          4134
---------------------------------------------
NewDelhi       Moscow         2708
Paris          4111
Seoul          2927
Sydney         6459
---------------------------------------------
Ottawa         Paris          3510
Washington     471
---------------------------------------------
Paris          Brasilia       5369
Moscow         1552
NewDelhi       4111
Ottawa         3510
Pretoria       5354
Washington     3848
---------------------------------------------
Pretoria       Brasilia       4888
Paris          5354
Sydney         6907
---------------------------------------------
SanFrancisco   Washington     2442
---------------------------------------------
Seoul          Moscow         4134
NewDelhi       2927
Sydney         5138
---------------------------------------------
Sydney         NewDelhi       6459
Pretoria       6907
Seoul          5138
---------------------------------------------
Washington     MexicoCity     1874
Ottawa         471
Paris          3848
SanFrancisco   2442
---------------------------------------------
How would you like to view the list of the cities?
1. Depth-First Traversal
2. Breadth-First Traversal
2
Displaying city - Brasilia
Displaying city - MexicoCity
Displaying city - Paris
Displaying city - Pretoria
Displaying city - Washington
Displaying city - Moscow
Displaying city - NewDelhi
Displaying city - Ottawa
Displaying city - Sydney
Displaying city - SanFrancisco
Displaying city - Seoul
Would you like to perform another action? (Y for yes, N for no): y

Welcome to  the delivery simulation!
Please choose an option :
1. Open a new delivery route
2. add a new delivery path
3. remove a delivery path
4. undo removal of delivery path
5. Show possible delivery paths
6. find the shortest delivery route
7. Create an output file
6
Please indicate which two cities you wish to find the shortest path for :
City A : Seoul
City B : Ottawa
The shortest route from Seoul to Ottawa is:
Seoul -> Moscow          w/ distance of: 4134
Moscow -> Paris           w/ distance of: 1552
Paris -> Ottawa          w/ distance of: 3510
And the total distance is: 9196 miles
Would you like to perform another action? (Y for yes, N for no): y

Welcome to  the delivery simulation!
Please choose an option :
1. Open a new delivery route
2. add a new delivery path
3. remove a delivery path
4. undo removal of delivery path
5. Show possible delivery paths
6. find the shortest delivery route
7. Create an output file
7
File name: outputfile.txt
Would you like to perform another action? (Y for yes, N for no): n

Press any key to continue . . .
*/