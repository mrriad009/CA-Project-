How to run the code ( main.cpp) : 

open terminal and go to the folder . 
Execute : 
g++ ALU.cpp Register.cpp ProgramCounter.cpp Memory.cpp Assembler.cpp main.cpp -o cpu_emulator
.\cpu_emulator.exe


```bash
echo "Hello, World!"
```

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


### 1. **ALU (Arithmetic Logic Unit)**

The **ALU** performs basic arithmetic and logical operations. In this program, the ALU handles the operations `ADD`, `SUB`, and `MOV`. It processes the operands and returns the result.

#### Key Code
```cpp
class ALU {
public:
    int execute(const std::string& instruction, int operand1, int operand2);
};
```

Register
The Register stores intermediate results during the program's execution. In this program, we use two registers (regA and regB), which store results from operations and can be updated with new values.