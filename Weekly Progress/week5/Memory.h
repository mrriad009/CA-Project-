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
        size_t segmentSize = memory.size() / 4; // Dividing memory into 4 segments
        std::cout << "=== Memory Segmentation ===\n";
        std::cout << "Code Segment: 0 - " << segmentSize - 1 << "\n";
        std::cout << "Data Segment: " << segmentSize << " - " << (2 * segmentSize) - 1 << "\n";
        std::cout << "Stack Segment: " << (2 * segmentSize) << " - " << (3 * segmentSize) - 1 << "\n";
        std::cout << "Heap Segment: " << (3 * segmentSize) << " - " << memory.size() - 1 << "\n";
        std::cout << "===========================\n";
    }

private:
    std::vector<uint8_t> memory;
};

#endif
