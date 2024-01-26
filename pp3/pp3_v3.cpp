#include <iostream>
#include <list>
#include <vector>
#include <limits>
using namespace std;
#define max 100
float inf = numeric_limits<float>::infinity();


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
        bool sick;
        
        list<VertexWeightPair> *adj;
        vector<Vertex> min_path;
    
    public:
        
        WeightGraphAL* sub_graphs;
        WeightGraphAL();
        WeightGraphAL(unsigned int);
        ~WeightGraphAL();
        void add_edge(Vertex, Vertex, Weight);
        void remove_edge(Vertex, Vertex);
        void build_subgraph(unsigned int);
        void turnsick(){sick = true;}
        unsigned int get_num_vertices() {return num_vertices;}
        unsigned int get_num_edges() {return num_edges;}
        unsigned int getSick(){return sick;}
        list<VertexWeightPair> get_adj(Vertex v) {return adj[v];} 
        void Dijkstra(unsigned int, unsigned int);
        vector<Vertex> get_min_path() {return min_path;}
};

WeightGraphAL::WeightGraphAL(){
    num_edges = num_vertices = 0;
    sick = false;
}

WeightGraphAL::WeightGraphAL(unsigned int num_vertices): num_vertices(num_vertices){
    adj = new list<VertexWeightPair>[num_vertices];
    num_edges = 0;
    sub_graphs = new WeightGraphAL[num_vertices];
    sick = false;
}

WeightGraphAL::~WeightGraphAL(){
    for(unsigned int i = 0; i < num_vertices; ++i){
        adj[i].clear();
    }
    delete[] adj;
    num_vertices = num_edges = 0;
}

void WeightGraphAL::build_subgraph(unsigned int num){
    num_vertices = num;
    adj = new list<VertexWeightPair>[num];
}

void WeightGraphAL::add_edge(Vertex u, Vertex v, Weight w){
    if (u == v)
        return;
    list<VertexWeightPair>:: iterator it;
    for(it = adj[u].begin(); it != adj[u].end(); it++){
        if(it->vertex == v){
            return;
        }
    }
    for(it = adj[v].begin(); it != adj[v].end(); it++){
        if(it->vertex == u){
            return;
        }
    }
    VertexWeightPair itemV{v, w};
    adj[u].push_back(itemV);
    VertexWeightPair itemU(u, w);
    adj[v].push_back(itemU);
    num_edges++;
}

void WeightGraphAL::remove_edge(Vertex u, Vertex v){
    bool exist = false;
    list<VertexWeightPair>::iterator iter;
    for(iter = adj[u].begin(); iter != adj[u].end(); iter++){
        if(iter->vertex == v){
            adj[u].erase(iter);
            exist = true;
            break;
        }
    }

    for(iter = adj[v].begin(); iter != adj[v].end(); iter++){
        if(iter->vertex == u){
            adj[v].erase(iter);
            exist = true;
            break;
        }
    }
    if(exist == true)
        num_edges--;
}

// Classe para o heap mínimo
template<typename T>
class MinHeap{
    private:
        T heap_array[max];
        int capacity;
        int heap_size = 0;
    public:
       // MinHeap(int);
        void MinHeapfy(int);
        int parent(int i) {return i/2;}
        int left(int i) {return 2*i;}
        int right(int i) {return 2*i + 1;}
        T extractMin();
        void insert(T);
        bool isEmpty();
        void Build_heapfy();
        int get_heap_size() {return heap_size;}
        void print_heap();
};

template<typename T>
void MinHeap<T>::MinHeapfy(int i){
    int l = left(i);
    int r = right(i);

    int smallest;
    if(l <= heap_size && heap_array[l] < heap_array[i]){
        smallest = l;
    }else {
        smallest = i;
    }
    if(r <= heap_size && heap_array[r] < heap_array[smallest]){
        smallest = r;
    }
    if(smallest != i){
        swap(heap_array[i], heap_array[smallest]);
        MinHeapfy(smallest);
    }
}

template<typename T>
void MinHeap<T>::Build_heapfy(){
    for(int i = heap_size / 2; i > 0; i--){
        MinHeapfy(i);
    }
}

template<typename T>
T MinHeap<T>::extractMin(){
    T x = heap_array[0];
    heap_array[0] = heap_array[heap_size - 1];
    heap_size--;
    MinHeapfy(0);
    //cout << "Extraiu";
    return x; 
}

template<typename T>
bool MinHeap<T>::isEmpty(){
    if(heap_size == 0){
        return true;
    } else{
        return false;
    }
}

template<typename T>
void MinHeap<T>::insert(T i){
    heap_array[heap_size++] = i;
    Build_heapfy();
}

template<typename T>
void MinHeap<T>::print_heap(){
    for(int i = 0; i < heap_size + 1; i++){
        cout << heap_array[i] << " ";
    }
}

