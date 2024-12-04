
# Week 4 - Virtual CPU Emulator Project

This week we focused on implementing core components of a Virtual CPU Emulator. The project simulates a simple CPU with basic functionality such as arithmetic and logic operations, memory manipulation, and instruction execution. The components developed in this week include:

## Components Implemented

### 1. **ALU (Arithmetic Logic Unit)**

The ALU is responsible for executing arithmetic and logic operations. In this week, the ALU performs basic operations:
- **ADD**: Adds two operands.
- **SUB**: Subtracts the second operand from the first operand.
- **MOV**: Moves data between registers.

The ALU handles the execution of instructions by taking in two operands, executing the corresponding operation, and returning the result.

### 2. **REGISTER**

The Register component holds the value of data during the execution of the program. There are two registers implemented:
- **regA**: Used to store results of arithmetic operations.
- **regB**: Used to store data during the `MOV` operation.

The Register allows reading and writing of values via the `set()` and `get()` methods.

### 3. **MEMORY**

The Memory component simulates a small block of memory with 4 slots. This memory is used to store data that will be used by the CPU for operations.

- **store(address, value)**: Stores the value at a specific memory address.
- **load(address)**: Retrieves the value from a specific memory address.

### 4. **PROGRAM COUNTER**

The Program Counter (PC) keeps track of the current instruction to be executed. It is incremented with each instruction cycle, ensuring the next instruction is executed in sequence.

- **increment()**: Increments the Program Counter to the next instruction.
- **set(address)**: Sets the Program Counter to a specific address.
- **get()**: Returns the current value of the Program Counter.

### 5. **ASSEMBLER**

The Assembler component converts high-level assembly instructions into machine-readable binary opcodes.

- **assemblerToMachineCode(instruction)**: Converts an assembler instruction (`ADD`, `SUB`, `MOV`) into an 8-bit binary opcode.

### 6. **main.cpp**

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

This week we have laid the foundation for our Virtual CPU Emulator project by implementing key components such as the ALU, Register, Memory, Program Counter, and Assembler. We are now able to simulate basic CPU operations like addition, subtraction, and moving data between registers.

