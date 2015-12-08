//
//  main.h
//  Dijkstra
//
//  Created by Ken Ishiguro, Ben Neduva, Ye-Eun Myung on 12/4/15.
//  Copyright © 2015 Ken Ishiguro. All rights reserved.
//

#ifndef main_h
#define main_h
#include <iomanip>

void display(string& anItem)
{
    cout << "Displaying city - " << anItem << endl;
}

int inputInt()
{
    string temp;
    getline(cin, temp);
    if (temp.back()=='\n'||temp.back()=='\r') temp.pop_back();
    if (temp > "7" || temp < "1")
        return -1;
    else
        return stoi(temp);
    
}

bool inputBool()
{
    string temp;
 //   if (temp.back()=='\n'||temp.back()=='\r') temp.pop_back();
	do 
	{
		getline(cin, temp);
		cout << endl;
		if (temp == "Y" || temp == "y")
			return true;
		else if (temp == "N" || temp == "n")
			return false;
		cout << "ERROR: Please enter 'Y' or 'y' for yes and 'N' or 'n' for no: ";
	} while (temp != "Y" && temp != "y" && temp != "N" && temp != "n");

}

bool openInputFile(ifstream&ifs)
{
    string filename;
    cout << "Enter the input filename: ";
    getline(cin, filename);
    if (filename.back() == '\n' || filename.back() == '\r') filename.pop_back();
    ifs.open(filename.c_str());
    return ifs.is_open();
    
//    ifs.open("/Users/itsyourboykenny/Google Drive/School/CIS 22C/Dijkstra/Dijkstra/airdistance.txt");
//    return ifs.is_open();
    
} // end openInputFile

bool readInputFile(ifstream &ifs, Dijkstra<string> &path)
{
   if (!openInputFile(ifs))
     return false;
    string  cityA,
            cityB;
    int     dist;

    while (ifs.peek() != EOF){
        ifs >> cityA >> cityB;
        ifs >> dist;
        path.add(cityA, cityB, dist);
    }
    return true;
}

void convertTolower(string &s)
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }
}


void newPath(Dijkstra<string> &path)
{
    string cityA,
    cityB;
    int dist;
    
    cout << "Please indicate which two cities you wish to connect : " << endl
    << "City A : ";
    getline(cin, cityA);
//    if (cityA.back() == '\n' || cityA.back() == '\r'){cityA.pop_back();}
    cout << endl;
    cout << "City B : ";
    getline(cin, cityB);
//    if (cityB.back() == '\n' || cityB.back() == '\r'){cityB.pop_back();}
    cout << endl;
    cout << "Distance between them : ";
    cin >> dist;
    cin.ignore(80, '\n');
    cout << endl;
    path.add(cityA, cityB, dist);
}

void removePath(Dijkstra<string> &path)
{
    string cityA,
    cityB;
	bool flag;
    cout << "Please indicate which two cities you wish to disconnect : " << endl
    << "City A : ";
    getline(cin, cityA);
    cout << "City B : ";
    getline(cin, cityB);
    flag = path.remove(cityA, cityB);

	if (!flag)
	{
		cout << "Cannot find the city or cities\n";
	}
}

void undoRemoval(Dijkstra<string> &path)
{
    path.undoRemove();
}

void showPaths(Dijkstra<string> &path)
{
    path.readPath();
	string city = path.getFirst();
	int traverse;

	cout << "How would you like to view the list of the cities?" << endl;
	cout << "1. Depth-First Traversal" << endl;
	cout << "2. Breadth-First Traversal" << endl;
	cin >> traverse;
	while (traverse < 1 || traverse > 2 || cin.fail())
	{
		cout << "ERROR: Please enter a choice between 1 and 2: ";
		cin >> traverse;
	}
	switch (traverse)
	{
	case 1: path.depthFirstTraversal(city, display);
		break;
	case 2: path.breadthFirstTraversal(city, display);
		break;
	}
	cin.ignore();
	
}
bool findShortestPath(Dijkstra<string> &path)
{
    string cityA,
    cityB;
//    int distance;
    cout << "Please indicate which two cities you wish to find the shortest path for : " << endl
    << "City A : ";
    getline(cin, cityA);
    if (cityA.back() == '\n' || cityA.back() == '\r')
        cityA.pop_back();
    cout << "City B : ";
    getline(cin, cityB);
    if (cityB.back() == '\n' || cityB.back() == '\r')
        cityB.pop_back();

    vector<pair<string, int>> shortestlist = path.findShortestPath(cityA, cityB);
    if (shortestlist.empty()) 
	{
        return false;
    }
    
    int totalWeight = 0;
//    int tempWeight;
    cout << "The shortest route from " << cityA << " to " << cityB << " is: \n";
    int l = 15;
    for (int g = 0; g < shortestlist.size()-1; g++)
	{
        cout << setw(l) << right << shortestlist[g].first << " -> " << setw(l) << left << shortestlist[g+1].first <<
        " w/ distance of: " <<shortestlist[g+1].second << endl;
    }
    
    for (int p = 0; p < shortestlist.size()-1; p++) 
	{
        totalWeight+=shortestlist[p+1].second;
    }
    cout << "And the total distance is: " << totalWeight << " miles" << endl;
    return true;
}

void createOutput(Dijkstra<string> &path)
{
	ofstream ofs;
	string filename;
	cout << "File name: ";
	getline(cin, filename);
	ofs.open(filename.c_str());

	path.writeFile(ofs);
	ofs.close();
}
#endif /* main_h */
