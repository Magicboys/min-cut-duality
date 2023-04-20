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
int FindMaxFlow();
void PrintGraph();

//Instantiate Graph
list<Node*> graph;

int main()
{
    cout << "Creating graph and transforming it into a max flow graph!" << endl;
    //First we will establish a graph with weighted edges
    AddNode("A");
    AddNode("B");
    AddNode("C");
    AddNode("D");
    AddEdge("A", "B", 6);
    AddEdge("A", "D", 1);
    AddEdge("C", "B", 1);
    AddEdge("C", "D", 6);

    //Lets now transform the graph into a max flow graph
    AddNode("Source");
    AddNode("Sink");
    AddEdge("C", "Sink", 5);
    AddEdge("D", "Sink", 5);
    AddEdge("Source", "A", 20);
    AddEdge("Source", "B", 20);

    //PrintGraph();

    int max_flow = FindMaxFlow();


    return 0;
}

int FindMaxFlow() {
    cout << "Finding the max flow!" << endl;

    list<string> current_path = list<string>();

    //Path finding logic
    Node* current_node = nullptr;

    //Find the source node in memory
    for (auto i = graph.begin(); i != graph.end(); i++) {
        Node* local = *i;
        if (local->name == "Source") {
            current_node = local;
            current_path.push_back("Source");
            break;
        }
    }
    
    while (current_node->name != "Sink") {
        //Find what edges the current node is connected to
        list<Edge*> savedEdges = list<Edge*>();
        for (auto i = graph.begin(); i != graph.end(); i++) {
            Node* local = *i;

            //Find what edges are connected to the current node
            list<Edge*> localEdges = local->edges;
            for (auto j = localEdges.begin(); j != localEdges.end(); j++) {
                Edge* edge = *j;
                if (edge->beginning_node == current_node->name) {
                    savedEdges.push_back(edge);
                }
            }
        }

        //Choose the path with the highest edge capacity
        Edge* max_capacity_edge = nullptr;
        for (auto i = savedEdges.begin(); i != savedEdges.end(); i++) {
            Edge* edge = *i;

            //TODO: LATER ADD A CHECK TO MAKE SURE THAT THE LOCAL EDGE HASN'T BEEN SELECTED YET BEFORE PROCESSING THE IF STATEMENT BELOW

            if (max_capacity_edge == nullptr) {
                max_capacity_edge = edge;
            }
            else {
                if (max_capacity_edge->weight < edge->weight) {
                    max_capacity_edge = edge;
                }
            }
        }

        //IF NULL THEN NO MORE PATHS FROM THIS NODE AND WE RESTART

        cout << "MAX CAPACITY EDGES DEBUG" << endl;
        cout << "       { (" << max_capacity_edge->beginning_node << "," << max_capacity_edge->ending_node << ") with a weight of " << max_capacity_edge->weight << "}" << endl;

        //Set current node equal to the next path
        for (auto i = graph.begin(); i != graph.end(); i++) {
            Node* local = *i;

            if (local->name == max_capacity_edge->ending_node) {
                current_node = local;
                break;
            }
        }

        //Add the next node as part of the current path
        current_path.push_back(current_node->name);
    }
    current_path.push_back("Sink");

    cout << "PATH DEBUG" << endl;
    /*
    for (auto i = current_path.begin(); i != current_path.end(); i++) {
        string local = *i;
        cout << local << " ";
    }*/
    
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


