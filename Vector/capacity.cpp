// capacity function in vector
#include <iostream>
#include <vector>

using namespace std;
int main(){
    vector<int> v;

    for(int i = 1; i <= 5; i++)
        v.push_back(i);

    cout << "Size: " << v.size();
    cout << "\nCapacity: " << v.capacity();
    cout << "\nMax Size: " << v.max_size();

    // cheks if the vector is empty or not
    if(v.empty() == false)
        cout << "\nVector is not empty";
    else
        cout << "\nVector is empty";

    cout << "\nVector elements are: ";
    for(auto it = v.begin(); it != v.end(); it++)
        cout << *it << " ";
    
    return 0;
}