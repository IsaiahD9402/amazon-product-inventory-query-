#include "HashTable.h"
#include "header.h"

HashTable::HashTable()
{
    // Initialize hash table
    for (int i = 0; i < TABLE_SIZE; ++i) 
    {
        table[i] = nullptr;
    }
}

// Implement function to insert a product into the hash table
void HashTable::insertProduct(Product* product) 
{
    size_t index = hashFunction(product->uniqId);
    if (table[index] == nullptr) 
    {
        table[index] = product;
    } 
    else 
    {
        // Handle collision by chaining
        Product* current = table[index];
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = product;
    }
}

// Implement function to list products belonging to a specific category
void HashTable::listProductsByCategory(const string& category) 
{
    // Traverse the hash table and print products belonging to the specified category
    for (int i = 0; i < TABLE_SIZE; ++i) 
    {
        Product* current = table[i];
        while (current != nullptr) 
        {
            if (std::find(current->categories.begin(), current->categories.end(), category) != current->categories.end()) 
            {
                // Print product information
                cout << "ID: " << current->uniqId << ", Name: " << current->name << endl;
            }
            current = current->next;
        }
    }
}

// Implement function to find a product by its unique ID
Product* HashTable::findProduct(const string& uniqId)
{
    size_t index = hashFunction(uniqId);
    Product* current = table[index];
    while (current != nullptr) {
        if (current->uniqId == uniqId) 
        {
            return current;
        }
        current = current->next;
    }
    return nullptr; // Product not found
}

// Implement hash function using std::hash
size_t HashTable::hashFunction(const string& key) 
{
    return std::hash<string>{}(key) % TABLE_SIZE;
}


