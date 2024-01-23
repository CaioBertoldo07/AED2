#include <iostream>
#include <list>
#include <vector>
#include <limits>

#define null -1
#define max 100
using namespace std;

float inf = numeric_limits<float>::infinity();

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
    cout << "Extraiu";
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
    for(int i = 0; i < heap_size; i++){
        cout << heap_array[i] << " ";
    }
}

int main(){
    MinHeap<int> q{max};
    for(int i = 0; i < 10; i++){
        q.insert(i);
    }
    q.print_heap();

    q.extractMin();
    cout << endl;
    q.print_heap();
    return 0;
}