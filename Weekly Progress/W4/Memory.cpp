#include "Memory.h"
#include <iostream>

Memory::Memory() {
    for (int i = 0; i < 4; i++) {
        memory[i] = 0;  // Initialize memory to 0
    }
}

void Memory::store(int address, int value) {
    memory[address] = value;
}

int Memory::load(int address) const {
    return memory[address];
}
