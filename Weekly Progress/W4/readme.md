How to run the code ( main.cpp) : 

open terminal and go to the folder . 
Execute : 
g++ ALU.cpp Register.cpp ProgramCounter.cpp Memory.cpp Assembler.cpp main.cpp -o cpu_emulator
.\cpu_emulator.exe


```bash
echo "Hello, World!"


# Virtual CPU Emulator Documentation

This documentation explains the key components of the Virtual CPU Emulator, describing their purpose, functionality, and key code snippets.

## Table of Contents

- [ALU (Arithmetic Logic Unit)](#alu-arithmetic-logic-unit)
- [Register](#register)
- [Program Counter](#program-counter)
- [Memory](#memory)
- [Assembler](#assembler)
- [Main Program](#main-program)

---

## ALU (Arithmetic Logic Unit)

The **ALU** is responsible for performing arithmetic and logical operations. In our emulator, it handles basic operations like `ADD`, `SUB`, and `MOV`. The ALU executes instructions by taking two operands and performing the requested operation.


