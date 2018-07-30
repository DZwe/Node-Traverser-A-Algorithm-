
#ifndef map_h
#define map_h

// Import headers
#include "node.h"
#include "vector"
#include "iostream"
#include "fstream"
#include "iomanip"
#include "string.h"
#include <queue>
#include <cmath>
#include <limits>

using namespace std;

#define MAX 99999


class map {
    friend class node;
public:
    
    // Declare variables
    
    node *graph=new node[200];
    vector<string> cities;
    vector<int> x_cords;
    vector<int> y_cords;
    friend class straightLine;
    vector<node *> queue;
    string x;
    vector<string> exception;
    vector<string> excep2;
    string q;
    int time = 0;
    
    // Build map function which builds the map from the provided information
	bool build_map(string connections, string locations)
    {
        // Locations ---------------
        ifstream inputFile; // Open file
        
        inputFile.open(locations);
        
        if (!inputFile)
        {
            cerr << "Unable to open file locations.";
            exit(1);
        }
        
        // Ask user for any cities that wants to be excluded.
        while (1)
        {
            cout << "Enter a city you want to omit (q to stop): ";
            cin >> q;
            
            if (q == "q")
                break;
            
            time++;
            
            exception.push_back(q); // Container for desired exclusion
        }
        
        while (inputFile >> x && x != "END")
        {
            cities.push_back(x); // name of city
            
            inputFile >> x;
            
            x_cords.push_back(stoi(x)); // x-coordinate
            
            inputFile >> x;
            
            y_cords.push_back(stoi(x)); // y-coordinate

        }
        
        inputFile.close(); // close file
        
        // Give the proper information to instantiated nodes
        for (int k = 0; k < cities.size(); k++)
        {
            graph[k].set_name(cities[k]);
            graph[k].set_x(x_cords[k]);
            graph[k].set_y(y_cords[k]);
            
        }
        
        
        //--------------------------
        
        // Connections
        
        ifstream inputFile2; // Open file
        
        inputFile2.open(connections);
        
        if (!inputFile2)
        {
            cerr << "Unable to open file connections.";
            exit(1);
        }

        // Set connections
        while (inputFile2 >> x && x != "END")
        {            
            int i = 0;
            int start = 0;
            int count = 0;
            int node_index = 0;
            
            while (x != graph[i].get_name())
                i++;
        
            if (x == graph[i].get_name())
            {
                inputFile2 >> x;
                count = stoi(x);
                
                while (start < count)
                {
                    node_index = 0;
                    inputFile2 >> x;
                    
                    // START LOOKING FOR NODE
                    while (x != graph[node_index].get_name())
                        node_index++;
                    
                    if (x == graph[node_index].get_name())
                    {
                        graph[i].set_connections(start, &graph[node_index]);
                    }
                    start++;
                }
            }
                
            
            
        }
        
        inputFile2.close();
        
        int number = 0;
        int j = 0;
        string temp;
        string temp2;
        
        // Assign flags for excluded cities
        while (j < cities.size())
        {
                while (number < exception.size())
                {
                    temp = graph[j].get_name();
                    temp2 = exception[number];
                    
                    if (temp == temp2)
                    {
                        graph[j].set_excluded(true);
                        graph[j].set_visited(true);
                    }
                
                    number++;
                }
            j++;
            number = 0;
        }
        
    	return true;
	}
    
