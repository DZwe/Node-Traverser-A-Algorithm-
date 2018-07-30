// Import headers
#include <iostream>
#include "map.h"
#include "fstream"
#include "node.h"
#include "iomanip"
using namespace std;

// Main Function

int main() {

    // Declare variables
    string connections;
    string locations;

    bool build;

    string x;

    map myGraph;

    string start_city;
    string end_city;

    char heuristic;
    char choice;

    string q;

    // Ask user for path of locations.txt
    cout << "Please, enter locations file path!" << endl
    << " Example: \"myDocs/myTestFiles/locations.txt\"" << endl << endl
    << "Location file(or \"q\"): ";

    cin >> locations;

    // Enter q to quit.
    if (!connections.compare("q"))
        return 0;

    // Ask user for path of connections.txt
    cout << "enter \"q\" any time to terminate..." << endl;
    cout << "Please, enter connections file path!" << endl
    << " Example: \"myDocs/myTestFiles/connections.txt\"" << endl << endl
    << "Connection file(or \"q\"): ";

    cin >> connections;

    if (!connections.compare("q"))
        return 0;

    // Ask user for preference
    cout << "Enter the start city: ";
    cin  >> start_city;

    cout << "Enter the end city: ";
    cin  >> end_city;

    cout << "Enter straight line or fewest link (s or f): ";
    cin  >> heuristic;

    cout << "Enter automatic or manual (a or m): ";
    cin  >> choice;

    // Start building the map.
    build = myGraph.build_map(connections, locations);

    // Fewest link function
    if (heuristic == 'f')
        myGraph.fewestLinks(start_city, end_city, choice);

    // Straight Line Distance function
    if (heuristic == 's')
        myGraph.straightLine(start_city, end_city, choice);

    if (build)
        cout << "Build sucessfull!" << endl;
    else
        cout << "Build failed!" << endl;

    return 0;

}
