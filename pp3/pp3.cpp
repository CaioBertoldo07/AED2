#include <iostream>
#include <list>
#include <vector>

using namespace std;

typedef unsigned int Neurons;
typedef Neuron_blocks Block; // No cérebro(grafo principal), os vértices serão de blocos de neurônios(subgrafos) 
typedef float Weight;

// Classe VertexWeightPair para os subgrafos(blocos de neurônios)
class VertexWeightPair_sub {
    public:
        Neurons neurons;
        Weight weight;
        VertexWeightPair_sub(Neurons neurons, Weight weight): neurons(neurons), weight(weight) {}
};

// Classe VertexWeightPair para o grafo(cérebro)
class VertexWeightPair_brain {
    public:
        Block block;
        Weight weight;
        VertexWeightPair_brain(Block block, Weight weight): block(block), weight(weight) {}
};

// Classe que dará origem aos subgrafos(blocos de neurônios) que são vértices do grafo principal
class Neuron_blocks {
    private:
        unsigned int num_neurons; // Quantidade de neurônios(vértices) que vão estar nos subgrafos(blocos de neurônios)
        unsigned int num_synapses_sub; // Quantidades de sinapses(arestas)
        list<VertexWeightPair_sub>* adj; // Lista de adjacência dos subgrafos(blocos de neurônios)
    
    public:
        Neuron_blocks(unsigned int) {}
        ~Neuron_blocks() {}
        void add_synapse_sub(Neurons, Neurons, Weight);
        unsigned int get_num_synapses_sub() {return num_synapses_sub;}
        unsigned int get_num_neurons() {return num_neurons;}
};

Neuron_blocks::Neuron_blocks(unsigned int num_neurons): num_neurons(num_neurons){
    adj = new list<VertexWeightPair_sub>[num_neurons];
}

Neuron_blocks::~Neuron_blocks(){
    for(unsigned int i = 0; i < num_neurons; i++){
        adj[i].clear();
    }
    num_synapses_sub = num_neurons = 0;
    delete[] adj;
}

void Neuron_blocks::add_synapse_sub(Neurons u, Neurons v, Weight w){
    VertexWeightPair_sub neuron_V{v, w};
    adj[u].push_back(neuron_V);
    VertexWeightPair_sub neuron_U{u, w};
    adj[v].push_back(neuron_U);
    num_synapses_sub++;
}

// Classe que dará origem ao grafo principal(cérebro)
class Brain {
    private:
        unsigned int num_blocks; // Quantidade de blocos de neurônios(vértices(subgrafos))
        unsigned int num_synapses; // Quantidade de sinapses(arestas)
        list<VertexWeightPair_brain>* adj_2; // Lista de adjacência dos blocos do cérebro(grafo principal)
    public:
        Brain(unsigned int);
        ~Brain();
        void add_synapse(Block, Block, Weight);
        unsigned int get_num_synapses() {return num_synapses;}
        unsigned int get_num_blocks() {return num_blocks;}
};

Brain::Brain(unsigned int num_blocks): num_blocks(num_blocks) {
    adj_2 = new list<VertexWeightPair_brain>[num_blocks];
}

Brain::~Brain(){
    for(unsigned int i = 0; i < num_blocks; i++){
        adj_2[i].clear();
    }
    num_blocks = num_synapses = 0;
    delete[] adj_2;
}

void Brain::add_synapse(Block u, Block v, Weight w){
    VertexWeightPair_brain block_V {v, w};
    adj_2[u].push_back(v);
    VertexWeightPair_brain block_U {u, w};
    adj_2[v].push_back(u);
    num_synapses++;
}
