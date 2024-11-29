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

**Key Operations**
- ADD: Adds operand1 and operand2 and returns the result.
- SUB: Subtracts operand2 from operand1 and returns the result.
- MOV: Copies the value of operand1 to the result

**Register**
A Register is a small storage area used to hold data temporarily. The Virtual CPU Emulator uses two general-purpose registers: Register A and Register B. The value in a register can be set using the set method and retrieved with the get method.

```
void Register::set(int v) { 
    value = v;  // Store the value in the register
}

int Register::get() const { 
    return value;  // Retrieve the value from the register
}

```


