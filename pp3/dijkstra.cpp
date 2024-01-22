#include <iostream>
#include <list>
#include <vector>
#include <limits>

using namespace std;

float inf = numeric_limits<float>::infinity();

typedef unsigned int Vertex;
typedef float Weight;

class VertexWeightPair {
    public:
        Vertex vertex;
        Weight weight;
        VertexWeightPair(Vertex vertex, Weight weight): vertex(vertex), weight(weight) {}
};

class WeightedDigraphAL {
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        list<VertexWeightPair> *adj;
    public:
        WeightedDigraphAL(unsigned int);
        ~WeightedDigraphAL();
        void add_edge(Vertex, Vertex, Weight);
        unsigned int get_num_vertices() {return num_vertices;}
        unsigned int get_num_edges() {return num_edges;}
        list<VertexWeightPair> get_adj(Vertex v) {return adj[v];}
};

WeightedDigraphAL::WeightedDigraphAL(unsigned int num_vertices){
    adj = new list<VertexWeightPair>[num_vertices];
}

WeightedDigraphAL::~WeightedDigraphAL(){
    for(unsigned int i = 0; i < num_vertices; ++i){
        adj[i].clear();
    }
    delete[] adj;
    num_vertices = num_edges = 0;
   // cout << "\nBye Bye Graph\n";
}

void WeightedDigraphAL::add_edge(Vertex u, Vertex v, Weight w){
    VertexWeightPair itemV{v, w};
    adj[u].push_back(itemV);
    num_edges++;
}

