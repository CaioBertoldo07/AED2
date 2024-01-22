#include <iostream>
#include <list>
#include <vector>
#include <limits>

#define null -1
#define max 100

using namespace std;

float inf = numeric_limits<float>::infinity();
// Classe para o heap mínimo
template<typename T>
class MinHeap {
    private:
        T *heap_array; // ponteiro para o vetor de elementos na heap
        int capacity; // tamanho máximo do heap mínimo
        int heap_size; // número atual de elementos no heap mínimo
    public:
        MinHeap(int); // construor
        void MinHeapfy(int); // método para heapificar uma subárvore com a raiz em determinado índice i
        int parent(int i) {return (i - 1) / 2;} // método para obter o índice do pai do nó no índice i
        int left(int i) {return (2 * i) + 1;} // método para obter o índice do filho esquerdo do nó no índice i
        int right(int i) {return (2 * i) + 2;} // método para obter o índice do filho direito do nó no índice i
        T extractMin(); // método para remover o elemento com chave mínima(ou a raiz) do heap mínimo
        void decrease(int, int); // método para diminuir o valor da chave no índice i para new_val
        int get_min() {return heap_array[0];} // Retorna a chave mínima (chave na raiz) do heap mínimo
        void delete_key(int); //método exclui chave no índice i (Primeiro reduziu o valor para menos infinito, depois chama extractMin())
        void insert_key(T); // método para inserir nova chave 'k'
        int get_heap_size() {return heap_size;} // Retorna o tamnho da fila
        T* get_heap_array() {return heap_array;}
};

template<typename T>
MinHeap<T>::MinHeap(int capacity){
    this->heap_size = 0;
    this->capacity = capacity;
    this->heap_array = new T[capacity];
}

template<typename T>
void MinHeap<T>::MinHeapfy(int i){
    // Método recursivo para heapficar o heap_array
    int l = left(i);
    int r = right(i);

    int smallest = i;
    if(l < heap_size && heap_array[l] < heap_array[i]){
        smallest = l;
    } 

    if(r < heap_size && heap_array[r] < heap_array[smallest]){
        smallest = r;
    }

    if(smallest != i){
        swap(heap_array[i], heap_array[smallest]);
        MinHeapfy(smallest);
    }
}

template<typename T>
T MinHeap<T>::extractMin(){
    if(heap_size <= 0){
        return INT8_MAX;
    }
    if(heap_size == 1){
        heap_size--;
        return heap_array[0];
    }

    // remove o valor mínimo do heap
    T root = heap_array[0];
    heap_array[0] = heap_array[heap_size - 1];
    heap_size--;
    MinHeapfy(0);

    return root;
}

template<typename T>
void MinHeap<T>::decrease(int i, int new_value){
    heap_array[i] = new_value;
    while(i != 0 && heap_array[parent(i)] > heap_array[i]){
        swap(heap_array[i], heap_array[parent(i)]);
        i = parent(i);
    }
}

template<typename T>
void MinHeap<T>::delete_key(int i){
    decrease(i, INT8_MIN);
    extractMin();
}

template<typename T>
void MinHeap<T>::insert_key(T k){
    if(heap_size == capacity){
        cout << "\nOverflow: Couldn't insert key";
        return;
    }

    // Inserindo a nova chave no final
    int i = heap_size;
    heap_array[heap_size++] = k;

    while(i != 0 && heap_array[parent(i)] > heap_array[i]){
        swap(heap_array[i], heap_array[parent(i)]);
        i = parent(i);
    }
}

void print_heap(MinHeap<int> &queue){
    for(int i = 0; i < queue.get_heap_size(); i++){
        cout << queue.get_heap_array();
    }
}

int main(){
    MinHeap<int> q{max};
    for(int i = 0; i < 10; i++){
        q.insert_key(i);
    }
    print_heap(q);
}