#include "header.h"
#include "HashTable.h"

void printHelp()
{
    cout << "Supported list of commands: " << endl;
    cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << endl;
    cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
         << endl;
}

bool validCommand(string line)
{
    return (line == ":help") ||
           (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory") == 0);
}

void evalCommand(string line, HashTable& inventory)
{
    if (line == ":help")
    {
        printHelp();
    }
    // if line starts with find
    else if (line.rfind("find", 0) == 0)
    {
        // Look up the appropriate datastructure to find if the inventory exist
        size_t pos = line.find(" ");
        if (pos != string::npos && pos + 1 < line.length()) 
        {
            string inventoryId = line.substr(pos + 1);
            Product* product = inventory.findProduct(inventoryId);
            if (product != nullptr)
            {
                // Print product details
                cout << "Product details:" << endl;
                cout << "Name: " << product->name << endl;
                cout << "Brand: " << product->brand << endl;
                for (const auto& category : product->categories) 
                {
                    cout << category << ", ";
                }
                cout << endl;;
                cout << "List Price: " << product->listPrice << endl;
                cout << "Selling Price: " << product->sellingPrice << endl;
                cout << "Quantity: " << product->quantity << endl;
                cout << "Model Number: " << product->modelNumber << endl;
                cout << "About Product: " << product->aboutProduct << endl;
                cout << "Product URL: " << product->productUrl << endl;
            }
            else 
            {
                cout << "Inventory/Product not found" << endl;
            }
        }
        else 
        {
            cout << "Invalid command format. Usage: find <inventoryid>" << endl;
        }
    }
    // if line starts with listInventory
    else if (line.rfind("listInventory", 0) == 0)
    {
        size_t pos = line.find(" ");
        if (pos != string::npos && pos + 1 < line.length()) 
        {
            string categoryString = line.substr(pos + 1);
            inventory.listProductsByCategory(categoryString);
        } 
        else 
        {
            cout << "Invalid command format. Usage: listInventory <category_string>" << endl;
        }
    }
}

void bootStrap(HashTable& inventory)
{
    // Code for reading data from CSV remains unchanged
    ifstream file("AmazonInventory.csv");
    if (!file.is_open()) 
    {
        cerr << "Error: Unable to open the CSV file." << endl;
        return;
    }

    string line;
    getline(file, line);
    while (getline(file, line)) 
    {
        stringstream lineStream(line);
        vector<string> tokens;
        string token;
        while (getline(lineStream, token, ',')) 
        {
            tokens.push_back(trim(token));
        }

        // Ensure tokens are parsed correctly and contain required fields
        if (!tokens.empty()) 
        {
            Product* product = new Product;
            product->uniqId = tokens.size() > 0 ? tokens[0] : "NA";
            product->name = tokens.size() > 1 ? tokens[1] : "NA";
            product->brand = tokens.size() > 2 ? tokens[2] : "NA";

            stringstream categoryStream(tokens.size() > 4 ? tokens[4] : "");
            string category;

            while (getline(categoryStream, category, '|')) 
            {
                product->categories.push_back(trim(category));
            }

            product->listPrice = tokens.size() > 7 ? tokens[7] : "NA";
            product->sellingPrice = tokens.size() > 8 ? tokens[8] : "NA";
            product->quantity = tokens.size() > 9 ? tokens[9] : "NA";
            product->modelNumber = tokens.size() > 10 ? tokens[10] : "NA";
            product->aboutProduct = tokens.size() > 11 ? tokens[11] : "NA";
            product->productUrl = tokens.size() > 19 ? tokens[19] : "NA";
            product->next = nullptr;
            inventory.insertProduct(product);
        }
    }

    file.close();

    cout << "\n> ";
    
    // Create two threads, one for reading from CSV and inserting products, and the other for handling user commands
    auto readerThread = std::async(std::launch::async, [&inventory]() {
        bootStrapReader(inventory);
    });

    auto commandThread = std::async(std::launch::async, [&inventory]() {
        bootStrapCommand(inventory);
    });

    // Wait for both threads to finish
    readerThread.wait();
    commandThread.wait();

}

void bootStrapReader(HashTable& inventory) 
{
    ifstream file("AmazonInventory.csv");
    if (!file.is_open()) 
    {
        cerr << "Error: Unable to open the CSV file." << endl;
        return;
    }

    string line;
    getline(file, line);
    while (getline(file, line)) 
    {
        stringstream lineStream(line);
        vector<string> tokens;
        string token;
        while (getline(lineStream, token, ',')) 
        {
            tokens.push_back(trim(token));
        }

        // Ensure tokens are parsed correctly and contain required fields
        if (!tokens.empty()) 
        {
            Product* product = new Product;
            product->uniqId = tokens.size() > 0 ? tokens[0] : "NA";
            product->name = tokens.size() > 1 ? tokens[1] : "NA";
            product->brand = tokens.size() > 2 ? tokens[2] : "NA";

            stringstream categoryStream(tokens.size() > 4 ? tokens[4] : "");
            string category;

            while (getline(categoryStream, category, '|')) 
            {
                product->categories.push_back(trim(category));
            }

            product->listPrice = tokens.size() > 7 ? tokens[7] : "NA";
            product->sellingPrice = tokens.size() > 8 ? tokens[8] : "NA";
            product->quantity = tokens.size() > 9 ? tokens[9] : "NA";
            product->modelNumber = tokens.size() > 10 ? tokens[10] : "NA";
            product->aboutProduct = tokens.size() > 11 ? tokens[11] : "NA";
            product->productUrl = tokens.size() > 19 ? tokens[19] : "NA";
            product->next = nullptr;
            inventory.insertProduct(product);
        }
    }

    file.close();

    cout << "\n> ";
}

void bootStrapCommand(HashTable& inventory) 
{
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    cout << "\n> ";

    string line;
    while (getline(cin, line) && line != ":quit") 
    {
        if (validCommand(line)) {
            evalCommand(line, inventory);
        } else {
            cout << "Command not supported. Enter :help for list of supported commands" << endl;
        }
        cout << "> ";
    }
}

// Function to trim whitespace from the beginning and end of a string
string trim(const string& str) 
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}