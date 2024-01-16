#include <iostream>
#include <list>
#include <vector>

using namespace std;
typedef unsigned int Vertex;

struct Position{
    pair<int, int> pos;
    int step;
};
typedef struct Position point;

template<typename T>
class Queue{ // Classe da fila para a busca
    private:
        list<T> lst;

    public:
        bool is_empty();
        void enqueue(T item);
        T dequeue();
        list<T> get_list() {return lst;}
        // void print_queue();

};


class Chessboard{ // Grafo (tabuleiro do xadrez)
    private:
        vector<pair<int,int>> visited;
        Queue<Position> q;
        list<Position> adj;

    public:
        // int Chess(pair<int,int>, pair<int,int>, pair<int,int>, pair<int,int>, pair<int,int>, int);
        ~Chessboard();
        bool check_vector(vector<pair<int,int>>, pair<int,int>);
        unsigned int search_pos_kinght(pair<int,int>);
};


// Funções do Grafo

Chessboard::~Chessboard(){
    visited.clear();
    adj.clear();
}

unsigned int Chessboard::search_pos_kinght(pair<int,int> knight){
    list<Position>::iterator it;
    for(it = adj.begin(); it != adj.end(); it++){
        if((*it).pos == knight){
            return (*it).step;
        } 
    }
    return (*it).step;
}

// Funções da Fila

template<typename T>
bool Queue<T>::is_empty(){
    if(lst.empty()){
        return true;
    } else{
        return false;
    }
}

template<typename T>
void Queue<T>::enqueue(T item){
    lst.push_back(item);
}

template<typename T>
T Queue<T>::dequeue(){
    T front = lst.front();
    lst.pop_front();
    return front;
}

bool Chessboard::check_vector(vector<pair<int, int>> v, pair<int, int> element){
    typename vector<pair<int, int>>::iterator it;
    for(it = v.begin(); it!=v.end(); it++){
        if(*it == element){
            return true;
        }
    }
    return false;
}

int Chess(pair<int,int> King, pair<int,int> Knight_1, pair<int, int> Knight_2, pair<int,int> Knight_3, pair<int,int> Knignt_4, int N){
    vector<bool> test(N + 1, false);
    vector<vector<bool>> visited(N + 1, test);
    pair<int, int> destiny = King;
    pair<int,int> k1 = Knight_1;
    pair<int,int> k2 = Knight_2;
    pair<int,int> k3 = Knight_3;
    pair<int,int> k4 = Knignt_4;
    Queue<Position> q;
     
    point source;
    source.pos = destiny;
    source.step = 0;
    q.enqueue(source);
    visited[k1.first][k1.second] = true;
    visited[k2.first][k2.second] = true;
    visited[k3.first][k3.second] = true;
    visited[k4.first][k4.second] = true;


    int gr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int gc[] = {-1, 1, -2, 2, 2, -2, 1, -1};
    
    while(!q.is_empty()){
        point tp = q.get_list().front();
        q.dequeue();

        int x = tp.pos.first;
        int y = tp.pos.second;

        if(x == King.first && y == King.second){
            return tp.step;
        }

        int nstep = tp.step + 1;
        for(int i = 0; i < 8; i++){
            int xn = x + gr[i];
            int yn = y + gc[i];
            if(xn < 1 || xn > N || yn < 1 || yn > N){
                continue;
            } else{
                if(visited[xn][yn] == false){
                    visited[xn][yn] = true;
                    point temp;
                    pair<int,int> tt = make_pair(xn, yn);
                    temp.pos = tt;
                    temp.step = nstep;
                    q.enqueue(temp);
                }
            }
        }
    }
    return -1;
}

void bubble_sort(vector<int> &v){
    int aux;
    for(unsigned int i = 0; i < v.size() - 1; i++){
        for(unsigned int j = 0; j < v.size() - i - 1; j++){
            if(v[i] > v[j]){
                aux = v[i];
                v[i] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

int main()
{
    int num_iterations;
    // cout << "NUm iter: \n";
    cin >> num_iterations;

    vector<int> response;
    for(int i = 0; i < num_iterations; i++){
        string k1, k2, k3, k4, king;
        cin >> k1 >> k2 >> k3 >> k4 >> king;
        pair<int, int> knight_1(int(k1[0] - 96), int(k1[1] - 48));
        pair<int, int> knight_2(int(k2[0] - 96), int(k2[1] - 48));
        pair<int, int> knight_3(int(k3[0] - 96), int(k3[1] - 48));
        pair<int, int> knight_4(int(k4[0] - 96), int(k4[1] - 48));
        pair<int, int> king0(int(king[0] - 96), int(king[1] - 48));
        Chessboard chess;
        // chess.Chess(king0, knight_1, knight_2, knight_3, knight_4, 64);

        // cout << "aaaaa";
        vector<pair<int,int>> horses;
        horses.push_back(knight_1);
        horses.push_back(knight_2);
        horses.push_back(knight_3);
        horses.push_back(knight_4);
        
        vector<int> found;
        for(int i = 0; i < 4; i++){
            // int x = (chess.search_pos_kinght(horses[i])) - 1;
            int x = Chess(king0, knight_1, knight_2, knight_3, knight_4, 64);
            found.push_back(x);
            // cout << found[i];
        }

        bubble_sort(found);
        int min = found[0];
        response.push_back(found[0]);
        
        for(int i = 1; i < 4; i++){
            if(found[i] == min){
                response.push_back(found[i]);
            }
        }
    }
    for(unsigned int i = 0; i < response.size(); i++){
        cout << response[i];
    }
    return 0;
}   