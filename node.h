
#ifndef node_h
#define node_h
#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// Class for cities which acts as nodes.

class node {
    friend class map;
private:
    string name;
    int x;
    int y;
    double count;
    node* pred;
    node* temp;
    bool visited;
    array<node *,10> connections;
    vector<node *> stack;
    bool excluded;

public:
    // Constructor.
    node()
    {
        name = " ";
        x = 0;
        y = 0;
        count = 0.00;
        visited = false;
        pred = NULL;
        temp = NULL;
        excluded = false;
        connections[0] = NULL;
        connections[1] = NULL;
        connections[2] = NULL;
        connections[3] = NULL;
        connections[4] = NULL;
        connections[5] = NULL;
        connections[6] = NULL;
        connections[7] = NULL;
        connections[8] = NULL;
        connections[9] = NULL;
    }
    
    // Set predecessor
    void set_pred(node* pre)
    {
        pred = pre;
    }
    
    // Print predecessor
    void print_pred(string s)
    {
        stack.push_back(this);
        
        temp = pred;
        while (temp != NULL)
        {
            stack.push_back(temp);
            temp = temp->get_pred();
            count++;
        }
        
        if ((stack.back())->get_name() == s)
        {
            cout << ((stack.back())->get_name());
            stack.pop_back();
        }
        
        while (!(stack.empty()))
        {
            cout << " -> " << (stack.back())->get_name();
            stack.pop_back();
        }
        
        cout << endl << "Distance Traveled: " << fixed << setprecision(2) << count <<  endl;
    }
    
    // Get predecessor
    node* get_pred()
    {
        return pred;
    }
    
    // Check visited
    bool get_visited()
    {
        return visited;
    }
    
    // Check exclusion
    bool get_excluded()
    {
        return excluded;
    }
    
    // Set exclusion
    void set_excluded(bool ex)
    {
        excluded = ex;
    }
    
    // Set name
    void set_name(string x)
    {
        name = x;
    }
    
    int size()
    {
        return sizeof(connections)/sizeof(connections[0]);
    }
    
    // Get connection
    node* get_connection(int index)
    {
        return connections[index];
    }
    
    
    void set_x(int z)
    {
        x = z;
    }
    
    void set_y(int l)
    {
        y = l;
    }
    
    void set_visited(bool vis)
    {
        visited = vis;
    }
    
    void set_connections(int index, node* city) // careful with pointers
    {
        connections[index] = city;
    }
    
    // Print connection info
    void print_conn_info()
    {
        print_info();
        connections[0]->print_info();
        connections[1]->print_info();
    }
    
    // Get city name
    string get_name()
    {
        return name;
    }
    
    // Print city info
    void print_info()
    {
        cout << name << " " << x << " " << y << " " << endl;
    }
    

    
};

#endif
