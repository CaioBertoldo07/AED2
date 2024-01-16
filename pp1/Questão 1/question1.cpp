#include <iostream>
#include <list>
using namespace std;
typedef unsigned int Vertex;

class ItemVertex{
    public:
        unsigned int value;
        ItemVertex() {}
        ItemVertex(unsigned int value): value(value) {}
};

class GraphAL{
    // Atributos
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        list<Vertex> *adj;

    public:
        GraphAL(unsigned int);
        ~GraphAL();

        void add_edge(Vertex, Vertex);
        void remove_edge(Vertex, Vertex);
        unsigned int get_num_vertices(){return num_vertices;}
        unsigned int get_num_edges(){return num_edges;}
        list<Vertex> get_adj(Vertex v) {return adj[v];}
};

GraphAL::GraphAL(unsigned int num_vertices): num_vertices(num_vertices){
    adj = new list<Vertex>[num_vertices];
}

void GraphAL::add_edge(Vertex u, Vertex v){
   adj[u].push_back(v);
   adj[v].push_back(u);
   num_edges++; 
}

void GraphAL::remove_edge(Vertex u, Vertex v) {
    adj[u].remove(v);
    adj[v].remove(u);
    num_edges--;
}

GraphAL::~GraphAL(){
    for(unsigned int i = 0; i < num_vertices; ++i){
        adj[i].clear();
    }
    num_edges = num_vertices = 0;
    cout << "\nBye bye graph" << "\n";
}

void display_list(list<Vertex> lst){
    for(ItemVertex item_vertex: lst){
        cout << item_vertex.value << ", ";
    }
    cout << endl;
}

void display_graph(GraphAL &g) {
	for (unsigned int v = 0; v < g.get_num_vertices(); v++) {
		cout << v << ": ";
		list<Vertex> lst = g.get_adj(v);
		display_list( lst );
	}
}

void input_graph(GraphAL &g, unsigned int num_edges) {
	Vertex u = 0, v = 0;
	for (unsigned int i = 0; i < num_edges; ++i) {
		cin >> u >> v;
		g.add_edge(u, v);
	}
}

int main()
{
    unsigned int num_vertices = 0;
	unsigned int num_edges = 0;
	cin >> num_vertices >> num_edges;
	cout << "num_vertices: " << num_vertices << endl;
	cout << "num_edges: " << num_edges << endl;
	GraphAL g{num_vertices};
	input_graph(g, num_edges);
	display_graph(g);

    cout << "\nRemove edge " << "\n";
    g.remove_edge(0, 1);
    display_graph(g);
	return 0;
}

// 9 12 0 1 0 2 0 3 1 4 2 4 3 4 4 5 4 6 4 7 5 8 6 8 7 8