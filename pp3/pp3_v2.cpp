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
        unsigned int entrance;
        unsigned int exit;
        bool sick;
        
        list<VertexWeightPair> *adj;
        vector<pair<pair<unsigned int,unsigned int>,float>> graph;
        
    public:
        WeightGraphAL* sub_graphs;
        WeightGraphAL();
        WeightGraphAL(unsigned int);
        ~WeightGraphAL();
        void add_edge(Vertex, Vertex, Weight);
        void remove_edge(Vertex, Vertex);
        void setEntrance(unsigned int entry){entrance = entry;}
        void setExit(unsigned int ext){exit = ext;}
        void build_subgraph(unsigned int);
        void turnsick(){sick = true;}
        pair<pair<unsigned int, unsigned int>, float> getPair(unsigned int i){return graph[i];}
        unsigned int getVectorSize(){return graph.size();}
        unsigned int getEntrance() {return entrance;}
        unsigned int getExit() {return exit;}
        unsigned int get_num_vertices() {return num_vertices;}
        unsigned int get_num_edges() {return num_edges;}
        unsigned int getSick(){return sick;}
        list<VertexWeightPair> get_adj(Vertex v) {return adj[v];} 
};

WeightGraphAL::WeightGraphAL(){
    entrance = exit = num_edges = num_vertices = 0;
    sick = false;
}

WeightGraphAL::WeightGraphAL(unsigned int num_vertices): num_vertices(num_vertices){
    adj = new list<VertexWeightPair>[num_vertices];
    entrance = exit = num_edges = 0;
    sub_graphs = new WeightGraphAL[num_vertices];
    sick = false;
}

WeightGraphAL::~WeightGraphAL(){
    for(unsigned int i = 0; i < num_vertices; ++i){
        adj[i].clear();
    }
    delete[] adj;
    delete[] sub_graphs;
    num_vertices = num_edges = entrance = exit = 0;
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

    pair<pair<unsigned int, unsigned int>,float> edge;
    edge.first.first = u;
    edge.first.second = v;
    edge.second = w;
    graph.push_back(edge);
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

void display_list(list<VertexWeightPair> lst){
    for(VertexWeightPair itemVertex: lst){
        cout << "(" << itemVertex.vertex << ", " << itemVertex.weight << "), ";
    }
    cout << endl;
}

void display_graph(WeightGraphAL &g){
    cout << "num_vertices: " << g.get_num_vertices() <<  endl;
    cout << "num_edges: " << g.get_num_edges() << endl;
    for(unsigned int v = 0; v < g.get_num_vertices(); v++){
        cout << v + 1 << ": ";
        list<VertexWeightPair> lst = g.get_adj(v);
        display_list(lst);
    }
    cout << "entrada: " << g.getEntrance() << " saida: "<< g.getExit() << endl << endl;
}

void display_subgraph(WeightGraphAL &g){
    cout << "num_vertices: " << g.get_num_vertices() <<  endl;
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
        g.add_edge(u - 1, v - 1, w);
    }
}

class UnionFind{
    private:
        unsigned int *parent;
    public:
        UnionFind(){};
        ~UnionFind();
        void BuildParent(unsigned int);
        unsigned int FindSet(unsigned int);
        void MakeSet(unsigned int);
        void Union(unsigned int, unsigned int);
};

void UnionFind::BuildParent(unsigned int num_elementos){
    parent = new unsigned int[num_elementos];
};

UnionFind::~UnionFind(){
    delete[] parent;
}

void UnionFind::MakeSet(unsigned int x){
    parent[x] = x;
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

class Mst{
    public:
        vector<pair<pair<unsigned int,unsigned int>,float>> pares;
        float sum;
        Mst();
        ~Mst();
};

Mst::Mst(){
    sum = 0;
}

Mst::~Mst(){
    sum = 0;
    pares.clear();
}

class Kruskal{
    private:
        WeightGraphAL graph;
        pair<pair<unsigned int, unsigned int>,float>* ordenedgraph;
        UnionFind unifier;
        Mst mst;
    public:
        Kruskal(WeightGraphAL);
        ~Kruskal();
        void organize(pair<pair<unsigned int, unsigned int>, float>*);
        void MstBuilder();
        float getMstWeight(){return mst.sum;}

};

Kruskal::Kruskal(WeightGraphAL graph): graph(graph){
    
    unifier.BuildParent(graph.get_num_vertices());
    
    ordenedgraph = new pair<pair<unsigned int, unsigned int>,float>[graph.get_num_vertices()];
       
    /*for(unsigned int i =0 ; i < graph.getVectorSize(); i++){
        ordenedgraph[i] = graph.getPair(i);
    }*/
    cout << "oiii";
}

Kruskal::~Kruskal(){
    delete[] ordenedgraph;
};

void Kruskal::organize(pair<pair<unsigned int, unsigned int>, float>* g){
    for(unsigned int i = 0; i < graph.get_num_vertices(); i++){
        for(unsigned int j = 0; j < graph.get_num_vertices() - i - 1; j++){
            if(g[j].second > g[j + 1].second){
                swap(g[j].second, g[j + 1].second);
            }
        }
    }
}

void Kruskal::MstBuilder(){
        for(unsigned int i = 0; i < graph.get_num_vertices(); i++){
        unifier.MakeSet(i);
    }
    organize(ordenedgraph);
    float sum = 0;

    for(unsigned int i = 0; i < graph.get_num_vertices(); i++){
        if(unifier.FindSet(ordenedgraph[i].first.first) != unifier.FindSet(ordenedgraph[i].first.second)){
            mst.pares.push_back(ordenedgraph[i]);
            unifier.Union(ordenedgraph[i].first.first, ordenedgraph[i].first.second);
        }
    }
    for (unsigned int i = 0; i < mst.pares.size(); i++){
        sum += mst.pares[i].second;
    }
    mst.sum = sum;
}

int main(){
    unsigned int num_vertices = 0;
    unsigned int num_edges = 0;
    cin >> num_vertices >> num_edges;
    WeightGraphAL brain{num_vertices};
    input_graph(brain, num_edges);
    

    unsigned int entrance = 0;
    unsigned int exit = 0;

    cin >> entrance >> exit;
    brain.setEntrance(entrance);
    brain.setExit(exit);
    
    display_graph(brain);

    for (unsigned int i = 0; i < num_vertices; i++){
        unsigned int num_vertices_sub = num_edges = 0;
        unsigned int num_sick = 0;
        unsigned int sick_vertices;
        cin >> num_vertices_sub >> num_edges;
        cin >> num_sick;

        brain.sub_graphs[i].build_subgraph(num_vertices_sub);
        if(num_sick > 0){
            brain.sub_graphs[i].turnsick();
            for(unsigned int j = 0; j < num_sick; j++){
                cin >> sick_vertices;
            }
        }
        input_graph(brain.sub_graphs[i], num_edges);
        //Kruskal kruskal{brain.sub_graphs[i]};
        //cout << "oi";
        //kruskal.MstBuilder();
        //cout << "\nPeso da MST: " << kruskal.getMstWeight();
    }
    display_graph(brain);
    for (unsigned int i = 0; i < num_vertices; i++){
        display_subgraph(brain.sub_graphs[i]);
    }
    
    return 0;
}