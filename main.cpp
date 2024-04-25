#include "header.h"
#include "HashTable.h"

int main()
{
    auto start = chrono::high_resolution_clock::now();
    string line;
    HashTable inventory;
    bootStrap(inventory); 
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    cout << duration.count() << endl;
    
    return 0;
}
