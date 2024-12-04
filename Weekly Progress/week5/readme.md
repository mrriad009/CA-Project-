# week5

This project simulates a basic CPU with components like memory management, an Arithmetic Logic Unit (ALU), registers, a program counter (PC), and an assembler to convert assembly instructions into machine code. It implements a simple fetch-decode-execute cycle to simulate how a CPU would execute instructions.


### 1. **ALU (Arithmetic Logic Unit)**

The ALU is responsible for performing arithmetic and logic operations, such as addition, subtraction, and moving values between registers.

#### ALU Header (`ALU.h`)

The `ALU` class provides an `execute()` function to perform different arithmetic and logic operations based on the instruction passed.

```cpp
#ifndef ALU_H
#define ALU_H

#include <string>

class ALU {
public:
    int execute(const std::string& instruction, int operand1, int operand2);
};

#endif
```
**ALU Implementation (ALU.cpp)**
The execute() method performs different operations based on the instruction. If the instruction is "MOV", it moves the value of operand1 into the result. If the instruction is "ADD", it adds operand1 and operand2. For "SUB", it subtracts operand2 from operand1
```cpp
#include "ALU.h"

int ALU::execute(const std::string& instruction, int operand1, int operand2) {
    int result = 0;

    if (instruction == "MOV") {
        result = operand1;  // Move operation
    } else if (instruction == "ADD") {
        result = operand1 + operand2;  // Addition
    } else if (instruction == "SUB") {
        result = operand1 - operand2;  // Subtraction
    }

    return result;
}
```
## Register
A register is a small, fast storage location within the CPU. In this project, two registers (regA and regB) are used to store data for operations.

Register Header (Register.h)
The Register class defines a register with a private variable value and provides methods to set and get this value.

```cpp
#ifndef REGISTER_H
#define REGISTER_H

class Register {
private:
    int value;  // Stores the value in the register
public:
    Register() : value(0) {}  // Constructor initializes the register value to 0
    void set(int v);          // Sets the value of the register
    int get() const;          // Gets the value of the register
};

#endif
```
Register Implementation (Register.cpp)
The set() function assigns a value to the register, and get() retrieves the current value stored in the register.
```cpp
#include "Register.h"

void Register::set(int v) {
    value = v;  // Assign value to register
}

int Register::get() const {
    return value;  // Return the current value of the register
}
```

## Program Counter (PC)
The Program Counter (PC) keeps track of the address of the next instruction to be fetched from memory. After each instruction is executed, it is incremented to point to the next instruction.

