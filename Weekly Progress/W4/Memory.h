#ifndef MEMORY_H
#define MEMORY_H

class Memory {
private:
    int memory[4];  // Small memory space for simulation
public:
    Memory();
    void store(int address, int value);
    int load(int address) const;
};

#endif
