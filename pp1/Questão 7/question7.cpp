#include <iostream>
#include <list>
using namespace std;
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
        void remove_edge(Vertex, Vertex);
        unsigned int get_num_vertices() {return num_vertices;}
        unsigned int get_num_edges() {return num_edges;}
        list<VertexWeightPair> get_adj(Vertex v) {return adj[v];}
};

WeightedDigraphAL::WeightedDigraphAL(unsigned int num_vertices): num_vertices(num_vertices){
    adj = new list<VertexWeightPair>[num_vertices];
}

WeightedDigraphAL::~WeightedDigraphAL(){
    for(unsigned int i = 0; i < num_vertices; ++i){
        adj[i].clear();
    }
    delete[] adj;
    num_vertices = num_edges = 0;
    cout << "\nBye Bye Graph\n";
}

void WeightedDigraphAL::add_edge(Vertex u, Vertex v, Weight w){
    VertexWeightPair itemV{v, w};
    adj[u].push_back(itemV);
    num_edges++;
}

void WeightedDigraphAL::remove_edge(Vertex u, Vertex v){
    list<VertexWeightPair>::iterator iter;
    for(iter = adj[u].begin(); iter != adj[u].end(); iter++){
        if(iter->vertex == v){
            adj[u].erase(iter);
            break;
        }
    }
    num_edges--;
}

void display_list(list<VertexWeightPair> lst){
    for(VertexWeightPair itemVertex: lst){
        cout << "(" << itemVertex.vertex << ", " << itemVertex.weight << ")";
    }
    cout << endl;
}

void display_graph(WeightedDigraphAL &g){
    for(unsigned int v = 0; v < g.get_num_vertices(); v++){
        cout << "v[" << v << "]: ";
        list<VertexWeightPair> lst = g.get_adj(v);
        display_list(lst);
    }
}

void input_graph(WeightedDigraphAL &g, unsigned int num_edges){
    Vertex u = 0, v = 0;
    Weight w = 0;
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
    WeightedDigraphAL g{num_vertices};
    input_graph(g, num_edges);
    display_graph(g);

    cout << "\nRemove edge" << endl;
    g.remove_edge(1, 2);
    display_graph(g);
}

// 4 7 0 1 -1.0 1 0 3.1 1 2 1.2 0 2 -1.0 0 3 0.0 3 0 1.4 3 2 6.4

