#pragma once

#include <iostream>
#include <string>
#include <functional> // For std::hash
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <future>
#include <chrono>

using namespace std;

class HashTable;

void printHelp();
bool validCommand(string line);
void evalCommand(string line, HashTable& inventory);
void bootStrap(HashTable& inventory);
string trim(const string& str);
void bootStrapCommand(HashTable& inventory);
void bootStrapReader(HashTable& inventory);

