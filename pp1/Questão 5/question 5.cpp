#include <iostream>
#include <list>
#include <vector>

using namespace std;
typedef unsigned int Vertex;

class ItemVertex{
    public:
        unsigned int value;
        ItemVertex() {}
        ItemVertex(unsigned int value): value(value) {}
};

class DigraphAL {
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        list<Vertex> *adj;
    public:
        DigraphAL(unsigned int);
        ~DigraphAL();
        void add_edge(Vertex, Vertex);
        void remove_edge(Vertex, Vertex);
        unsigned int get_num_vertices() {return num_vertices;}
        unsigned int get_num_edges() {return num_edges;}
        list<Vertex> get_adj(Vertex v) {return adj[v];}
};

DigraphAL::DigraphAL(unsigned int num_vertices): num_vertices(num_vertices){
    adj = new list<Vertex>[num_vertices];
}

DigraphAL::~DigraphAL(){
    for(unsigned int i = 0; i < num_vertices; i++){
        adj[i].clear();
    }
    delete[] adj;
    num_edges = num_vertices = 0;
    cout << "\nBye Bye Graph" << endl;
}

void DigraphAL::add_edge(Vertex u, Vertex v){
    adj[u].push_back(v);
    num_edges++;
}

void DigraphAL::remove_edge(Vertex u, Vertex v){
    adj[u].remove(v);
    num_edges--;
}

void input_graph(DigraphAL &g, unsigned int num_edges){
    Vertex u = 0, v = 0;
    for(unsigned int i = 0; i < num_edges; i++){
        cin >> u >> v;
        g.add_edge(u, v);
    }
}

void display_list(list<Vertex> lst){
    for(ItemVertex item_vertex: lst){
        cout << item_vertex.value << " ,";
    }
    cout << endl;
}

void display_graph(DigraphAL &g) {
    for(unsigned int i = 0; i < g.get_num_vertices(); i++){
        cout << "v[" << i << "]: ";
		list<Vertex> lst = g.get_adj(i);
		display_list( lst );
    }
}

int main(){
    unsigned int num_vertices = 0;
    unsigned int num_edges = 0;
    cin >> num_vertices >> num_edges;
    cout << "num_vertices: " << endl;
    cout << "num_edges: " << endl;

    DigraphAL g{num_vertices};
    input_graph(g, num_edges);
    display_graph(g);
    

    cout << "\nRemove edge" << endl;
    g.remove_edge(0, 1);
    display_graph(g);
    return 0;
}
// 4 7 0 1 1 0 1 2 0 2 0 3 3 0 3 2