```cpp
#ifndef PROGRAMCOUNTER_H
#define PROGRAMCOUNTER_H

class ProgramCounter {
private:
    int counter;  // Stores the current program counter address
public:
    ProgramCounter() : counter(0) {}  // Initialize counter to 0
    void increment();  // Increment the counter to point to the next instruction
    void set(int address);  // Set the counter to a specific address
    int get() const;  // Get the current value of the counter
};

#endif

```
## Program Counter Implementation (ProgramCounter.cpp)
The increment() function increases the value of the program counter, while set() assigns a specific address to the counter. The get() function retrieves the current counter value.
```cpp
#include "ProgramCounter.h"

void ProgramCounter::increment() {
    counter++;  // Increment the counter to point to the next instruction
}

void ProgramCounter::set(int address) {
    counter = address;  // Set the counter to a specific address
}

int ProgramCounter::get() const {
    return counter;  // Get the current counter value
}
```
## Memory
The Memory class simulates a memory structure with three segments: data, stack, and heap. It supports storing and loading data in these segments.
```cpp
#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <vector>
#include <stdexcept>  // For handling exceptions

class Memory {
private:
    std::vector<int> dataMemory;  // Data segment
    std::vector<int> stackMemory; // Stack segment
    std::vector<int> heapMemory;  // Heap segment

public:
    Memory(int dataSize = 4, int stackSize = 4, int heapSize = 4);
    void storeData(int address, int value);  // Store data at a given address
    int loadData(int address) const;  // Load data from a given address
    
    void storeStack(int address, int value);  // Store stack value
    int loadStack(int address) const;  // Load stack value
    
    void storeHeap(int address, int value);  // Store heap value
    int loadHeap(int address) const;  // Load heap value
    
    void printMemory() const;  // Print all memory contents
};

#endif
```
## Memory Implementation (Memory.cpp)
The storeData(), loadData(), storeStack(), loadStack(), storeHeap(), and loadHeap() methods handle storing and retrieving data from their respective segments. printMemory() displays all memory contents for debugging purposes.
```cpp
#include "Memory.h"

Memory::Memory(int dataSize, int stackSize, int heapSize) {
    dataMemory.resize(dataSize, 0);  // Initialize data memory with zeros
    stackMemory.resize(stackSize, 0);  // Initialize stack memory with zeros
    heapMemory.resize(heapSize, 0);  // Initialize heap memory with zeros
}

void Memory::storeData(int address, int value) {
    if (address >= 0 && address < dataMemory.size()) {
        dataMemory[address] = value;  // Store data at the given address
    } else {
        throw std::out_of_range("Data memory address out of bounds");
    }
}

int Memory::loadData(int address) const {
    if (address >= 0 && address < dataMemory.size()) {
        return dataMemory[address];  // Return value stored at the address
    } else {
        throw std::out_of_range("Data memory address out of bounds");
    }
}

// Similar functions for stackMemory and heapMemory

void Memory::printMemory() const {
    // Print memory contents
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
```
## Assembler
The Assembler converts assembly language instructions into machine code (binary). This project uses a simple method that converts a few predefined instructions (MOV, ADD, SUB) into binary opcodes.

```cpp
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>
#include <bitset>  // For converting to binary

class Assembler {
public:
    static std::string assemblerToMachineCode(const std::string& instruction);
};

#endif
```
## Assembler Implementation (Assembler.cpp)
The assemblerToMachineCode() method converts a simple assembly instruction into its corresponding binary opcode.

```cpp
#include "Assembler.h"

std::string Assembler::assemblerToMachineCode(const std::string& instruction) {
    if (instruction == "MOV") {
        return std::bitset<8>(0b00000010).to_string();  // MOV opcode: 0b00000010
    } else if (instruction == "ADD") {
        return std::bitset<8>(0b00000000).to_string();  // ADD opcode: 0b00000000
    } else if (instruction == "SUB") {
        return std::bitset<8>(0b00000001).to_string();  // SUB opcode: 0b00000001
    } else {
        return "Unknown";  // For any undefined instructions
    }
}
```
main program :

- Initialize Components:
    At the start, we initialize the following components of the CPU simulator:
    ```
    ALU alu;
    Register regA, regB;
    ProgramCounter pc;
    Memory memory;
    ```
- Store Initial Data in Memory
    -The memory segments are initialized with specific values:
```cpp
memory.storeData(0, 10);  // Data Segment: Store value 10 at address 0
memory.storeData(1, 20);  // Data Segment: Store value 20 at address 1
memory.storeStack(0, 5);  // Stack Segment: Store value 5 at address 0
memory.storeHeap(0, 15);  // Heap Segment: Store value 15 at address 0
```
This simulates loading some values into the data, stack, and heap memory segments. These values will be used later when fetching and decoding instructions

The printMemory() method displays the current state of all memory segments (data, stack, and heap). It helps verify that the memory is correctly initialized.

- Start the Fetch-Decode-Execute Cycle
The program begins the core CPU simulation loop:
```cpp
vector<string> instructions = {"ADD", "SUB", "MOV"};
vector<int> operands1 = {0, 1, 2};
vector<int> operands2 = {1, 2, 3};
```
 - The instructions vector holds the instructions to be executed: "ADD", "SUB", and "MOV".
 - The operands1 and operands2 vectors contain the memory addresses that will be used as operands for the instructions.


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
