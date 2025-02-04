#include "Memory.h"

Memory::Memory(int size) : memorySpace(size, 0) {}

int Memory::read(int address) {
    if (address < 0 || address >= memorySpace.size()) {
        std::cout << "Memory read error: Address out of bounds" << std::endl;
        return -1;
    }
    return memorySpace[address];
}

void Memory::write(int address, int value) {
    if (address < 0 || address >= memorySpace.size()) {
        std::cout << "Memory write error: Address out of bounds" << std::endl;
        return;
    }
    std::cout << "Writing value " << value << " to memory address " << address << std::endl;
    memorySpace[address] = value;
}

void Memory::display(std::ostream& outputStream) {
    for (int i = 0; i < memorySpace.size(); ++i) {
        outputStream << "Address " << i << ": " << memorySpace[i] << " ";
    }
    outputStream << std::endl;
}
