//
//  main.h
//  Dijkstra
//
//  Created by Ken Ishiguro on 12/4/15.
//  Copyright © 2015 Ken Ishiguro. All rights reserved.
//

#ifndef main_h
#define main_h
#include <iomanip>

void display(string& anItem)
{
    cout << "Displaying item - " << anItem << endl;
}

int inputInt(){
    string temp;
    getline(cin, temp);
    if (temp.back()=='\n'||temp.back()=='\r') temp.pop_back();
    if (temp > "6" || temp < "1")
        return -1;
    else
        return stoi(temp);
    
}

bool inputBool(){
    string temp;
    getline(cin, temp);
    if (temp.back()=='\n'||temp.back()=='\r') temp.pop_back();
    if (temp == "Y" || temp == "y")
        return true;
    else
        return false;
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

//bool readInputFile(ifstream&ifs, Dijkstra<string> &path){
//    if (!openInputFile(ifs))
//        return false;
//    string cityA, cityB;
//    int dist;
//    
//    while (true)
//    {
//        if (!getline(ifs, cityA, ','))
//            break;
//        if (!getline(ifs, cityB, ','))
//            break;
//        if (!(ifs >> dist))
//            break;
//        
//        cout << cityA << " " << cityB << " " << dist << endl;
//        /*convertTolower(cityA);
//         convertTolower(cityB);*/
//        path.add(cityA, cityB, dist);
////        ifs.ignore();
//        
//    }
//    
//    return true;
//    
//} // end readInputFile

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
    cout << endl;
    cout << "City B : ";
    getline(cin, cityB);
    cout << endl;
    cout << "Distance between them : ";
    cin >> dist;
//    cin.ignore(80, '\n');
    cout << endl;
    path.add(cityA, cityB, dist);
}

void removePath(Dijkstra<string> &path)
{
    string cityA,
    cityB;
    cout << "Please indicate which two cities you wish to disconnect : " << endl
    << "City A : ";
    getline(cin, cityA);
    cout << "City B : ";
    getline(cin, cityB);
    path.remove(cityA, cityB);
}

/*void undoRemoval()
 =======
 void undoRemoval(Dijkstra<string> &path)
 {
 }*/
void showPaths(Dijkstra<string> &path)
{
//    cout << "City A           City B           distance" << endl
//    << "-------          -------          --------" << endl;
    
    path.readPath();
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
    if (shortestlist.empty()) {
        return false;
    }
    
    int totalWeight = 0;
//    int tempWeight;
    cout << "The shortest route from " << cityA << " to " << cityB << " is: \n";
    int l = 15;
    for (int g = 0; g < shortestlist.size()-1; g++){
        cout << setw(l) << right << shortestlist[g].first << " -> " << setw(l) << left << shortestlist[g+1].first <<
        " w/ distance of: " <<shortestlist[g+1].second << endl;
    }
    
//    for (int i = 0; i < shortestlist.size(); i++)
//    {
//        cout << shortestlist[i].first;
//        if ((i + 1) < shortestlist.size())
//        {
//            cout << " -> " << shortestlist[i + 1] << " = ";
//            tempWeight = path.readWeight(shortestlist[i].data(), shortestlist[i + 1].data());
//            cout << tempWeight << " miles" << endl;
//            totalWeight += tempWeight;
//        }
//    }
    
    for (int p = 0; p < shortestlist.size()-1; p++) {
        totalWeight+=shortestlist[p+1].second;
    }
    cout << "And the total distance is: " << totalWeight << " miles" << endl;
    return true;
}

#endif /* main_h */
