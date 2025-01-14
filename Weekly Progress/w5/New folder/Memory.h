#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <vector>
#include <stdexcept>  // For handling exceptions

class Memory {
private:
    std::vector<int> dataMemory;  // For data segment (addresses 0-3)
    std::vector<int> stackMemory; // For stack segment
    std::vector<int> heapMemory;  // For heap segment

public:
    Memory(int dataSize = 4, int stackSize = 4, int heapSize = 4);
    void storeData(int address, int value);
    int loadData(int address) const;
    
    void storeStack(int address, int value);
    int loadStack(int address) const;
    
    void storeHeap(int address, int value);
    int loadHeap(int address) const;
    
    void printMemory() const;  // Display current memory content
};

#endif
