# Virtual CPU Emulator Documentation

This document provides an in-depth overview of the components and operations of a Virtual CPU Emulator. Each component is essential to the proper functioning of the CPU, including memory management, instruction execution, and arithmetic operations.

---

## **Overview**
The Virtual CPU Emulator simulates the operation of a simplified CPU, executing assembly-level instructions and demonstrating the fetch-decode-execute cycle.

### **Key Features**:
- Supports instructions: `ADD`, `SUB`, `LOAD`, `STORE`.
- Memory management with segmentation.
- Real-time display of execution and register states.
- Translates assembly instructions into machine code.

---

## **Components**

### **1. ALU (`ALU.h`)**
The Arithmetic Logic Unit performs arithmetic and logical operations.
#### **Supported Operations**:
- `ADD`: Adds two operands.
- `SUB`: Subtracts the second operand from the first.
- `LOAD`: Directly assigns a value to a register from memory.
- `STORE`: Stores the value of a register into memory.

#### **Code Snippet**:
```cpp
uint8_t performOperation(const std::string& opcode, uint8_t operand1, uint8_t operand2) {
    if (opcode == "ADD") return operand1 + operand2;
    if (opcode == "SUB") return operand1 - operand2;
    if (opcode == "LOAD") return operand2;
    if (opcode == "STORE") return operand1;
    return 0; // Default for unknown instructions
}
```

---

### **2. CPU (`CPU.h`)**
The central processing unit manages instruction execution, integrating ALU, registers, and memory.
#### **Responsibilities**:
- **Instruction Fetch**: Reads the next instruction from memory.
- **Instruction Decode**: Splits instructions into opcode, source, and destination.
- **Instruction Execute**: Uses the ALU and memory to perform operations.

#### **Key Methods**:
- `fetch()`: Retrieves instructions from memory.
- `decode()`: Breaks down instructions into components.
- `execute()`: Executes instructions and updates states.

---

### **3. Registers (`Registers.h`)**
Simulates general-purpose registers for temporary storage.
#### **Features**:
- Storage of 8-bit values.
- Display of current register values.

#### **Initial Values**:
| Register | Initial Value |
|----------|---------------|
| `R0`     | `0x00`        |
| `R1`     | `0x04`        |
| `R2`     | `0x09`        |
| `R3`     | `0x0A`        |

---

### **4. Memory (`Memory.h`)**
Simulates memory with segmentation for different sections:
#### **Segments**:
- **Code**: Stores instructions.
- **Data**: Stores program variables.
- **Stack**: Temporary data.
- **Heap**: Dynamically allocated memory.

#### **Operations**:
- `read(address)`: Reads an 8-bit value from memory.
- `write(address, value)`: Writes an 8-bit value to memory.

---

### **5. Assembler (`Assembler.h`)**
Translates assembly language into binary machine code.
#### **Instruction Format**:
| Bit(s) | Description           |
|--------|-----------------------|
| 7-6    | Opcode                |
| 5-3    | Source Register Index |
| 2-0    | Destination Register  |

#### **Example**:
```assembly
ADD R1 R2
```
Converts to binary:
```
0b00000110
```

---

## **How It Works**

### **Execution Process**:
1. **Input Assembly Code**: The user inputs assembly instructions.
2. **Translation**: The assembler converts the instructions into machine code.
3. **Execution**: The CPU fetches, decodes, and executes each instruction sequentially.

### **Supported Instructions**:
| Instruction | Opcode | Description                              |
|-------------|--------|------------------------------------------|
| `ADD`       | `00`   | Add values from two registers.           |
| `SUB`       | `01`   | Subtract second register from the first. |
| `LOAD`      | `10`   | Load value from memory into a register.  |
| `STORE`     | `11`   | Store value from a register into memory. |

---

## **Usage Instructions**

1. Compile the program using a C++ compiler.
   ```bash
   g++ main.cpp -o VirtualCPU
   ```

2. Run the executable.
   ```bash
   ./VirtualCPU
   ```

3. Enter assembly instructions as input, ending with an empty line.
   ```plaintext
   LOAD R1 R2
   ADD R1 R3
   STORE R1 R2
   ```

4. Observe the output:
   - Machine code.
   - Register and memory states.
   - Execution progress.

---

## **Example Run**
### Input:
```assembly
LOAD R1 R2
ADD R1 R3
STORE R1 R2
```

### Output:
```plaintext
[Input Assembly Code]:
LOAD R1 R2
ADD R1 R3
STORE R1 R2

[Assembling Code...]
[Generated Machine Code]:
10000110 00000111 11000110 

[Loading Program into Memory]

=== Starting Program Execution ===

--- Fetch-Decode-Execute Cycle ---
[Fetch] Instruction: 10000110
[Decode] Opcode: 10, Reg1: R1, Reg2: R2
[Execute] LOAD R1, R2 => Updated R1: 00001001
...
```

---

## **Contributing**
Contributions are welcome! Fork the repository, make changes, and submit a pull request.

---

## **License**
This project is licensed under the MIT License.
