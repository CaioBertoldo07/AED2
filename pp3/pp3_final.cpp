#include <iostream>
#include <list>
#include <vector>
#include <limits>
using namespace std;
#define max 100
float inf = numeric_limits<float>::infinity();


typedef unsigned int Vertex;
typedef float Weight;
typedef pair<pair<unsigned int,unsigned int>,float> vertexPair;

class VertexWeightPair {
    public:
        Vertex vertex;
        Weight weight;
        VertexWeightPair(Vertex vertex, Weight weight): vertex(vertex), weight(weight) {}
};

//Minimum Spanning Tree
class Mst{
    public:
        vector<vertexPair> pairs;
        float sum;
        Mst(){sum = 0;}
        ~Mst();
};

Mst::~Mst(){
    sum = 0;
    pairs.clear();
}

//TDA Union Find
class UnionFind{
    private:
        unsigned int *parent;
        unsigned int numElements;
    public:
        UnionFind(unsigned int);
        ~UnionFind();
        unsigned int FindSet(unsigned int);
        void MakeSet();
        void Union(unsigned int, unsigned int);
};


UnionFind::UnionFind(unsigned int numElements): numElements(numElements){
    parent = new unsigned int[numElements];
};

UnionFind::~UnionFind(){
    delete[] parent;
}

void UnionFind::MakeSet(){
    for(unsigned int i = 0; i < numElements; i++){
        parent[i] = i;
    }
};

unsigned int UnionFind::FindSet(unsigned int x){
    if(parent[x] == x){
        return x;
    } else{
        return FindSet(parent[x]);
    }
}

void UnionFind::Union(unsigned int x, unsigned int y){
    x = FindSet(x);
    y = FindSet(y);
    if(x != y){
        parent[y] = x;
    }
}

// TDA Grafo Ponderado
class WeightGraphAL {
    private:
        unsigned int numVertices;
        unsigned int numEdges;
        bool sick;          
        
        list<VertexWeightPair> *adj;
        vector<Vertex> minPath; 

        Mst mst;                 
        vector<vertexPair> graph;


        WeightGraphAL** subGraphs;

    public:
        WeightGraphAL();
        WeightGraphAL(unsigned int);
        ~WeightGraphAL();
        void addEdge(Vertex, Vertex, Weight);
        void removeEdge(Vertex, Vertex);
        void buildSubgraph(unsigned int);
        void setSick(){sick = true;}
        unsigned int getNumVertices() {return numVertices;}
        unsigned int getNumEdges() {return numEdges;}
        unsigned int getSick(){return sick;}
        WeightGraphAL* getSubgraph(unsigned int i){return subGraphs[i];}
        list<VertexWeightPair> getAdj(Vertex v) {return adj[v];}


        //Dijkstra
        void Dijkstra(unsigned int, unsigned int);
        vector<Vertex> getMinPath() {return minPath;}

        //Kruskal
        void Kruskal();
        float getMstWeight(){return mst.sum;}
};

WeightGraphAL::WeightGraphAL(){
    numEdges = numVertices = 0;
    sick = false;
}

WeightGraphAL::WeightGraphAL(unsigned int numVertices): numVertices(numVertices){
    adj = new list<VertexWeightPair>[numVertices];
    numEdges = 0;
    subGraphs = new WeightGraphAL*[numVertices];
    for (unsigned int i =0; i < numVertices; i++){
        subGraphs[i] = new WeightGraphAL;
    }
    sick = false;
}

WeightGraphAL::~WeightGraphAL(){
    for(unsigned int i = 0; i < numVertices; ++i){
        adj[i].clear();
    }
    delete[] adj;
    numVertices = numEdges = 0;
}

void WeightGraphAL::buildSubgraph(unsigned int num){
    numVertices = num;
    adj = new list<VertexWeightPair>[num];
}

void WeightGraphAL::addEdge(Vertex u, Vertex v, Weight w){
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
    numEdges++;

    vertexPair edge;
    edge.first.first = u;
    edge.first.second = v;
    edge.second = w;
    graph.push_back(edge);
}

void WeightGraphAL::removeEdge(Vertex u, Vertex v){
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
        numEdges--;
}

// TDA Fila de Prioridade com Heap Minimo
template<typename T>
class MinHeap{
    private:
        T heapArray[max];
        int capacity;
        int heapSize = 0;
    public:
       // MinHeap(int);
        void minHeapfy(int);
        int parent(int i) {return i/2;}
        int left(int i) {return 2*i;}
        int right(int i) {return 2*i + 1;}
        T extractMin();
        void insert(T);
        bool isEmpty();
        void buildHeapfy();
        int getHeapSize() {return heapSize;}
};

