
# Week 4: Advanced CPU Components and Instruction Set

## Objective
In Week 4, we have extended the implementation of the CPU Emulator by adding more advanced components such as:
- **Memory** for storing and retrieving data.
- **Control Unit** for managing the flow of execution.
- **Instruction Set Architecture (ISA)** for defining CPU instructions.
- **Assembler** for handling a broader set of instructions.
These components interact to simulate a more complex CPU, capable of handling more diverse operations.

## Table of Contents
1. [Introduction](#introduction)
2. [Memory](#memory)
3. [Control Unit](#control-unit)
4. [Instruction Set Architecture (ISA)](#instruction-set-architecture-isa)
5. [Assembler](#assembler)
6. [Testing and Example Output](#testing-and-example-output)
7. [Compilation and Execution](#compilation-and-execution)
8. [Conclusion](#conclusion)

## Introduction
In Week 4, we expanded the virtual CPU by adding memory, a control unit, and an expanded instruction set. The components work together to handle more complex operations such as memory access and control flow management. The new **Assembler** can now convert a wider range of assembly instructions into machine code.

## Memory
The **Memory** component stores data that the CPU can read from and write to. It uses an array to simulate a simple memory system.

### Memory Code
```cpp
// Memory.h
#ifndef MEMORY_H
#define MEMORY_H

class Memory {
private:
    int memory[4];  // Array to simulate memory
public:
    void store(int address, int value);
    int load(int address) const;
};

#endif
```

Purpose: The header file declares the Memory class, which uses an array to simulate memory storage. It provides methods to store and load values.

```cpp
// Memory.cpp
#include "Memory.h"

void Memory::store(int address, int value) {
    memory[address] = value;
}

int Memory::load(int address) const {
    return memory[address];
}
```

Purpose: This file implements the methods to store and load values in memory.

## Control Unit
The **Control Unit (CU)** is responsible for directing the operations of the CPU, managing data flow, and controlling the timing of execution.

### Control Unit Code
```cpp
// ControlUnit.h
#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

class ControlUnit {
public:
    void fetchInstruction(int& pc, Memory& memory);
    void executeInstruction(int opcode, ALU& alu, Register& reg1, Register& reg2);
};

#endif
```

Purpose: This header file declares the ControlUnit class, which controls the flow of the program by fetching instructions and executing them.

```cpp
// ControlUnit.cpp
#include "ControlUnit.h"

void ControlUnit::fetchInstruction(int& pc, Memory& memory) {
    // Fetch instruction from memory based on program counter (PC)
    int instruction = memory.load(pc);
    pc++;
}

void ControlUnit::executeInstruction(int opcode, ALU& alu, Register& reg1, Register& reg2) {
    if (opcode == 0) {  // ADD operation
        reg1.set(alu.add(reg1.get(), reg2.get()));
    } else if (opcode == 1) {  // SUB operation
        reg1.set(alu.sub(reg1.get(), reg2.get()));
    }
}
```

Purpose: This file implements the functions for fetching and executing instructions. It executes operations based on the opcode (machine code).

## Instruction Set Architecture (ISA)
The **ISA** defines the set of instructions that the CPU can understand and execute. In this project, the ISA includes instructions like ADD, SUB, MOV, and more.

### ISA Code
```cpp
// ISA.h
#ifndef ISA_H
#define ISA_H

class ISA {
public:
    static int getOpcode(const std::string& instruction);
};

#endif
```

Purpose: The ISA class is responsible for converting human-readable instructions into opcodes that the CPU can understand.

```cpp
// ISA.cpp
#include "ISA.h"

int ISA::getOpcode(const std::string& instruction) {
    if (instruction == "ADD") {
        return 0;  // Opcode for ADD
    } else if (instruction == "SUB") {
        return 1;  // Opcode for SUB
    } else if (instruction == "MOV") {
        return 2;  // Opcode for MOV
    } else {
        return -1;  // Unknown instruction
    }
}
```

Purpose: This file maps assembly instructions to corresponding opcodes.

## Assembler
The **Assembler** now supports more instructions and translates them into machine code. It handles instructions like ADD, SUB, and MOV.

### Updated Assembler Code
```cpp
// Assembler.h
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>

class Assembler {
public:
    static std::string assemblerToMachineCode(const std::string& instruction);
};

#endif
```

Purpose: The Assembler class includes a static method `assemblerToMachineCode` to convert assembly code into binary.

```cpp
// Assembler.cpp
#include "Assembler.h"
#include <bitset>

std::string Assembler::assemblerToMachineCode(const std::string& instruction) {
    if (instruction == "ADD") {
        return std::bitset<8>(0b00000000).to_string();  // ADD opcode
    } else if (instruction == "SUB") {
        return std::bitset<8>(0b00000001).to_string();  // SUB opcode
    } else if (instruction == "MOV") {
        return std::bitset<8>(0b00000010).to_string();  // MOV opcode
    } else {
        return "Unknown";
    }
}
```

Purpose: This file implements the assemblerToMachineCode method, which converts assembly code into binary machine code.

## Main Program
The main program integrates all components:
- Memory for data storage
- Control Unit for managing execution flow
- ALU for performing arithmetic operations
- ISA and Assembler for instruction decoding and translation

### Main Program Code
```cpp
#include "ALU.h"
#include "Memory.h"
#include "ControlUnit.h"
#include "ISA.h"
#include "Assembler.h"
#include "Register.h"
#include "ProgramCounter.h"

int main() {
    // Initialize components
    ALU alu;
    Memory memory;
    ControlUnit controlUnit;
    Register reg1, reg2;
    ProgramCounter pc;
    
    // Load instructions into memory (simulated)
    memory.store(0, 0);  // ADD instruction
    memory.store(1, 1);  // SUB instruction

    // Set initial register values
    reg1.set(42);
    reg2.set(84);

    // Execute instructions
    pc.set(0);
    controlUnit.fetchInstruction(pc.get(), memory);
    controlUnit.executeInstruction(memory.load(pc.get()), alu, reg1, reg2);

    // Output final register values
    std::cout << "Final Register Values:" << std::endl;
    std::cout << "R1: " << reg1.get() << std::endl;
    std::cout << "R2: " << reg2.get() << std::endl;
    return 0;
}
```

Purpose: The main program demonstrates how to use the components together to simulate a basic CPU.

## Testing and Example Output
Here is a sample output showing the interaction between the components:

```
Memory: Stored value 10 at address 0
Memory: Stored value 20 at address 1
Memory: Stored value 11 at address 2
Memory: Stored value -1 at address 3
----------------------------
Starting Fetch-Decode-Execute Cycle...
----------------------------

Memory: Loaded value 10 from address 0
Program Counter: Incremented to 1 (Machine Code: 0001)
Instruction: ADD (Machine Code: 00000000)
CPU Understands: Opcode (binary): 00000000 Operand1: 1010 Operand2: 0100
ALU: ADD 10 20 = 30 (Binary: 1110)
Register A: Set value to 30 (Binary: 1110)

Memory: Loaded value 20 from address 1
Program Counter: Incremented to 2 (Machine Code: 0010)
Instruction: SUB (Machine Code: 00000001)
CPU Understands: Opcode (binary): 00000001 Operand1: 0100 Operand2: 1011
ALU: SUB 20 11 = 9 (Binary: 1001)
Register A: Set value to 9 (Binary: 1001)

MOV Operation: Register A value 9 moved to Register B.
Register B: Set value to 9 (Binary: 1001)

Final Register A: 9 (Binary: 1001)
Final Register B: 9 (Binary: 1001)
Terminating program...
```

## Compilation and Execution

### Steps to Run the Code:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/CA-Project.git
   ```

2. **Navigate to the project directory**:
   ```bash
   cd CA-Project/Weekly Progress/W4
   ```

3. **Compile the code**:
   ```bash
   g++ ALU.cpp Register.cpp ProgramCounter.cpp Memory.cpp Assembler.cpp main.cpp -o cpu_emulator
   ```

4. **Run the program**:
   ```bash
   .\cpu_emulator.exe
   ```

This will execute the CPU simulation, displaying the result of operations performed by the ALU on values stored in registers.


The main program coordinates the fetch-decode-execute cycle:
1. It loads initial values into memory.
2. It fetches the instructions (`ADD`, `SUB`, `MOV`) and decodes them into binary opcodes.
3. Executes the instructions by interacting with the ALU, Registers, Program Counter, and Memory.
4. Outputs the results of each instruction cycle, including the values in memory and the register contents.

The program simulates basic arithmetic operations and data transfer between registers.

## How to Run

1. Ensure that all the necessary files are in the same directory.
2. Compile the project using your preferred C++ compiler.
3. Run the executable to simulate the Virtual CPU operations.

## Files Included

- **ALU.h**: Header file for ALU.
- **ALU.cpp**: Implementation of ALU functionality.
- **Register.h**: Header file for Register.
- **Register.cpp**: Implementation of Register functionality.
- **ProgramCounter.h**: Header file for Program Counter.
- **ProgramCounter.cpp**: Implementation of Program Counter functionality.
- **Memory.h**: Header file for Memory.
- **Memory.cpp**: Implementation of Memory functionality.
- **Assembler.h**: Header file for Assembler.
- **Assembler.cpp**: Implementation of Assembler functionality.
- **main.cpp**: Main program that runs the Virtual CPU Emulator.

## Conclusion
In Week 4, we extended the CPU Emulator by adding:
- **Memory** for storing and retrieving data
- **Control Unit** for managing execution flow
- **ISA** for defining CPU instructions
- **Assembler** for handling a broader set of instructions

These components work together to simulate a more complete CPU capable of handling a wider range of operations.
