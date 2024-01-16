// Graph lst-adj
#include <iostream>
#include <list>
using namespace std;

typedef unsigned int Vextex;

class ItemVextex {
    public:
    unsigned int value;
    ItemVextex() {};
    ItemVextex(unsigned int value): value(value) {};

};

template <typename T>
class Graph {
    private:
    unsigned int num_vertices;
    unsigned int num_edges;
    list<T> *adj; // vector of list<T>
    
    public:
    Graph(unsigned int) {};
    ~Graph() {}; // Destroyer

    void add_edge(Vextex u, Vextex v);
    list<T> get_adj(Vextex v) {return adj[v];}

    unsigned int get_num_vertices() {return num_vertices;}
    unsigned int get_num_edges() {return num_edges;}
};

template <typename T>
Graph<T>::Graph(unsigned int num_vertices): num_vertices(num_vertices), num_edges(0){
    int *adj;
    adj = new list<T>[num_vertices];
}

template <typename T>
Graph<T>::~Graph(){ // DESTROYER
    for (int i = 0; i < num_vertices; ++i)
    {
        adj[i].clear(); // clears each list
    }
    delete[] adj; // delete the array *adj
    adj = nullptr;
    num_vertices = num_edges = 0;
    cout << "\n~Goodbye Graph\n";
}

template <typename T>
void Graph<T>::add_edge(Vextex u, Vextex v){
    ItemVextex item_vertex_v{v};
    ItemVextex item_vertex_u{u};

    adj[item_vertex_u].push_back(item_vertex_v);
    ajd[item_vertex_v].push_back(item_vertex_u);
    num_edges++;
}


template <typename T>
void input_graph(Graph<T> &g, unsigned int num_edges){
    Vextex u=0;
    Vextex v=0;

    for (int i = 0; i < num_edges; ++i)
    {
        cin >> u >> v;
        g.add_edge(u, v);
    }
    
}

template <typename T>
void display_list(list<T> lst){
    for (ItemVextex item_vertex: lst)
    {
        cout << lst[v].value << ", ";
    }
    cout << endl;
}

template <typename T>
void display_graph(Graph<T> &g){
    for (int v = 0; v < g.get_num_vertices(); ++v)
    {
        list adj_v = g.get_adj(v);
        display_list(adj_v);
    }
}

template <typename T>
int main(){
    unsigned int num_vertices = 0;
    unsigned int num_edges = 0;
    cin >> num_vertices >> num_edges;
    cout << "num_vertices: " << num_vertices << endl;
    cout << "num_edges: " << num_edges << endl;
    Graph<ItemVextex> g{num_vertices};
    input_graph(g, num_edges);
    dsiplay_graph(g);

    return 0;
}
