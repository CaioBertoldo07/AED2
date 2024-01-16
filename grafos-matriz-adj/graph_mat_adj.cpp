#include <iostream>
#include <cstdlib> // atoi
#include <vector>
#include <list>

using namespace std;
typedef unsigned int Vertex;
typedef unsigned int Weight;

class Edge{
    public:
        Weight weight;
        Edge(Weight _weight): weight(_weight) {}
};

class Graph {
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        Edge **adj;

    public:
        Graph(unsigned int);
        void add_edge(Vertex, Vertex);
        list<Edge> get_adj(Vertex);
        Weight get_weight_edge(Vertex, Vertex);
        ~Graph();
        
};

Graph::Graph(unsigned int _num_vertices): num_vertices(_num_vertices), num_edges(0){
    unsigned int LINES  = num_vertices;
    unsigned int COLUMNS = num_vertices;
    adj = new Edge*[LINES];
    for (int i = 0; i < LINES; ++i){
        adj[i] = new Edge[COLUMNS] {0};  
    }
}

Graph::~Graph(){
    const unsigned int LINES = num_vertices;
    for(int i = 0; i < LINES; ++i){
        delete[] adj[i];
    }
    delete[] adj;
    cout << "~Bye bye graph!";
}

void Graph::add_edge(Vertex u, Vertex v){
    Edge edge{1};
    adj[u][v] = edge;
    adj[u][v] = edge;
    num_edges++;
}

list<Edge> Graph::get_adj(Vertex u){
    list<Edge> values;
    for(int v = 0; v < num_vertices; ++v){
        if(adj[u][v].weight != 0){
            values.push_back(v);
        }
    }
    return values;
}

Weight Graph::get_weight_edge(Vertex u, Vertex v){
    return adj[u][v].weight;
}


int main(int argc, char const *argv[]){
    // Inserindo valores
    vector<int> values;
    int value = 0;
    for (int i = 1; i < argc; ++i){
        value = atoi(argv[i]);
        values.push_back(value);
    }

//    0 1  2 3 4 5 6 7 8 9 ...
//v : 9 12 0 1 0 2 0 3 1 4 2 4 3 4 4 5 4 5 4 7 5 8 6 8 7 8
//         u v
    unsigned int num_vertices = values[0];
    unsigned int num_edges = values[1];
    // Graph<Edge> g{num_vertices};
    for (int i = 0; i < num_edges * 2; i += 2)
    {
        Vertex u = values[i];
        Vertex v = values[i + 1];
        cout << u << ", " << v << endl;
        // g.add_edge(u, v);
        cout << values[i] << ", ";
    }
    //display_graph(g);
    cout << endl;

    return 0;
}
