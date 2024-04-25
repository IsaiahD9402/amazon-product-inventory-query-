#pragma once

#include <string>

#include "header.h"

struct Product 
{
    std::string uniqId;
    std::string name;
    std::string brand;
    std::vector<std::string> categories;
    std::string listPrice;
    std::string sellingPrice;
    std::string quantity;
    std::string modelNumber;
    std::string aboutProduct;
    std::string productUrl;
    Product* next; // Pointer to next product in case of collision
};

class HashTable 
{
private:
    static const int TABLE_SIZE = 20000; 
    Product* table[TABLE_SIZE];

    size_t hashFunction(const std::string& key);
   

public:
    HashTable();

    void insertProduct(Product* product);

    Product* findProduct(const std::string& uniqId);
    
    // Implement function to list products belonging to a specific category
    void listProductsByCategory(const std::string& category);
};
