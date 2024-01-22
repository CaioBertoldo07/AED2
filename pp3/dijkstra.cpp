#include <iostream>
#include <list>
#include <vector>
#include <limits>

#define null -1
#define max 100

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
        void Dijkstra(int);
       // void relax(vector<float>);
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
   // cout << "\nBye Bye Graph\n";
}

void WeightedDigraphAL::add_edge(Vertex u, Vertex v, Weight w){
    VertexWeightPair itemV{v, w};
    adj[u].push_back(itemV);
    num_edges++;
}


// Classe para o heap mínimo
template<typename T>
class MinHeap{
    private:
        T* heap_array;
        int capacity;
        int heap_size;
    public:
        MinHeap(int);
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
MinHeap<T>::MinHeap(int capacity){
    this->capacity = capacity;
    this->heap_array = new T[capacity];
    this->heap_size = 0;
}

template<typename T>
void MinHeap<T>::MinHeapfy(int i){
    int l = left(i);
    int r = right(i);

    int smallest = 0;
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
    for(int i = heap_size / 2; i--;){
        MinHeapfy(i);
    }
}

template<typename T>
T MinHeap<T>::extractMin(){
    T x = heap_array[0];
    heap_array[0] = heap_array[heap_size - 1];
    heap_size--;
    MinHeapfy(0);
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

void WeightedDigraphAL::Dijkstra(int s){
    MinHeap<Vertex> queue{max};
    vector<float> distance(num_vertices);
    vector<Vertex> predecessor(num_vertices);
    for(unsigned int i = 0; i < num_vertices; i++){
        distance[i] = inf;
        predecessor[i] = null;
    }
    distance[s] = 0;
    queue.insert(s);
    while(!queue.isEmpty()){
        Vertex u = queue.extractMin();
        
        for(auto v: adj[u]){
            if(distance[v.vertex] > distance[u] + v.weight){
                distance[v.vertex] = distance[u] + v.weight;
                predecessor[v.vertex] = u;
                queue.insert(v.vertex);
            }
        }
    }
    cout << num_vertices;
    for(unsigned int i = 0; i < num_vertices; i++){
        cout << distance[i] << " ";
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
    unsigned int num_edges = 0, num_vertices = 0;
    unsigned int entrance = 0, exit = 0;
    cin >> num_vertices >> num_edges;
    WeightedDigraphAL g{num_vertices};
    input_graph(g, num_edges);
    cin >> entrance >> exit;
    g.Dijkstra(0);
    return 0;
}