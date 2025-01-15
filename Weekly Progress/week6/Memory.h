#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <iostream>
#include <bitset>

class Memory {
private:
    std::vector<int> memory;

public:
    Memory(size_t size) {
        memory.resize(size, 0);
        std::cout << "[Memory Initialized] Total Size: " << size << " bytes" << std::endl;
    }

    void write(size_t address, int data) {
        if (address < memory.size()) {
            memory[address] = data;
            std::cout << "[Memory Write] Address: " << std::bitset<8>(address) << ", Data: " << std::bitset<8>(data) << std::endl;
        } else {
            std::cerr << "[Memory Error] Invalid address." << std::endl;
        }
    }

    int read(size_t address) {
        if (address < memory.size()) {
            int data = memory[address];
            std::cout << "[Memory Read] Address: " << std::bitset<8>(address) << ", Data: " << std::bitset<8>(data) << std::endl;
            return data;
        } else {
            std::cerr << "[Memory Error] Invalid address." << std::endl;
            return -1;
        }
    }

    void print_segments() {
        std::cout << "=== Memory Segmentation ===" << std::endl;
        std::cout << "Code Segment: 0x00 - 0x03" << std::endl;
        std::cout << "Data Segment: 0x04 - 0x07" << std::endl;
        std::cout << "Stack Segment: 0x08 - 0x0B" << std::endl;
        std::cout << "Heap Segment: 0x0C - 0x0F" << std::endl;
        std::cout << "===========================" << std::endl;
    }
};

#endif