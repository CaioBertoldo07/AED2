#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

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

class Graph {
    private:
        vector<pair<pair<unsigned int,unsigned int>,float>> graph;
        vector<pair<pair<unsigned int,unsigned int>,float>> mst;
        unsigned int num_vertices;
        // unsigned int *parent;
    public:
        Graph(unsigned int);
        ~Graph();
        void add_edge(unsigned int, unsigned int, float);
        unsigned int get_num_vertices() {return num_vertices;}
        vector<pair<pair<unsigned int,unsigned int>,float>> get_graph() {return graph;}
        vector<pair<pair<unsigned int,unsigned int>,float>> get_mst() {return mst;}
        void Mst_Kruskal();
        // Bubble sort
        void bubble_sort(vector<pair<pair<unsigned int, unsigned int>, float>>);
        void display_mst();

};



void Graph::display_mst(){
    for(unsigned int i = 0; i < mst.size(); i++){
        cout << mst[i].first.first << " "  <<  mst[i].first.second << " " << mst[i].second << endl;
    }
}

Graph::Graph(unsigned int num_vertices){
    this->num_vertices = num_vertices;
    // parent = new unsigned int[num_vertices];
}

Graph::~Graph(){
    graph.clear();
    mst.clear();
    //delete [] parent;
    num_vertices = 0;
}

void Graph::add_edge(unsigned int u, unsigned int v, float w){
    pair<pair<unsigned int, unsigned int>,float> edge;
    edge.first.first = u;
    edge.first.second = v;
    edge.second = w;
    graph.push_back(edge);
}

void Graph::bubble_sort(vector<pair<pair<unsigned int, unsigned int>, float>> g){
    pair<pair<unsigned int, unsigned int>, float> aux;
    for(unsigned int i = 0; i < g.size(); i++){
        for(unsigned int j = 0; j < g.size() - i - 1; j++){
            if(g[j].second > g[j + 1].second){
                swap(g[j].second, g[j + 1].second);
            }
        }
    }
}

void Graph::Mst_Kruskal(){
    UnionFind u{num_vertices};
    u.make_set();
    bubble_sort(graph);

    for(unsigned int i = 0; i < graph.size(); i++){
        if(u.find_set(graph[i].first.first) != u.find_set(graph[i].first.second)){
            mst.push_back(graph[i]);
            u.Union(graph[i].first.first, graph[i].first.second);
            //cout<< "teste " << mst[i].first.first<<endl;
        }
    }
    //cout <<"size: "<< mst.size()<<endl;
}



int main(){

    Graph g{6};
    g.add_edge(0, 1, 0.5);
    g.add_edge(0, 2, 0.12);
    g.add_edge(1, 4, 0.2);
    g.add_edge(1, 3, 0.9);
    g.add_edge(2, 3, 0.1);
    g.add_edge(2, 5, 0.9);
    g.add_edge(3, 5, 0.7);
    g.add_edge(4, 3, 0.3);
    g.Mst_Kruskal();
    g.display_mst();
    return 0;
}