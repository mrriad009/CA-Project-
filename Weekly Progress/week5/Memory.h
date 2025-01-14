#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <iostream>
#include <bitset>

class Memory {
public:
    Memory(size_t size) : memory(size, 0b00000000) {}

    uint8_t read(size_t address) {
        if (address >= memory.size()) {
            throw std::out_of_range("Memory read out of bounds!");
        }
        return memory[address];
    }

    void write(size_t address, uint8_t value) {
        if (address >= memory.size()) {
            throw std::out_of_range("Memory write out of bounds!");
        }
        memory[address] = value;
    }

    size_t size() const { // Method to return the memory size
        return memory.size();
    }

    void display() {
        std::cout << "=== Memory Contents ===\n";
        for (size_t i = 0; i < memory.size(); ++i) {
            std::cout << "[" << i << "]: " << std::bitset<8>(memory[i]) << "\n";
        }
        std::cout << "========================\n";
    }

private:
    std::vector<uint8_t> memory;
};

#endif
