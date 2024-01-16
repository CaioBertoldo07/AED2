#include <iostream>
#include <cstdlib> // atoi
#include <vector>
#include <list>
#include <iomanip> // setw
#include <limits>
using namespace  std;
typedef unsigned int Vertex;
typedef float Weight;

float inf = numeric_limits<float>::infinity();

class WeightedGraphAM {
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        Weight **adj;
    
    public:
        WeightedGraphAM(unsigned int);
        ~WeightedGraphAM();
        void add_edge(Vertex, Vertex, Weight);
        void remove_edge(Vertex, Vertex);
        unsigned int get_num_vertices() {return num_vertices;}
        unsigned int get_num_edges() {return num_edges;}
        list<Vertex> get_adj(Vertex);
        Weight get_weight_edge(Vertex u, Vertex v) {return adj[u][v];}
};

WeightedGraphAM::WeightedGraphAM(unsigned int _num_vertices): num_vertices(_num_vertices), num_edges(0){
    const unsigned int LINES = num_vertices;
    const unsigned int COLUMNS = num_vertices;
    adj = new Weight*[LINES];
    for(unsigned int i = 0; i < LINES; ++i){
        adj[i] = new Weight[COLUMNS];
    }

    for(unsigned int i = 0; i < LINES; i++){
        for(unsigned int j = 0; j < COLUMNS; j++){
            adj[i][j] = inf;
        }
    }
}

WeightedGraphAM::~WeightedGraphAM(){
    const unsigned int LINES = num_vertices;
    for(unsigned int i = 0; i < LINES; ++i){
        delete[] adj[i];
    }
    delete[] adj;
    cout << "\nBye Bye Graph\n";
}

void WeightedGraphAM::add_edge(Vertex u, Vertex v, Weight w){
    Weight edge{w};
    adj[u][v] = edge;
    adj[v][u] = edge;
    num_edges++;
}

void WeightedGraphAM::remove_edge(Vertex u, Vertex v){
    Weight edge{inf};
    adj[u][v] = edge;
    adj[v][u] = edge;
    num_edges--;
}

list<Vertex> WeightedGraphAM::get_adj(Vertex u){
    list<Vertex> values;
    for(unsigned int v = 0; v < num_vertices; ++v){
        if(adj[u][v] != 0){
            values.push_back(v);
        }
    }
    return values;
}

void display_matadj_graph(WeightedGraphAM &g){
    int k = 3;
    // build each line of the matrix
    for(unsigned int i = 0; i < g.get_num_vertices(); i++){
        
        // Line values
        for(unsigned int j = 0; j < g.get_num_vertices(); j++){
            cout << setw(k) << "   " << g.get_weight_edge(i, j);
        }
        cout << endl;
    }    
}


void input_graph(WeightedGraphAM &g, unsigned int num_edges){
    Vertex u = inf, v = 0;
    Weight w = inf;
    for(unsigned int i = 0; i < num_edges; i++){
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }
}

int main(){
    unsigned int num_vertices = 0;
    unsigned int num_edges = 0;
    cin >> num_vertices >> num_edges;
    cout << "num_vertices: " << num_vertices << endl;
    cout << "num_edges: " << num_edges << endl;
    WeightedGraphAM g{num_vertices};
    input_graph(g, num_edges);
    display_matadj_graph(g);

    cout << "\nRemove edge" << endl;
    g.remove_edge(0, 1);
    display_matadj_graph(g);
    
    return 0;
}
//7 12 0 1 1.5 0 2 0.4 0 3 1.3 1 2 -2.5 1 4 1.4 3 2 3.1 3 6 1.3 2 4 -1.9 2 5 0.6 2 6 10.0 4 5 1.7 6 5 -2.8