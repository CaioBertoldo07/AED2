#include <iostream>
#include <list>
#include <vector>

using namespace std;
typedef unsigned int Vertex;
typedef float Weight;

class VertexWeightPair {
    public:
        Vertex vertex;
        Weight weight;
        VertexWeightPair(Vertex vertex, Weight weight): vertex(vertex), weight(weight) {}
};

class WeightGraphAL {
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        list<VertexWeightPair> *adj;
    
    public:
        WeightGraphAL(unsigned int);
        ~WeightGraphAL();
        void add_edge(Vertex, Vertex, Weight);
        void remove_edge(Vertex, Vertex);
        unsigned int get_num_vertices() {return num_vertices;}
        unsigned int get_num_edges() {return num_edges;}
        list<VertexWeightPair> get_adj(Vertex v) {return adj[v];} 
};

WeightGraphAL::WeightGraphAL(unsigned int num_vertices): num_vertices(num_vertices){
    adj = new list<VertexWeightPair>[num_vertices];
}

WeightGraphAL::~WeightGraphAL(){
    for(unsigned int i = 0; i < num_vertices; ++i){
        adj[i].clear();
    }
    delete[] adj;
    num_vertices = num_edges = 0;
    cout << "\nBye Bye Graph\n";
}

void WeightGraphAL::add_edge(Vertex u, Vertex v, Weight w){
    VertexWeightPair itemV{v, w};
    adj[u].push_back(itemV);
    VertexWeightPair itemU(u, w);
    adj[v].push_back(itemU);
    num_edges++;
}

void WeightGraphAL::remove_edge(Vertex u, Vertex v){
    list<VertexWeightPair>::iterator iter;
    for(iter = adj[u].begin(); iter != adj[u].end(); iter++){
        if(iter->vertex == v){
            adj[u].erase(iter);
            break;
        }
    }

    for(iter = adj[v].begin(); iter != adj[v].end(); iter++){
        if(iter->vertex == u){
            adj[v].erase(iter);
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

void display_graph(WeightGraphAL &g){
    for(unsigned int v = 0; v < g.get_num_vertices(); v++){
        cout << v << ": ";
        list<VertexWeightPair> lst = g.get_adj(v);
        display_list(lst);
    }
}

void input_graph(WeightGraphAL &g, unsigned int num_edges){
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
    cout << "num_vertices: " << num_vertices <<  endl;
    cout << "num_edges: " << num_edges << endl;
    WeightGraphAL g{num_vertices};
    input_graph(g, num_edges);
    display_graph(g);

    cout << "\nRemove edge: \n";
    g.remove_edge(2, 3);
    display_graph(g);
}

// 7 12 0 1 1.5 0 2 0.4 0 3 1.3 1 2 -2.5 1 4 1.4 3 2 3.1 3 6 1.3 2 4 -1.9 2 5 0.6 2 6 10.0 4 5 1.7 6 5 -2.8
