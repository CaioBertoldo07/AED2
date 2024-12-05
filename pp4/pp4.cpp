#include <iostream>
#include <list>
#include <vector>
#include <math.h>

using namespace std;

class HashTable
{
    private:
        unsigned int table_size;
        list<pair<char, string>> *table;
        char *letters_vector;

    public:
        HashTable(unsigned int);
        ~HashTable();
        int perfect_hash(string);
        void insert_value(char, string);
        char search_letter(string);
        void show();
        int get_k_value(string);
        string decode(int, string, string);

};

HashTable::HashTable(unsigned int n)
{
    table_size = n;
    table = new list<pair<char, string>>[table_size];
    
    insert_value('A', ":::");
    insert_value('B', ".::");
    insert_value('C', ":.:");
    insert_value('D', "::.");
    insert_value('E', ":..");
    insert_value('F', ".:.");
    insert_value('G', "..:");
    insert_value('H', "...");
    insert_value('I', "|::");
    insert_value('J', ":|:");
    insert_value('K', "::|");
    insert_value('L', "|.:");
    insert_value('M', ".|:");
    insert_value('N', ".:|");
    insert_value('O', "|:.");
    insert_value('P', ":|.");
    insert_value('Q', ":.|");
    insert_value('R', "|..");
    insert_value('S', ".|.");
    insert_value('T', "..|");
    insert_value('U', ".||");
    insert_value('V', "|.|");
    insert_value('W', "||.");
    insert_value('X', "-.-");
    insert_value('Y', ".--");
    insert_value('Z', "--.");
    insert_value(' ', "---");
    insert_value('.', "~~~");

    char letter = 'A';
    letters_vector = new char[28];

    for(int i = 0; i < 26; i++)
    {
        letters_vector[i] = letter;
        letter++;
    }

    letters_vector[26] = ' ';
    letters_vector[27] = '.';
    
}

HashTable::~HashTable()
{
    for (unsigned int i=0; i<table_size; i++)
        table[i].clear();
    
    delete[] table;

    table = nullptr;
    table_size = 0;
}

int HashTable::perfect_hash(string key)
{
    int TAM_ASCII = 256;
    int M = 7; // tamanho da tabela
    int hash = 0;
    int len = key.length();
    for (int i = 0; i < len; i++) 
        hash += static_cast<int>(key[i]) * (int)pow(TAM_ASCII, len - i - 1) % M;
    
    return hash % M;

}

void HashTable::insert_value(char letter, string code)
{
    int id = perfect_hash(code);
    pair <char, string> test;

    test.first = letter;
    test.second = code;
    table[id].push_back(test);
}

void HashTable::show()
{
    for (int i = 0; i < 7; i++)
    {
        cout << endl << "lista " << i << endl;

        for (pair<char, string> element: table[i])
            cout << "(" << element.first << ", " << element.second << ")" << "; ";
        
        cout << endl;
    }
}

char HashTable::search_letter(string code)
{
    int id = perfect_hash(code);
    for (auto it = table[id].begin(); it != table[id].end(); it++)
    {
        if ((*it).second == code)
            return (*it).first;
    }
    return '\0';
}

int HashTable::get_k_value(string coded_message)
{
    string compare = "MENSAGEM", coded_msg;
    int k = 0;

    for (int i = 0; i < 8; i++)
        coded_msg += coded_message[i];

    if (compare == coded_msg)
        return k;
    else
    {
        while (coded_msg[0] != 'M')
        {
            k -= 1;
            coded_msg[0] -= 1;
        }

        return k;
    }
}

string HashTable::decode(int k, string coded_message, string decoded_message)
{
    int reverse = 0;
    char reverse_char;
    int coded_len = coded_message.size();
    for (int i = 0; i < coded_len; i++)
    {
        if (coded_message[i] == '.')
            decoded_message += '.';

        else if (coded_message[i] != ' ')
        {
            if (((int)coded_message[i] + k) < 65)
            {
                reverse = 65 - ((int)coded_message[i] + k);
                reverse_char = 91 - reverse;

                decoded_message += reverse_char;
            }
            else
                decoded_message += (int)coded_message[i] + k;
        }
        else
            decoded_message += ' ';
    }

    return decoded_message;
}


class BoyerMoore
{
    private:
        string T;
        string P;
        int N;
        int M;
        int salto;

    public:
        BoyerMoore(string, string);
        void Computa_Tabela_Saltos(int *);
        void BoyerMoore_process(int *);
};

BoyerMoore::BoyerMoore(string T_out, string P_out)
{
    T = T_out;
    P = P_out;
    N = T.size();
    M = P.size();
    salto = 0;
}

void BoyerMoore::Computa_Tabela_Saltos(int *R)
{
    for (int i = 0; i < 26; i++)
        R[i] = -1;

    for (int j = 0; j < M; j++)
        R[P[j] - 65] = j;

    R[26] = -1;
    R[27] = -1;
}

void BoyerMoore::BoyerMoore_process(int *R)
{
    for (int i = 0; i <= N - M; i += salto)
    {
        salto = 0;

        int j = M - 1;

        for (; j >= 0; j--)
        {
            if (P[j] != T[i + j])
            {
                // cout << "i = " << i << " ; j = " << j << " ; T[i + j] = " << T[i + j] << endl;

                if (T[i + j] == ' ')
                {
                    salto = j - R[T[i + j] - 6];
                    cout << salto << " ";
                }

                else if (T[i + j] == '.')
                {
                    salto = j - R[T[i + j] - 19];
                    cout << salto << " ";
                }
                else
                {
                    salto = j - R[T[i + j] - 65];

                    if (salto >= 1)
                        cout << salto << " ";
                }
                
                if (salto < 1)
                {
                    salto = 1;
                    cout << salto << " ";
                }   
                break;
            }
        }

        if (salto == 0)
        {
            cout << salto << " ";
            cout << "(" << i << ") ";
            salto = 1;
        }
    }
    cout << endl;
}


int main()
{
    //creating hash table
    int k = 0;
    unsigned int hash_table_size = 7;
    HashTable ht{hash_table_size};

    string et_phrase;
    cin >> et_phrase;

    int et_phrase_size = et_phrase.size();

    string charac, codificado, decodificado;

    for (int i = 0; i < et_phrase_size; i += 3)
    {
        charac += et_phrase[i];
        charac += et_phrase[i + 1];
        charac += et_phrase[i + 2];

        codificado += ht.search_letter(charac);
        charac = "";
    }

    k = ht.get_k_value(codificado);

    decodificado = ht.decode(k, codificado, decodificado);

    // cout << "Decodificado.size() = " << decodificado.size() << "Decodificado: " << decodificado << endl;

    string word;
    vector<string> words_vector;
    int word_size;

    while (true)
    {
        cin >> word;

        if(word == "fim")
            break;
            
        word_size = word.size();

        for (int k = 0; k < word_size; k++)
            word[k] = toupper(word[k]);

        words_vector.push_back(word);
    }

    int R[28];

    vector<string>::iterator it;
    for(it = words_vector.begin(); it != words_vector.end(); it++)
    {
        cout << *it << ": ";

        BoyerMoore bm{decodificado, *it};

        bm.Computa_Tabela_Saltos(R);

        bm.BoyerMoore_process(R);
    }

    return 0;
}