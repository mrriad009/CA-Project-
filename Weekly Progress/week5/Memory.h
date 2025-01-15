#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <iostream>
#include <bitset>

class Memory {
public:
    Memory(size_t size) : memory(size, 0b00000000) {
        std::cout << "[Memory Initialized] Total Size: " << size << " bytes\n";
    }

    uint8_t read(uint16_t address) {
        if (address >= memory.size()) {
            throw std::out_of_range("Memory read out of bounds!");
        }
        std::cout << "[Memory Read] Address: " << address 
                  << ", Data: " << std::bitset<8>(memory[address]) << "\n";
        return memory[address];
    }

    void write(uint16_t address, uint8_t value) {
        if (address >= memory.size()) {
            throw std::out_of_range("Memory write out of bounds!");
        }
        memory[address] = value;
        std::cout << "[Memory Write] Address: " << address 
                  << ", Data: " << std::bitset<8>(value) << "\n";
    }

void segmentInfo() {
    std::cout << "=== Memory Segmentation ===\n";
    std::cout << "Code Segment: 0x00 - 0x03\n";
    std::cout << "Data Segment: 0x04 - 0x07\n";
    std::cout << "Stack Segment: 0x08 - 0x0B\n";
    std::cout << "Heap Segment: 0x0C - 0x0F\n";
    std::cout << "===========================\n";
}


private:
    std::vector<uint8_t> memory;
};

#endif
