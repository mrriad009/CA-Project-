#include <iostream>
#include <vector>
#include <stdexcept>

class Memory {
private:
    std::vector<int> dataMemory;
    std::vector<int> stackMemory;
    std::vector<int> heapMemory;

public:
    Memory(int dataSize = 4, int stackSize = 4, int heapSize = 4) {
        dataMemory.resize(dataSize, 0);
        stackMemory.resize(stackSize, 0);
        heapMemory.resize(heapSize, 0);
    }

    void storeData(int address, int value) {
        if (address >= 0 && address < dataMemory.size()) {
            dataMemory[address] = value;
        } else {
            throw std::out_of_range("Data memory address out of bounds");
        }
    }

    int loadData(int address) const {
        if (address >= 0 && address < dataMemory.size()) {
            return dataMemory[address];
        } else {
            throw std::out_of_range("Data memory address out of bounds");
        }
    }

    void storeStack(int address, int value) {
        if (address >= 0 && address < stackMemory.size()) {
            stackMemory[address] = value;
        } else {
            throw std::out_of_range("Stack memory address out of bounds");
        }
    }

    int loadStack(int address) const {
        if (address >= 0 && address < stackMemory.size()) {
            return stackMemory[address];
        } else {
            throw std::out_of_range("Stack memory address out of bounds");
        }
    }

    void storeHeap(int address, int value) {
        if (address >= 0 && address < heapMemory.size()) {
            heapMemory[address] = value;
        } else {
            throw std::out_of_range("Heap memory address out of bounds");
        }
    }

    int loadHeap(int address) const {
        if (address >= 0 && address < heapMemory.size()) {
            return heapMemory[address];
        } else {
            throw std::out_of_range("Heap memory address out of bounds");
        }
    }

    void printMemory() const {
        std::cout << "Data Memory: ";
        for (int i : dataMemory) std::cout << i << " ";
        std::cout << std::endl;

        std::cout << "Stack Memory: ";
        for (int i : stackMemory) std::cout << i << " ";
        std::cout << std::endl;

        std::cout << "Heap Memory: ";
        for (int i : heapMemory) std::cout << i << " ";
        std::cout << std::endl;
    }
};
