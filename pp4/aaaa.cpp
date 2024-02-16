#include <iostream>
#include <list>
#include <vector>
#include <math.h>
using namespace std;

#define alphabet_ASCII 256
class HashTable {
    private:
        unsigned int tot_elements;
        list<pair<char, string>> *table;
    public:
        HashTable(unsigned int);
        ~HashTable();
        void insert(char, string);
        int index_hash(string);
        void print_table();
};

HashTable::HashTable(unsigned int n){
    tot_elements = n;
    table = new list<pair<char, string>>[tot_elements];

    // Inserindo os valores da tabela
    insert('A', ":::");
    insert('B', ".::");
    insert('C', ":.:");
    insert('D', "::.");
    insert('E', ":..");
    insert('F', ".:.");
    insert('G', "..:");
    insert('H', "...");
    insert('I', "|::");
    insert('J', ":|:");
    insert('K', "::|");
    insert('L', "|.:");
    insert('M', ".|:");
    insert('N', ".:|");
    insert('O', "|:.");
    insert('P', ":|.");
    insert('Q', ":.|");
    insert('R', ".|.");
    insert('S', "..|");
    insert('T', "..|");
    insert('U', ".");
    insert('V', "||.");
    insert('W', "-.-");
    insert('X', ".--");
    insert('Y', "--.");
    insert('Z', "---");
    insert(' ', "~~~");
    insert('.', "~~~");
}

int HashTable::index_hash(string Key){
    const int M = 7; // tamanho da tabela
    int hash = 0;
    for(unsigned int i = 0; i < Key.length(); i++){
        hash += static_cast<int>(Key[i]) * (int) pow(alphabet_ASCII, Key.length() - i - 1) % M;
    }
    return hash % M;
}

void HashTable::insert(char c, string code){
    int index = index_hash(&c);
    pair<char, string> coordinate;
    coordinate.first = c;
    coordinate.second = code;
    table[index].push_back(coordinate);
}

void HashTable::print_table(){
    for(int i = 0; i < 7; i++){
        cout << endl << i << endl;
        for(pair<char, string> j: table[i]){
            cout << j.first << ": " << j.second << ";";
        }
        cout << endl;
    }
}

int main(){
    HashTable h{7};
    h.print_table();
    return 0;
}