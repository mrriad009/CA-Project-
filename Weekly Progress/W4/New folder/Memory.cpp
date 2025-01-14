#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <vector>  // provide & manage dynamic array 
using namespace std;

class Memory {
public:
    vector<int> memory;

    Memory(int size) : memory(size, 0) {}  //Initializes the memory with a specified size, setting all values to 0

   //storing value to specific memeroy addrs
   
    void store(int address, int value) {
        if (address < memory.size()) {
            memory[address] = value;
            cout << "Memory: Stored value " << value << " at address " << address << endl;
        } else {
            cout << "Memory Error: Address " << address << " out of bounds!" << endl;
        }
    }
//for lead value from  memory addrs

    int load(int address) {
        if (address < memory.size()) {
            cout << "Memory: Loaded value " << memory[address] << " from address " << address << endl;
            return memory[address];
        }
        cout << "Memory Error: Address " << address << " out of bounds!" << endl;
        return 0;
    }
};

#endif
