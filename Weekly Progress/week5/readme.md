```cpp

#include "Memory.h"
#include <iostream>
#include <bitset>

Memory::Memory() {
    // Initialize memory segments with predefined binary values
    dataMemory[0] = std::bitset<8>(10);  // 10 in binary: 00001010
    dataMemory[1] = std::bitset<8>(20);  // 20 in binary: 00010100
    dataMemory[2] = std::bitset<8>(30);  // 30 in binary: 00011110
    dataMemory[3] = std::bitset<8>(40);  // 40 in binary: 00101000

    stackMemory[0] = std::bitset<8>(5);  // 5 in binary: 00000101
    stackMemory[1] = std::bitset<8>(15); // 15 in binary: 00001111
    stackMemory[2] = std::bitset<8>(25); // 25 in binary: 00011001
    stackMemory[3] = std::bitset<8>(35); // 35 in binary: 00100011

    heapMemory[0] = std::bitset<8>(50);  // 50 in binary: 00110010
    heapMemory[1] = std::bitset<8>(60);  // 60 in binary: 00111100
    heapMemory[2] = std::bitset<8>(70);  // 70 in binary: 01000110
    heapMemory[3] = std::bitset<8>(80);  // 80 in binary: 01010000
}

// Store a binary value in the specified segment
void Memory::store(int address, const std::bitset<8>& value, const std::string& segment) {
    if (segment == "data") {
        dataMemory[address] = value;
    } else if (segment == "stack") {
        stackMemory[address] = value;
    } else if (segment == "heap") {
        heapMemory[address] = value;
    } else {
        std::cerr << "Error: Invalid memory segment." << std::endl;
    }
}

// Load a binary value from the specified segment
std::bitset<8> Memory::load(int address, const std::string& segment) const {
    if (segment == "data") {
        return dataMemory[address];
    } else if (segment == "stack") {
        return stackMemory[address];
    } else if (segment == "heap") {
        return heapMemory[address];
    } else {
        std::cerr << "Error: Invalid memory segment." << std::endl;
        return std::bitset<8>(0); // Return zero if segment is invalid
    }
}

// Optional: Print the binary representation of all memory contents for debugging
void Memory::printMemoryContents() const {
    std::cout << "Data Memory:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << "Address " << i << ": " << dataMemory[i] << std::endl;
    }

    std::cout << "Stack Memory:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << "Address " << i << ": " << stackMemory[i] << std::endl;
    }

    std::cout << "Heap Memory:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << "Address " << i << ": " << heapMemory[i] << std::endl;
    }
}


```



Explanation:
Memory Class:

The Memory class contains three memory segments: dataMemory, stackMemory, and heapMemory. Each segment is represented by an array of std::bitset<8>, which stores 8-bit binary values. These represent memory addresses holding values in binary format.
The constructor initializes the memory segments with some predefined values (converted to binary using std::bitset).
Store and Load Functions:

store(int address, const std::bitset<8>& value, const std::string& segment):
Stores the binary value at the specified address in the given memory segment.
The segment can be "data", "stack", or "heap".
load(int address, const std::string& segment):
Loads the binary value from the specified address in the given segment and returns it as a std::bitset<8>.
Print Memory Contents (Optional Debugging):

printMemoryContents() prints out the contents of all three memory segments (data, stack, heap), showing the binary values stored at each address.



















Explanation:
Memory Initialization:
We store data in the data segment, stack segment, and heap segment.
Memory Operations:
The program loads operands from the data segment for the instructions and executes them using the ALU.
Memory Display:
The memory.printMemory() function is used to display the contents of all memory segments at the beginning of the program.

## Sample Output 
```
Data Memory: 10 20 0 0 
Stack Memory: 5 0 0 0 
Heap Memory: 15 0 0 0 

----------------------------
Starting Fetch-Decode-Execute Cycle...
----------------------------
Instruction: ADD (Machine Code: 00000000)
CPU Understands: Opcode (binary): 00000000 Operand1: 00001010 Operand2: 00010100
ALU: ADD 10 20 = 30 (Binary: 00011110)
Register A: Set value to 30 (Binary: 00011110)

Instruction: SUB (Machine Code: 00000001)
CPU Understands: Opcode (binary): 00000001 Operand1: 00010100 Operand2: 00000000
ALU: SUB 20 0 = 20 (Binary: 00010100)
Register A: Set value to 20 (Binary: 00010100)

MOV Operation: Register A value 20 moved to Register B.
Register B: Set value to 20 (Binary: 00010100)

Final Register A: 20 (Binary: 00010100)
Final Register B: 20 (Binary: 00010100)

Terminating program...
````