template<typename T>
void MinHeap<T>::minHeapfy(int i){
    int l = left(i);
    int r = right(i);

    int smallest;
    if(l <= heapSize && heapArray[l] < heapArray[i]){
        smallest = l;
    }else {
        smallest = i;
    }
    if(r <= heapSize && heapArray[r] < heapArray[smallest]){
        smallest = r;
    }
    if(smallest != i){
        swap(heapArray[i], heapArray[smallest]);
        minHeapfy(smallest);
    }
}

template<typename T>
void MinHeap<T>::buildHeapfy(){
    for(int i = heapSize / 2; i > 0; i--){
        minHeapfy(i);
    }
}

template<typename T>
T MinHeap<T>::extractMin(){
    T x = heapArray[0];
    heapArray[0] = heapArray[heapSize - 1];
    heapSize--;
    minHeapfy(0);
    //cout << "Extraiu";
    return x; 
}

template<typename T>
bool MinHeap<T>::isEmpty(){
    if(heapSize == 0){
        return true;
    } else{
        return false;
    }
}

template<typename T>
void MinHeap<T>::insert(T i){
    heapArray[heapSize++] = i;
    buildHeapfy();
}


//Algoritmo de Dijkstra
void WeightGraphAL::Dijkstra(unsigned int origin, unsigned int destiny){
    MinHeap<Vertex> queue;
    vector<Weight> distance(numVertices);
    vector<Vertex> predecessor(numVertices);

    for(unsigned int i = 0; i < numVertices; i++){
        distance[i] = inf;
        predecessor[i] = -1;
    }
    distance[origin] = 0;
    queue.insert(origin);
    while(!queue.isEmpty()){
        Vertex u = queue.extractMin();
        for(VertexWeightPair v: adj[u]){
            if(distance[v.vertex] > distance[u] + v.weight){
                distance[v.vertex] = distance[u] +  v.weight;
                predecessor[v.vertex] = u;
                queue.insert(v.vertex);
            }
        }
    }   
    
    minPath.push_back(destiny);
    Vertex v = destiny;
    while(v != origin){
        v = predecessor[v];
        minPath.push_back(v);
    }

}

//Algoritmo de Kruskal
void WeightGraphAL::Kruskal(){
    UnionFind unionfinder{numVertices};
    unionfinder.MakeSet();

    for(unsigned int i = 0; i < numEdges; i++){
        for(unsigned int j = 0; j < numEdges - i - 1; j++){
            if(graph[j].second > graph[j + 1].second){
                swap(graph[j], graph[j + 1]);
            }
        }
    }
    float sum = 0;

    for(unsigned int i = 0; i < graph.size(); i++){
        if(unionfinder.FindSet(graph[i].first.first) != unionfinder.FindSet(graph[i].first.second)){
            mst.pairs.push_back(graph[i]);
            unionfinder.Union(graph[i].first.first, graph[i].first.second);
        }
    }
    for (unsigned int i = 0; i < mst.pairs.size(); i++){
        sum += mst.pairs[i].second;
    }
    mst.sum = sum;
}

void input_graph(WeightGraphAL &g, unsigned int numEdges){
    Vertex u = 0, v = 0;
    Weight w = 0;
    for(unsigned int i = 0; i < numEdges; i++){
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
}

int main(){
    unsigned int numVertices = 0;
    unsigned int numEdges = 0;
    cin >> numVertices >> numEdges;
    WeightGraphAL brain{numVertices + 1};
    input_graph(brain, numEdges);
    

    unsigned int entrance = 0;
    unsigned int exit = 0;

    cin >> entrance >> exit;

    brain.Dijkstra(entrance, exit);

    for (unsigned int i = 1; i <= numVertices; i++){
        unsigned int numVerticesSub = numEdges = 0;
        unsigned int numSick = 0;
        unsigned int sickVertices;
        cin >> numVerticesSub >> numEdges;
        cin >> numSick;

        brain.getSubgraph(i)->buildSubgraph(numVerticesSub + 1);
        if(numSick > 0){
            brain.getSubgraph(i)->setSick();
            for(unsigned int j = 0; j < numSick; j++){
                cin >> sickVertices;
            }
        }
        input_graph(*brain.getSubgraph(i), numEdges);
    }


    float sum = 0;
    for(auto i: brain.getMinPath()){
        if(brain.getSubgraph(i)->getSick() == 1){
            brain.getSubgraph(i)->Kruskal();
            sum += brain.getSubgraph(i)->getMstWeight();

        }
    }

    cout << sum;
    return 0;
}