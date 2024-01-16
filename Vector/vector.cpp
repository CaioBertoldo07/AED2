// Initialize a vector
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    // Create a vector containing intergers
    vector<int> v = {8, 4, 5, 9}; // or v[8, 4, 5, 9]

    // Overwrite element at position 2
    v[2] = -1;

    cout << "\nPrint out the vector: ";
    for(int value: v)
        cout << value << " ";
    cout << "\n";
    return 0;
}
