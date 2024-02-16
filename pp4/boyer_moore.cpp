#include <iostream>
#include <vector>
#define alphabet_size 27
using namespace std;

void computes_jump_table(string pattern, char *R){
    int M = pattern.size();
    for(int i = 0; i < alphabet_size; ++i){
        R[i] = -1;
    }

    for(int j = 0; j < M; ++j){
        R[pattern[j] - 65] = j;
    }
}

void Boyer_Moore(string text, string pattern){
    int N = text.size();
    int M = pattern.size();
    int jump = 0;
    char R[alphabet_size];
    computes_jump_table(pattern, R);
    // for(int i = 0; i < 27; i++){
    //     cout << R[i] << ", ";
    // }

    for(int i = 0; i <= N - M; i += jump){
        jump = 0;
        int j = M -1;
        for(; j >= 0; j--){
            if(pattern[j] != text[i + j]){
                jump = j - R[text[i + j]];
            }
            if(jump < 1) {jump = 1;}
        }
        if(jump == 0){
            cout << jump;
            cout << i; // Deslocamento
            jump = 1;
        }
    }
}

int main(){
    string text = "ABCACAIODFGH";
    string pattern = "CAIO";

    cout << "Text: " << text << endl;
    cout << "Pattern: "<< pattern << endl;

    Boyer_Moore(text, pattern);
    return 0;
}