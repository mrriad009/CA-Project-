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

1. [Features](#features)
2. [Installation](#installation)
3. [Usage](#usage)
4. [Project Structure](#project-structure)
5. [Components](#components)
   - [ALU](#alu)
   - [Program Counter](#program-counter)
   - [Registers](#registers)
   - [Memory](#memory)
   - [Assembler](#assembler)
6. [License](#license)

---

## Installation

### Prerequisites
- **C++ Compiler** (e.g., GCC, Clang)
- **C++11** or later standard support

### Steps to Install

1. Clone the repository:
    ```bash
    git clone https://github.com/your-username/virtual-cpu-emulator.git
    cd virtual-cpu-emulator
    ```

2. Compile the project:
    ```bash
    g++ main.cpp -o virtual_cpu_emulator -std=c++11
    ```

3. Run the program:
    ```bash
    ./virtual_cpu_emulator
    ```

---

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

---

## Project Structure

```plaintext
/virtual-cpu-emulator
├── main.cpp             # Entry point to the program and CPU simulation
├── include
│   ├── ALU.h            # ALU component definition
│   ├── Assembler.h      # Assembler component definition
│   ├── Memory.h         # Memory component definition
│   ├── ProgramCounter.h # Program Counter component definition
│   └── Register.h       # Register component definition
├── README.md            # This documentation
└── LICENSE              # Project license file
```

## Components

# ALU (Arithmetic Logic Unit)

The **Arithmetic Logic Unit (ALU)** is responsible for performing basic arithmetic operations such as **ADD**, **SUB**, and **MOV**.

---

## Code

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

### **Register.md**


# Register

Registers temporarily store data during the execution of instructions. They are general-purpose storage units used to hold values for computations.

---

## Code

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
- store(int address, int value): Saves the given value at the specified memory address.
- load(int address): Fetches the value from the specified memory address.

## rogram Counter
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
- increment(): Advances the counter to the next instruction address.
- set(int address): Sets the counter to a specific instruction address.
- get(): Retrieves the current value of the program counter.