void WeightGraphAL::Dijkstra(unsigned int origin, unsigned int destiny){
    MinHeap<Vertex> queue;
    vector<Weight> distance(num_vertices);
    vector<Vertex> predecessor(num_vertices);
  //  cout << "Beleza" << endl;
    for(unsigned int i = 0; i < num_vertices; i++){
        distance[i] = inf;
        predecessor[i] = -1;
    }
   // cout << "Beleza 2" << endl;
    distance[origin] = 0;
    queue.insert(origin);
  //cout <<"Distancia 0: " << distance[0];
    //cout << "Beleza 3" << endl;
    while(!queue.isEmpty()){
        Vertex u = queue.extractMin();
        //cout << "Beleza 4" << endl;
        for(VertexWeightPair v: adj[u]){
            if(distance[v.vertex] > distance[u] + v.weight){
                distance[v.vertex] = distance[u] +  v.weight;
                predecessor[v.vertex] = u;
                queue.insert(v.vertex);
            }
        }
    }

    // for(unsigned int i = 0; i < num_vertices; i++){
    //     cout << "Predecessor de " << i + 1 << ": " << predecessor[i] << endl;
    // }
    
    
    min_path.push_back(destiny);
    // cout << "Beleza 5" << endl;
    Vertex v = destiny;
    while(v != origin){
        // cout << "V antes: " << v << endl;
        v = predecessor[v];
        // cout << "V depois: " << v << endl;
        min_path.push_back(v);
        // cout << "Beleza 6" << endl;
        // cout << path[v] << endl;
    }
    //cout << "Beleza 7" << endl;
    // cout << "Caminho: ";
    // for(auto i: min_path){
    //     cout << i << " ";
    // }
    // cout << endl;
    // cout << num_vertices << endl;
    // for(unsigned int i = 0; i < num_vertices; i++){
    //     cout << "Distancia de " << i << ": " << distance[i] << endl;
    // }
    
}

void display_list(list<VertexWeightPair> lst){
    for(VertexWeightPair itemVertex: lst){
        cout << "(" << itemVertex.vertex << ", " << itemVertex.weight << "), ";
    }
    cout << endl;
}

void display_graph(WeightGraphAL &g){
    cout << "num_vertices: " << g.get_num_vertices() - 1 <<  endl;
    cout << "num_edges: " << g.get_num_edges() << endl;
    for(unsigned int v = 0; v < g.get_num_vertices(); v++){
        cout << v + 1 << ": ";
        list<VertexWeightPair> lst = g.get_adj(v);
        display_list(lst);
    }
}

void display_subgraph(WeightGraphAL &g){
    cout << "num_vertices: " << g.get_num_vertices() - 1<<  endl;
    cout << "num_edges: " << g.get_num_edges() << endl;
    for(unsigned int v = 0; v < g.get_num_vertices(); v++){
        cout << v + 1 << ": ";
        list<VertexWeightPair> lst = g.get_adj(v);
        display_list(lst);
    }
    cout << "Doente?: " << g.getSick() << endl << endl;
}

void input_graph(WeightGraphAL &g, unsigned int num_edges){
    Vertex u = 0, v = 0;
    Weight w = 0;
    for(unsigned int i = 0; i < num_edges; i++){
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }
}

class UnionFind {
    private:
        unsigned int *parent;
        unsigned int num_vertices;
    public:
        UnionFind(unsigned int);
        int find_set(unsigned int);
        void make_set();
        void Union(int, int);
        
};

UnionFind::UnionFind(unsigned int num_vertices): num_vertices(num_vertices){
    parent = new unsigned int[num_vertices];
}

int UnionFind::find_set(unsigned int x){
    if(parent[x] == x){
        return x;
    } else{
        return find_set(parent[x]);
    }
}

void UnionFind::make_set(){
    for(unsigned int i = 0; i < num_vertices; i++){
        parent[i] = i;
    }
}

void UnionFind::Union(int x, int y){
    x = find_set(x);
    y = find_set(y);
    if(x != y){
        parent[y] = x;
    }
}


int main(){
    unsigned int num_vertices = 0;
    unsigned int num_edges = 0;
    cin >> num_vertices >> num_edges;
    WeightGraphAL brain{num_vertices + 1};
    input_graph(brain, num_edges);
    

    unsigned int entrance = 0;
    unsigned int exit = 0;

    cin >> entrance >> exit;
    //cout << "aaaaaaa" << endl;
    brain.Dijkstra(entrance, exit);
    // cout << "Caminho: "<< endl;
    // for(auto i: brain.get_min_path()){
    //     cout << i << " ";
    // }
    cout << endl;
    for (unsigned int i = 1; i <= num_vertices; i++){
        unsigned int num_vertices_sub = num_edges = 0;
        unsigned int num_sick = 0;
        unsigned int sick_vertices;
        cin >> num_vertices_sub >> num_edges;
        cin >> num_sick;

        brain.sub_graphs[i].build_subgraph(num_vertices_sub + 1);
        if(num_sick > 0){
            brain.sub_graphs[i].turnsick();
            for(unsigned int j = 0; j < num_sick; j++){
                cin >> sick_vertices;
            }
        }
        input_graph(brain.sub_graphs[i], num_edges);
    }


    // display_graph(brain);
    // for (unsigned int i = 1; i <= num_vertices; i++){
    //     display_subgraph(brain.sub_graphs[i]);
    // }
    
    return 0;
}