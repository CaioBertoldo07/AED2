#include <iostream>

using namespace std;

void inc(int &v){
    v++;
}

void swap(int &a, int &b){
    int t = a;
    a = b;
    b = t;
}

int main(){

    int x = 1234;
    int y = 2222;

    cout << "antes:" << x << "\n" << y << "\n";
    swap(x, y);
    cout << "depois:" << x << "\n" << y << "\n";

    return 0;
}