    bool fewestLinks(string start_city, string end_city, char choice)
    {
            cout << endl;
            
            
            
            node* start;
            node* end;
        
            // Find the cities
            int i = 0;
            while (graph[i].get_name() != start_city)
                i++;
            
            start = &graph[i];
            
            i = 0;
            while (graph[i].get_name() != end_city)
                i++;
            
            
            end = &graph[i];
        
            // Start printing the path.
            cout << "Heuristic: Fewest Links:" << endl;
            cout << "Starting city: " << start->get_name() << endl;
            cout << "Target city: " << end->get_name() << endl << endl;
            
            node* temp;
            string s;
            s = start->get_name();
            int out = 0;
            int counter = 0;
            
            cout << "Current Optimal Path:" << endl;
            cout << start->get_name() << endl;
            cout << "Distance Traveled: 0.00" << endl << endl;
        
            // If user wants manual, this will make user press enter to continue.
            if (choice == 'm')
                cin.ignore();
        
            // Start traversing
            while (start != end)
            {
                while(counter < 10)
                {
                    start->set_visited(true);
                    temp = start->get_connection(counter);
                    
                    // If there are no more connections, break.
                    if (temp == NULL)
                    {
                        counter = 0;
                        break;
                    }
                    
                    // If it is already visited, skip.
                    if ((temp->get_visited()) == true)
                    {
                        counter++;
                        continue;
                    }
                    
                    // If it is excluded, skip.
                    if ((temp->get_excluded()) == true)
                    {
                        counter++;
                        continue;
                    }
                    
                    temp->set_pred(start);
                    temp->set_visited(true);
                    
                    if (choice == 'm')
                        cin.ignore();
                    
                    if (temp == end)
                    {
                        cout << "Final Path: " << endl;
                        temp->print_pred(s);
                        cout << endl;
                        out = 1;
                        break;
                    }
                    
                    if (choice == 'm')
                    {
                        cout << "Current Optimal Path:" << endl;
                        temp->print_pred(s);
                    }
                    
                    queue.push_back(temp);
                    
                    counter++;
                    
                }
                
                // If you find a way out, break.
                if (out == 1)
                    break;
                
                // If no path is found, notify.
                if (queue.empty())
                {
                    cout << "No path found." << endl;
                    break;
                }
                
                temp = queue.front();
                
                // Stacks for algorithm
                if (temp->get_visited() == false)
                {
                    start = queue.front();
                    queue.erase(queue.begin());
                }
                else
                {
                    queue.erase(queue.begin());
                    start = queue.front();
                }
            }

    return true;
};

    // Straight line search
    bool straightLine(string start_city, string end_city, char choice)
    {
        cout << endl << "Heuristic: Straight Line distance:" << endl;
        cout << "Starting city: " << start_city << endl;
        cout << "Target city: " << end_city << endl;
        
        // Declare variables
        
        node* start;
        node* finish;
        node* current;
        vector<string> exception;
        double distance = 0;
        double x,y;
        int i = 0;
        string q;
        
        // Find cities
        while (graph[i].get_name() != start_city)
            i++;
        
        start = &graph[i];
        
        i=0;
        
        while (graph[i].get_name() != end_city)
            i++;
        
        finish = &graph[i];
        
        // Calculate heuristics and traverse.
        double *shortDis = new double[i];
        
        x = abs((finish->x - start->x));
        y = abs((finish->y - start->y));
        
        distance = sqrt(pow(x, 2) + pow(y,2));
        
        current = start;
        current->visited = true;
        
        vector<node *> path;
        vector<double> disTotal;
        
        double disTotalTemp = 0;
        
        disTotal.push_back(0);
        path.push_back(current);
        int index = 0;
        
        while (distance != 0){
            int i = 0;
            while (current->connections[i] != NULL)
                i++;
            for (int j=0; j < i; j++)
            {
                x = abs(finish->x - current->connections[j]->x);
                y = abs(finish->y - current->connections[j]->y);
                shortDis[j] = sqrt(pow(x, 2) + pow(y,2));
            }
            
            double smallest = MAX;
            
            for (int k = 0; k < i; k++)
            {
                if ((smallest > shortDis[k]) && (current->connections[k]->visited == false))
                {
                    smallest = shortDis[k];
                    index = k;
                }
            }
            
            x = abs((current->x - current->connections[index]->x));
            y = abs((current->y - current->connections[index]->y));
            
            disTotalTemp += sqrt(pow(x,2) + pow(y,2));
            disTotal.push_back(disTotalTemp);
            
            current = current->connections[index];
            current->visited = true;
            
            x = abs((finish->x - current->x));
            y = abs((finish->y - current->y));
            
            distance = sqrt(pow(x,2) + pow(y,2));
            path.push_back(current);
        }
        if (choice == 'm')
            cin.ignore();
        
        // Print paths.
        cout << endl;
        for (int i = 0; i < path.size(); i++)
        {
            if (choice == 'm')
            {
                
                if ((i+1) != path.size())
                    cout << "Current Optimal Path:" << endl;
                else
                {
                    cout << "Final Path: " << endl;
                }
            
                for (int k = 0; k <= i; k++)
                {
                    cout << path[k]->get_name();
                
                    if (k != i)
                    {
                        cout << "->";
                    }
                }
                cout << endl << "Distance Traveled: " << fixed << setprecision(2) << disTotal[i] << endl << endl;
                cin.ignore();
            }
            else
            {
                if ((i+1) == path.size())
                {
                    cout << "Final Path: " << endl;
                    for (int k = 0; k <= i; k++)
                    {
                        cout << path[k]->get_name();
                        
                        if (k != i)
                        {
                            cout << "->";
                        }
                    }
                    cout << endl << "Distance Traveled: " << fixed << setprecision(2) << disTotal[i] << endl << endl;

                }
            }
        }
        return true;
    }
};

#endif 
