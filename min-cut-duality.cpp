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
list<list<Edge*>> choosen_paths;

int main()
{
    std::cout << "Creating graph and transforming it into a max flow graph!" << endl;
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
    AddEdge("B", "Sink", 5);
    AddEdge("D", "Sink", 5);
    AddEdge("Source", "A", 20);
    AddEdge("Source", "C", 20);

    //PrintGraph();

    //Run max flow algorithm
    int max_flow = FindMaxFlow();
    cout << "MAX FLOW: " << max_flow << endl;


    //Calculate the min-cut based on minimum edge sum
    list<Edge*> limiting_edge = list<Edge*>();
    for (auto k = choosen_paths.begin(); k != choosen_paths.end(); k++) {
        list<Edge*> localList = *k;

        //Find the smallest capacity edge in the path
        Edge* local_limiting_edge = nullptr;
        for (auto i = localList.begin(); i != localList.end(); i++) {
            cout << "DAIBNFS" << endl;
            Edge* local = *i;
            cout << local->weight << endl;

            if (local_limiting_edge == nullptr) {
                cout << "HI" << endl;
                local_limiting_edge = local;
            }
            else {
                cout << "OK" << endl;
                if (local->weight < local_limiting_edge->weight) {
                    cout << "eyes" << endl;
                    local_limiting_edge = local;
                }
            }
        }
        cout << "(" << local_limiting_edge->weight << "," << local_limiting_edge->weight << ")" << endl;
        limiting_edge.push_back(local_limiting_edge);
    }

    cout << "The min-cut solution consists of performing a cut on the following edges:" << endl;
    for (auto k = limiting_edge.begin(); k != limiting_edge.end(); k++) {
        Edge* local = *k;
        cout << "(" << local->beginning_node << "," << local->ending_node << ")" << endl;
    }

    return 0;
}

int FindMaxFlow() {
    std::cout << "Finding the max flow!" << endl;

    Node* source = nullptr;
    //Find the source node in memory
    for (auto i = graph.begin(); i != graph.end(); i++) {
        Node* local = *i;
        if (local->name == "Source") {
            source = local;
            break;
        }
    }

    list<list<Edge*>> temp(source->edges.size(), list<Edge*>());
    choosen_paths = temp;

    list<Edge*> takenEdges = list<Edge*>();
    Edge* max_capacity_edge = nullptr;

    for (int iteration = 0; iteration < source->edges.size(); iteration++) {
        list<Edge*> current_path = list<Edge*>();

        //Path finding logic
        Node* current_node = nullptr;

        //Find the source node in memory
        current_node = source;
    
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
            max_capacity_edge = nullptr;
            for (auto i = savedEdges.begin(); i != savedEdges.end(); i++) {
                Edge* edge = *i;

                bool alreadyChosen = false;
                for (auto j = takenEdges.begin(); j != takenEdges.end(); j++) {
                    Edge* edgeInQuestion = *j;
                    if ((edgeInQuestion->beginning_node == edge->beginning_node) && (edgeInQuestion->ending_node == edge->ending_node)) {
                        alreadyChosen = true;
                    }
                }

                if (!alreadyChosen) {
                    if (max_capacity_edge == nullptr) {
                        max_capacity_edge = edge;
                        takenEdges.push_back(edge);
                    }
                    else {
                        if (max_capacity_edge->weight < edge->weight) {
                            max_capacity_edge = edge;
                            takenEdges.push_back(edge);
                        }
                    }
                }
                
            }

            if (max_capacity_edge != nullptr) {
                //Set current node equal to the next path
                for (auto i = graph.begin(); i != graph.end(); i++) {
                    Node* local = *i;

                    if (local->name == max_capacity_edge->ending_node) {
                        current_node = local;
                        break;
                    }
                }

                //Add the next node as part of the current path
                current_path.push_back(max_capacity_edge);
            } else {
                //If the source node has all taken paths then we have found our best maximal flow solution
                if (current_node->name == "Source") {
                    break;
                }
            }
            
        }

        //Verify that we only save valid paths
        if (current_path.size() != 1) {
            choosen_paths.push_back(current_path);
        }
        
        
    }
    
    //Calculate max flow from all paths
    std::cout << "Maximal Path(s):" << endl;
    int max_flow = 0;
    for (auto k = choosen_paths.begin(); k != choosen_paths.end(); k++) {
        list<Edge*> localList = *k;
        int path_limiting_flow = 200000000;
        for (auto i = localList.begin(); i != localList.end(); i++) {
            Edge* local = *i;
            cout << local->beginning_node << " ";
            if (local->ending_node == "Sink") {
                cout << "Sink" << endl;
            }

            if (local->weight < path_limiting_flow) {
                path_limiting_flow = local->weight;
            }
        }

        if (path_limiting_flow != 200000000) {
            max_flow += path_limiting_flow;
        }
        
    }
    
    return max_flow;
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
        std::cout << "{" << endl;
        std::cout << "   Node: " << value->name << endl;
        std::cout << "   Edges: " << endl;
        for (auto j = value->edges.begin(); j != value->edges.end(); j++) {
            Edge* edge_info = *j;
            std::cout << "       { (" << edge_info->beginning_node << "," << edge_info->ending_node << ") with a weight of " << edge_info->weight << "}" << endl;
        }
        std::cout << "}" << endl;
    }
}


