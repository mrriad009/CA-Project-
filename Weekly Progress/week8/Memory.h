#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <iostream>

class Memory {
public:
    std::vector<int> memorySpace;

    Memory(int size);
    int read(int address);
    void write(int address, int value);
    void display(std::ostream& outputStream);
};

#endif // MEMORY_H
