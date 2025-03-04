# Virtual CPU Emulator

This project simulates a basic Virtual CPU and demonstrates the **Fetch-Decode-Execute (FDE)** cycle, which is fundamental to CPU operations. It includes core CPU components such as the Arithmetic Logic Unit (ALU), registers, program counter, memory, and an assembler to convert assembly instructions into machine code. The emulator performs basic operations like **ADD**, **SUB**, and **MOV**.

---

## Features

- Simulates a simple CPU with the following components:
  - **ALU:** Performs arithmetic operations.
  - **Program Counter:** Tracks instruction addresses.
  - **Registers:** Store intermediate results.
  - **Memory:** Holds data used by the CPU.
  - **Assembler:** Converts assembly instructions into machine code.
- Supports basic operations:
  - **ADD:** Adds two values.
  - **SUB:** Subtracts one value from another.
  - **MOV:** Transfers a value between components.
- Implements the **Fetch-Decode-Execute (FDE)** cycle for processing instructions.

---

## Table of Contents

- [Virtual CPU Emulator](#virtual-cpu-emulator)
  - [Features](#features)
  - [Table of Contents](#table-of-contents)
  - [Installation](#installation)
    - [Prerequisites](#prerequisites)
  - [Usage](#usage)
  - [Components](#components)
- [ALU (Arithmetic Logic Unit)](#alu-arithmetic-logic-unit)
- [Register](#register)
  - [Memory](#memory)
  - [Program Counter](#program-counter)
  - [Assembler](#assembler)
  - [Compilation and Execution](#compilation-and-execution)
    - [Steps to Run the Code:](#steps-to-run-the-code)

---

## Installation

### Prerequisites
- **C++ Compiler** (e.g., GCC, Clang)
- **C++11** or later standard support


## Usage

Once the program is running, it simulates the execution of assembly-like instructions using the following cycle:

1. **Fetch:** The program counter fetches the next instruction.
2. **Decode:** The instruction is converted into machine code.
3. **Execute:** The ALU performs the specified operation on the operands.

**Outputs include:**
- Memory contents
- Program counter state
- Instruction fetch, decode, and execution results
- Final register values


## Components

# ALU (Arithmetic Logic Unit)

The **Arithmetic Logic Unit (ALU)** is responsible for performing basic arithmetic operations such as **ADD**, **SUB**, and **MOV**.

---

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
Explanation
- execute(const std::string& instruction, int operand1, int operand2):
    - Executes the specified instruction (ADD, SUB, or MOV) on the given operands.
    - Returns the result of the operation.

---


# Register

Registers temporarily store data during the execution of instructions. They are general-purpose storage units used to hold values for computations.

---

```cpp
#ifndef REGISTER_H
#define REGISTER_H

class Register {
private:
    int value;
public:
    Register() : value(0) {}
    void set(int v);
    int get() const;
};

#endif
```
- set(int v): Sets the value of the register to the specified integer v.
- get(): Retrieves the current value stored in the register.

## Memory
The Memory component simulates a small data storage space for the CPU. 
It holds data such as operands and intermediate values used during computations.

```cpp
#ifndef MEMORY_H
#define MEMORY_H

class Memory {
private:
    int memory[4];  // Simulated memory with 4 addresses
public:
    Memory();
    void store(int address, int value);
    int load(int address) const;
};

#endif
```
- **store**(int address, int value): Saves the given value at the specified memory address.
- **load**(int address): Fetches the value from the specified memory address.

## Program Counter

The Program Counter (PC) keeps track of the current instruction address and increments to fetch the next one during the Fetch-Decode-Execute cycle.

```cpp
#ifndef PROGRAMCOUNTER_H
#define PROGRAMCOUNTER_H

class ProgramCounter {
private:
    int counter;
public:
    ProgramCounter() : counter(0) {}
    void increment();
    void set(int address);
    int get() const;
};

#endif
```
- **increment()**: Advances the counter to the next instruction address.
- set(int address): Sets the counter to a specific instruction address.
- get(): Retrieves the current value of the program counter.

## Assembler
The Assembler component converts assembly instructions into machine-readable binary codes.

```cpp
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>
#include <bitset>  // for converting to binary

class Assembler {
public:
    static std::string assemblerToMachineCode(const std::string& instruction);
};

#endif
```
- assemblerToMachineCode(const std::string& instruction): Converts human-readable assembly instructions (ADD, MOV, SUB) into machine-readable binary codes.
    - ADD: 0b00000000
    - SUB: 0b00000001
    - MOV: 0b00000010


## Compilation and Execution

### Steps to Run the Code:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/CA-Project.git
   ```

2. **Navigate to the project directory**:
   ```bash
   cd CA-Project/Weekly Progress/W5
   ```

3. **Compile the code**:
   ```bash
   g++ -o cpu_simulation main.cpp ALU.cpp Assembler.cpp Register.cpp ProgramCounter.cpp
   ```

4. **Run the program**:
   ```bash
   ./cpu_simulation
   ```