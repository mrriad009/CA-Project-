# CPU Simulator Project

This week’s project focuses on implementing a basic CPU simulator that emulates instruction execution with the use of an Arithmetic Logic Unit (ALU), Registers, and Memory management. The CPU simulator fetches and executes machine instructions from memory, performs arithmetic operations, stores values in memory, and outputs the results.

The implementation also includes a basic Assembler that converts assembly code into machine code, simulating the full functionality of a simplified CPU. The project is structured to follow modular programming practices, using separate classes for CPU components to facilitate future extensibility and maintainability.

## Table of Contents
1. [Classes and Functionality](#classes-and-functionality)
2. [Instruction Set](#instruction-set)
3. [Assembler](#assembler)
4. [Execution Flow](#execution-flow)
5. [Input/Output](#inputoutput)
6. [Memory and Register Management](#memory-and-register-management)
7. [Setup and Compilation](#setup-and-compilation)
8. [Known Issues and Future Improvements](#known-issues-and-future-improvements)
9. [Conclusion](#conclusion)

## Classes and Functionality

## 1. ALU (Arithmetic Logic Unit)

The ALU is responsible for performing basic arithmetic and logical operations on operands. Supported operations include:

- **ADD**: Adds two operands.
- **SUB**: Subtracts the second operand from the first.
- **LOAD**: Loads the value from memory to a register.
- **STORE**: Stores the value from a register to memory.

```cpp
class ALU {
public:
    int performOperation(const std::string& opcode, int operand1, int operand2);
};
```cpp
## 2. Registers

The Registers class maintains the state of the CPU’s general-purpose registers (R0, R1, R2, R3). Registers hold values that are used in instructions for arithmetic and memory operations.

```cpp
class Registers {
public:
    std::map<std::string, int> regs;
    Registers();
    int get(const std::string& reg);
    void set(const std::string& reg, int value);
    void display(std::ostream& outputStream);
};

## 3. Memory

The Memory class simulates the system's memory space, providing methods for reading and writing to memory addresses. It stores values used in the STORE and LOAD operations.

```cpp
class Memory {
public:
    std::vector<int> memorySpace;
    Memory(int size);
    int read(int address);
    void write(int address, int value);
    void display(std::ostream& outputStream);
};

## 4. CPU

The CPU class ties everything together, controlling the program counter, instruction fetching, decoding, and execution of instructions. It also handles memory access, register updates, and the ALU operations.

```cpp
class CPU {
public:
    int programCounter;
    std::vector<int> instructionMemory;
    Registers registers;
    ALU alu;
    Memory memory;
    CPU();
    void loadProgram(const std::vector<int>& program);
    void executeProgram(std::ostream& outputStream);
};

## Instruction Set

The CPU supports a basic set of instructions that are encoded into machine code and executed during the simulation. These instructions are:

- **ADD**: Adds two registers and stores the result in the first register.
- **SUB**: Subtracts the second register from the first register and stores the result in the first register.
- **LOAD**: Loads the value from the specified memory address into the register.
- **STORE**: Stores the value from the register into the specified memory address.
- **INPUT**: Takes user input and stores it in the specified register.
- **OUTPUT**: Outputs the value stored in the specified register.
- **JUMP**: Sets the program counter to a specified address.
- **CALL**: Saves the current program counter to memory and jumps to a specified address.
- **RET**: Returns from a subroutine by loading the program counter from memory.

## Assembler

The Assembler class converts assembly instructions into machine code for the CPU. The assembly code consists of opcode and register operands. The assembler translates these into a format that the CPU can execute.


## Assembler Example

For example, the instruction:

``
ADD R0 R1
``
is converted into machine code like this:
```
193
The assembler operates as follows:

cpp
Copy
Edit
std::vector<int> assemble(const std::string& assemblyCode);
The assembler parses each line, converts the opcodes and registers into the corresponding machine code, and returns a list of machine instructions.

Execution Flow
The execution flow of the CPU involves the following steps:

Fetch: The CPU fetches the instruction from memory using the program counter.
Decode: The instruction is decoded into its opcode and operands.
Execute: The appropriate operation is performed using the ALU, and the registers or memory are updated.
Update State: The state of the registers and memory is displayed after each instruction execution.
cpp
Copy
Edit
void CPU::executeProgram(std::ostream& outputStream) {
    while (programCounter < instructionMemory.size()) {
        int instruction = instructionMemory[programCounter];
        outputStream << "Fetching instruction at address " << programCounter << ": " << instruction << std::endl;
        programCounter++;
        decodeAndExecute(instruction, outputStream);
    }
}
Input/Output
Input Handling
The program accepts user input when the INPUT instruction is encountered. For example:

arduino
Copy
Edit
INPUT R0
This will prompt the user to enter a value to be stored in R0.

Output Handling
When the OUTPUT instruction is encountered, the value of the specified register is printed to the console.

File Handling
Input File: The program reads assembly code from the file input.txt.
Output File: The results of the program execution (including memory and register states) are saved to the file output.txt.
Memory and Register Management
The memory space in the CPU simulator is managed using a vector<int> array. Initially, all memory locations are set to 0.

Registers are stored in a map and can be accessed and updated via methods in the Registers class. Each register's value is updated after each instruction execution.

