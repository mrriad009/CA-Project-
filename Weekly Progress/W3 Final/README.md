
# Week 3: Basic CPU Components

## Objective
This repository contains the implementation of basic CPU components including:
- **Arithmetic Logic Unit (ALU)**
- **General-Purpose Registers**
- **Program Counter (PC)**
- **Assembler for converting assembly instructions to machine code**

These components are the building blocks for simulating a basic CPU. The project includes the interaction of these components to perform basic operations such as addition and subtraction.

## Table of Contents
1. [Introduction](#introduction)
2. [ALU - Arithmetic Logic Unit](#alu-arithmetic-logic-unit)
3. [General-Purpose Registers](#general-purpose-registers)
4. [Program Counter (PC)](#program-counter-pc)
5. [Assembler](#assembler)
6. [Testing and Example Output](#testing-and-example-output)
7. [Compilation and Execution](#compilation-and-execution)
8. [Conclusion](#conclusion)

## Introduction
In Week 3, we have implemented and tested the fundamental components of a CPU. These include the **ALU**, **Registers**, and **Program Counter**. We have also developed an **Assembler** to convert assembly code into machine code (binary values) that can be executed by the CPU. The components are tested together to simulate basic CPU operations.

## ALU - Arithmetic Logic Unit
The **ALU** performs arithmetic and logical operations. In this project, it handles the **addition** and **subtraction** operations on data stored in registers.

### ALU Code
```cpp
// ALU.h
#ifndef ALU_H
#define ALU_H

class ALU {
public:
    int add(int operand1, int operand2);
    int sub(int operand1, int operand2);
};

#endif
```
Purpose: This header file declares the ALU class, which contains two member functions: add and sub. These functions perform basic arithmetic operations between two integers.
Functions:
add: Takes two integer arguments (a and b), returns their sum.
sub: Takes two integer arguments (a and b), returns their difference.

```cpp
// ALU.cpp
#include "ALU.h"

int ALU::add(int operand1, int operand2) {
    return operand1 + operand2;
}

int ALU::sub(int operand1, int operand2) {
    return operand1 - operand2;
}
```
Purpose: This file implements the functions declared in ALU.h. It defines how the add and sub operations are carried out.
Logic:
The add function returns the result of adding two integers.
The sub function returns the result of subtracting one integer from another.

## General-Purpose Registers
General-purpose registers temporarily store data during CPU operations. In this project, two registers `R1` and `R2` are used.

### Register Code
```cpp
// Register.h
#ifndef REGISTER_H
#define REGISTER_H

class Register {
private:
    int value;
public:
    void set(int v);
    int get() const;
};

#endif
```
Purpose: This header file declares the Register class, which has a value member to store the register's value and functions to set and retrieve the value.
Functions:
set: Sets the register's value to the specified integer v.
get: Returns the current value stored in the register.

```cpp
// Register.cpp
#include "Register.h"

void Register::set(int v) {
    value = v;
}

int Register::get() const {
    return value;
}
```
Purpose: This file implements the set and get functions for the Register class.
Logic:
The set function updates the register's value.
The get function simply returns the value stored in the register.

## Program Counter (PC)
The **Program Counter** keeps track of the address of the current instruction and increments after each operation to point to the next instruction.

### Program Counter Code
```cpp
// ProgramCounter.h
#ifndef PROGRAMCOUNTER_H
#define PROGRAMCOUNTER_H

class ProgramCounter {
private:
    int value;
public:
    void set(int v);
    int get() const;
    void increment();
};

#endif
```
Purpose: The header file defines the ProgramCounter class, which includes methods to increment, set, and get the current PC value.
Functions:
increment: Increments the PC by 1 to point to the next instruction.
set: Sets the PC to a specific address.
get: Returns the current value of the PC.

```cpp
// ProgramCounter.cpp
#include "ProgramCounter.h"

void ProgramCounter::set(int v) {
    value = v;
}

int ProgramCounter::get() const {
    return value;
}

void ProgramCounter::increment() {
    value++;
}
```
Purpose: This file implements the functions declared in ProgramCounter.h.
Logic:
The increment function increases the PC by 1, advancing the program flow.
- The set function sets the PC to a given address.
- The get function returns the current value of the PC.

## Assembler
The **Assembler** converts assembly instructions (like `ADD` and `SUB`) into machine code (binary format) that can be executed by the CPU.

### Assembler Code
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
Purpose: This header file declares the Assembler class, which includes a static method assemblerToMachineCode that converts assembler instructions into machine code.
Functions:
assemblerToMachineCode: Converts an assembler instruction (e.g., ADD, SUB) into a binary machine code.

```cpp
// Assembler.cpp
#include "Assembler.h"
#include <bitset>

std::string Assembler::assemblerToMachineCode(const std::string& instruction) {
    if (instruction == "ADD") {
        return std::bitset<8>(0b00000000).to_string();  // Machine code for ADD
    } else if (instruction == "SUB") {
        return std::bitset<8>(0b00000001).to_string();  // Machine code for SUB
    } else {
        return "Unknown";
    }
}
```
Purpose: This file implements the assemblerToMachineCode function, which returns the 4-bit binary representation of an assembler instruction.
Logic:
- For the ADD instruction, the machine code 0000 is returned.
- For the SUB instruction, the machine code 0001 is returned.
- If an unsupported instruction is passed, it returns "Unknown".

## Main Program :

Purpose: This file demonstrates how all components (ALU, Registers, ProgramCounter, and Assembler) work together. It initializes the registers, performs arithmetic operations, and displays the results in both decimal and binary formats.
Summary:
Each component is designed to perform a specific function within the Virtual CPU Emulator project:

- ALU performs basic arithmetic operations.
- Registers store temporary data for the CPU.
- ProgramCounter tracks the execution flow.
- Assembler translates assembler instructions into machine code.


## Testing and Example Output

Here is a sample output showing the interaction between the components:

```
Initial Register Values:
R1: 42 (00101010)
R2: 84 (01010100)
-------------------------
Program Counter (PC) Initial Value: 0 (00000000)
-------------------------

Testing with Program Counter interacting with Assembler Instructions:
Assembler: ADD -> Machine Code: 00000000 (00000000)
PC = 0 (00000000): ADD
ADD R1, R2 -> Result = 126 (01111110)
Assembler: SUB -> Machine Code: 00000001 (00000001)
PC = 1 (00000001): SUB
SUB R1, R2 -> Result = -42 (11111110)

Final Register Values:
R1: 42 (00101010)
R2: 84 (01010100)

Final Program Counter: 2 (00000010)
```

## Compilation and Execution

### Steps to Run the Code:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/CA-Project.git
   ```

2. **Navigate to the project directory**:
   ```bash
   cd CA-Project/Week3
   ```

3. **Compile the code**:
   ```bash
   g++ -o cpu_simulation main.cpp ALU.cpp Assembler.cpp Register.cpp ProgramCounter.cpp
   ```

4. **Run the program**:
   ```bash
   ./cpu_simulation
   ```

This will execute the CPU simulation, displaying the result of arithmetic operations performed by the ALU on values stored in registers.

## Conclusion
In Week 3, we implemented the basic components of a CPU:
- **ALU** for arithmetic operations
- **Registers** for temporary data storage
- **Program Counter** to track instructions
- **Assembler** to convert assembly code to machine-readable binary

These components work together to simulate basic CPU operations and help understand how a real CPU handles instructions and executes operations.

---

### License

