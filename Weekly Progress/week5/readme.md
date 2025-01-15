
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

#### **Code Snippet**:
```cpp
void execute(uint8_t opcode, uint8_t reg1, uint8_t reg2) {
    std::string opcodeStr = getOpcodeString(opcode);
    std::string reg1Name = "R" + std::to_string(reg1);
    std::string reg2Name = "R" + std::to_string(reg2);

    uint8_t operand1 = registers.get(reg1Name);
    uint8_t operand2 = registers.get(reg2Name);
    uint8_t result = 0;

    if (opcodeStr == "LOAD") {
        result = memory.read(operand2); // Load from memory
    } else if (opcodeStr == "STORE") {
        memory.write(operand2, operand1); // Store to memory
        result = operand1; // No modification to register
    } else {
        result = alu.performOperation(opcodeStr, operand1, operand2);
    }

    registers.set(reg1Name, result);

    std::cout << "[Execute] " << opcodeStr
              << " " << reg1Name << ", " << reg2Name
              << " => Updated " << reg1Name << ": " << std::bitset<8>(result) << "\n";
    registers.display();
}
```

---

### **3. Registers (`Registers.h`)**
Simulates general-purpose registers for temporary storage.

#### **Features**:
- Storage of 8-bit values.
- Display of current register values.

#### **Initial Values**:
| Register | Initial Value |
|----------|---------------|
| R0       | 0x00          |
| R1       | 0x04          |
| R2       | 0x09          |
| R3       | 0x0A          |

#### **Code Snippet**:
```cpp
void display() {
    std::cout << "=== Register States ===\n";
    for (const auto& reg : regs) {
        std::cout << reg.first << ": " << std::bitset<8>(reg.second) << "\n";
    }
    std::cout << "========================\n";
}
```

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

#### **Code Snippet**:
```cpp
void segmentInfo() {
    std::cout << "=== Memory Segmentation ===\n";
    std::cout << "Code Segment: 0x00 - 0x03\n";
    std::cout << "Data Segment: 0x04 - 0x07\n";
    std::cout << "Stack Segment: 0x08 - 0x0B\n";
    std::cout << "Heap Segment: 0x0C - 0x0F\n";
    std::cout << "===========================\n";
}
```

---

### **5. Assembler (`Assembler.h`)**
Translates assembly language into binary machine code.

#### **Instruction Format**:
| Bit(s) | Description                   |
|--------|-------------------------------|
| 7-6    | Opcode                        |
| 5-3    | Source Register Index         |
| 2-0    | Destination Register Index    |

#### **Example**:
```assembly
ADD R1 R2
```
Converts to binary:
```plaintext
0b00000110
```

#### **Code Snippet**:
```cpp
std::vector<uint8_t> assemble(const std::string& assemblyCode) {
    std::map<std::string, uint8_t> registers = {{"R0", 0b000}, {"R1", 0b001}, {"R2", 0b010}, {"R3", 0b011}};
    std::istringstream iss(assemblyCode);
    std::string line;
    std::vector<uint8_t> machineCode;

    while (std::getline(iss, line)) {
        std::istringstream linestream(line);
        std::string opcode, reg1, reg2;
        linestream >> opcode >> reg1 >> reg2;
        uint8_t opcodeNum = (opcode == "ADD" ? 0b00 : opcode == "SUB" ? 0b01 : opcode == "LOAD" ? 0b10 : opcode == "STORE" ? 0b11 : 0b00);
        uint8_t machineInstruction = (opcodeNum << 6) | (registers[reg1] << 3) | registers[reg2];
        machineCode.push_back(machineInstruction);
    }

    return machineCode;
}
```

---

### **How It Works**

#### **Execution Process**:
1. **Input Assembly Code**: The user inputs assembly instructions.
2. **Translation**: The assembler converts the instructions into machine code.
3. **Execution**: The CPU fetches, decodes, and executes each instruction sequentially.

#### **Supported Instructions**:
| Instruction | Opcode | Description                                 |
|-------------|--------|---------------------------------------------|
| ADD         | 00     | Add values from two registers.             |
| SUB         | 01     | Subtract second register from the first.    |
| LOAD        | 10     | Load value from memory into a register.     |
| STORE       | 11     | Store value from a register into memory.    |

---

### **Usage Instructions**
1. Compile the program using a C++ compiler.
   ```bash
   g++ main.cpp -o VirtualCPU
   ```
2. Run the executable.
   ```bash
   ./VirtualCPU
   ```
3. Enter assembly instructions as input, ending with an empty line.
   ```assembly
   LOAD R1 R2
   ADD R1 R3
   STORE R1 R2
   ```
4. Observe the output:
   - Machine code.
   - Register and memory states.
   - Execution progress.

#### **Example Run**:
##### **Input**:
```assembly
LOAD R1 R2
ADD R1 R3
STORE R1 R2
```

##### **Output**:
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

### **Conclusion**
This Virtual CPU Emulator is a simple yet effective simulation of a CPU with I/O capabilities. It demonstrates the basic principles of CPU operation, memory management, and I/O device interaction. The emulator can be extended with additional instructions and features to create a more complex simulation.
