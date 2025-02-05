# Week 8 Enhancements

## New Operations

The instruction set was expanded to include the following new operations:
- **MUL**: Multiply two registers (MUL R0 R1).
- **DIV**: Divide one register by another (DIV R0 R1), with division-by-zero error handling.
- **CMP**: Compare two registers (CMP R0 R1), setting a flag if they are equal (useful for branching).
- **SHL**: Logical shift left (SHL R0 R1).
- **SHR**: Logical shift right (SHR R0 R1).

## Changes

- The ALU class was updated to handle new operations like multiplication, division, comparison, and shift operations.
- The CPU class was updated to handle these new instructions by decoding and executing them.
- The Assembler class was updated to support the new instructions and convert them into machine code.

### Code Changes

- **ALU** now supports: MUL, DIV, CMP, SHL, and SHR.
- **CPU's** `decodeAndExecute()` method was modified to decode and execute these new operations.
- **Assembler** was modified to include opcodes for the new instructions.

## Enhancements in Instruction Handling

### Week 7 Features

- The CPU decoded and executed basic instructions like ADD, SUB, LOAD, STORE, etc.

### Week 8 Enhancements

- **Advanced Arithmetic**: The CPU can now perform more complex operations, like multiplication and division, which were not supported in Week 7.
- **Comparison**: The CPU can compare registers (CMP) and set flags for branching, which was not previously possible.
- **Shift Operations**: The ability to perform bitwise shifts (SHL and SHR) was added.

### Changes

- The `performOperation` method in ALU was updated to handle the new operations.
- The `decodeAndExecute` method in the CPU class was extended to decode the new instructions and perform the appropriate operations.

### Code Changes

- **CPU.cpp**:
  - Added logic to handle new instructions (MUL, DIV, CMP, SHL, SHR).
  - Updated the `getOpcodeString()` method to return correct instruction names for new opcodes.

## Improved Error Handling

### Week 7 Features

- Basic error handling was present in the form of invalid memory access errors.

### Week 8 Enhancements

- **Division by Zero Error**: In Week 8, division operations (DIV) now check for division by zero, preventing runtime errors and providing error messages.
- **Input Error Handling**: Error messages were added for invalid input scenarios.

### Changes

- In `ALU.cpp`, the DIV operation was modified to check for division by zero before attempting the operation.
- The program now prints a helpful error message when division by zero occurs.

### Code Changes

- **ALU.cpp**:
  - Added error checking in `performOperation` for DIV to handle division by zero gracefully.

## Updated Instruction Set and Assembler

### Week 7 Features

- The assembler supported basic instructions like ADD, SUB, LOAD, STORE, etc.
- Each instruction was converted into machine code by the assembler using an opcode and register addressing scheme.

### Week 8 Enhancements

- Week 8 updated the assembler to support the new instructions (MUL, DIV, CMP, SHL, SHR).
- The opcode mapping was updated in the Assembler class to include the new instructions, allowing them to be parsed from assembly code and converted into machine code.

### Changes

- The assembler now converts MUL, DIV, CMP, SHL, and SHR instructions to their corresponding opcodes in machine code.
- The `Assembler.cpp` file now handles additional operations, expanding the instruction set for the simulator.

### Code Changes

- **Assembler.cpp**:
  - Added new opcodes for the new instructions (MUL, DIV, CMP, SHL, SHR).
  - The assembler parses these instructions from assembly code and converts them to machine code correctly.

## Handling New Instructions in CPU Execution

### Week 7 Features

- The CPU class fetched instructions, decoded them, and executed them based on the instruction set (e.g., ADD, SUB).

### Week 8 Enhancements

- The CPU class was updated to handle new instructions like MUL, DIV, CMP, SHL, and SHR during the fetch-decode-execute cycle.
- The CPU now updates the registers and memory for each new instruction, and handles each operation accordingly.

### Changes

- The `decodeAndExecute` method was modified to include the logic for handling the new instructions (MUL, DIV, CMP, SHL, SHR).
- The register state was updated after each instruction execution.

### Code Changes

- **CPU.cpp**:
  - Updated the `decodeAndExecute` function to handle the new instructions.
  - Extended the logic to perform arithmetic, logical, and comparison operations and update the register values accordingly.

## Updated Main Program (I/O Handling)

### Week 7 Features

- The program reads assembly code from a file (`input.txt`) and writes the output to a file (`output.txt`).
- The execution logic printed the register and memory states after each instruction.

### Week 8 Enhancements

- Division by Zero errors and invalid instructions are handled more gracefully in Week 8.
- The program continues to read from the `input.txt` file and output results to `output.txt`, but now handles more complex operations (e.g., multiplication, shifts).

### Changes

- The `main.cpp` file remains largely the same in terms of structure, but with enhanced error handling and logging of new instructions.

### Code Changes

- **main.cpp**:
  - Slight modifications to handle new instructions and print relevant output after each execution.

## Summary of Key Changes in Week 8

| Feature            | Week 7                              | Week 8                                                                 |
|--------------------|-------------------------------------|-----------------------------------------------------------------------|
| New Instructions   | Basic operations (ADD, SUB, etc.)   | Added new instructions: MUL, DIV, CMP, SHL, SHR                       |
| ALU                | Basic arithmetic operations         | Extended to handle multiplication, division, comparison, shifts       |
| CPU                | Fetch-decode-execute basic ops      | Extended to handle new instructions and comparison                    |
| Assembler          | Converts basic assembly to machine code | Supports new instructions and corresponding opcodes                    |
| Error Handling     | Basic memory access errors          | Added division-by-zero error handling and other validation checks     |
| Control Flow       | N/A                                 | Not yet implemented in Week 8, will be added in future                |
| Execution Flow     | Executes basic instructions         | Handles new instructions, executes them and updates the state         |
| Input/Output       | Read from `input.txt`, output to `output.txt` | Same, but with more detailed logging and error reporting              |
