//Authored by: Tyler Watson
//Date: 4/20/2023

//Imports
#include <iostream>
#include <list>
using namespace std;

//Graph structs
struct Edge {
    string beginning_node;
    string ending_node;
    int weight;
};

struct Node {
    string name;
    list<Edge*> edges;
};


//Method Declarations
void AddNode(string name);
void AddEdge(string node, string ending_node, int weight);
void PrintGraph();

//Instantiate Graph
list<Node*> graph;

int main()
{
    std::cout << "Hello World!\n";

    //Establish graph nodes
    AddNode("Source");
    AddNode("A");
    AddNode("B");
    AddNode("C");
    AddNode("D");
    AddNode("Sink");

    //Establish graph edges
    AddEdge("Source", "A", 8);
    AddEdge("Source", "B", 8);
    AddEdge("A", "C", 3);
    AddEdge("B", "D", 5);
    AddEdge("C", "Sink", 5);
    AddEdge("D", "Sink", 4);
    
    PrintGraph();
    return 0;
}

void AddEdge(string node, string ending_node, int weight) {
    Edge* edge = new Edge();
    edge->beginning_node = node;
    edge->ending_node = ending_node;
    edge->weight = weight;

    for (auto i = graph.begin(); i != graph.end(); i++) {
        Node* value = *i;

        if (value->name == node) {
            list<Edge*> temp = value->edges;
            temp.push_back(edge);
            value->edges = temp;
        }
        if (value->name == ending_node) {
            list<Edge*> temp = value->edges;
            temp.push_back(edge);
            value->edges = temp;
        }
    }
}

void AddNode(string name) {
    Node* temp = new Node();
    temp->name = name;
    temp->edges = list<Edge*>();
    graph.push_back(temp);
}

void PrintGraph() {
    for (auto i = graph.begin(); i != graph.end(); i++) {
        Node* value = *i;
        cout << "{" << endl;
        cout << "   Node: " << value->name << endl;
        cout << "   Edges: " << endl;
        for (auto j = value->edges.begin(); j != value->edges.end(); j++) {
            Edge* edge_info = *j;
            cout << "       { (" << edge_info->beginning_node << "," << edge_info->ending_node << ") with a weight of " << edge_info->weight << "}" << endl;
        }
        cout << "}" << endl;
    }
}


