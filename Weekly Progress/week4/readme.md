### **Week 4: Instruction Execution**
**Objective**: Develop the instruction fetch-decode-execute cycle.  
**Tasks**:
- Implement the instruction fetching mechanism.
- Decode instructions and execute them using the ALU and registers.
- Test with simple programs.


# Virtual CPU Emulator

This project simulates a simple virtual CPU capable of executing basic assembly instructions. The emulator consists of components like an Arithmetic Logic Unit (ALU), registers, memory, and an assembler to translate assembly code into machine code.

---

## **Project Overview**

### **Features:**
- Emulates the fetch-decode-execute cycle of a CPU.
- Supports basic instructions: `ADD`, `SUB`, `LOAD`, `STORE`.
- Simulates memory and register operations.
- Assembles human-readable assembly code into binary machine code.
- Provides real-time output during execution.

### **Objective:**
This project demonstrates the inner workings of a CPU, including:
1. Instruction decoding.
2. Arithmetic and logical computations.
3. Register and memory interactions.

---

## **Code Structure**

### **Key Components**

1. **`main.cpp`**: Entry point for the program. Handles user input, assembles code, and manages CPU execution.

2. **`CPU.h`**: Implements the main CPU class, responsible for:
   - Fetching instructions from memory.
   - Decoding and executing instructions using the ALU and registers.
   - Managing program control via the program counter.

3. **`ALU.h`**: Defines the Arithmetic Logic Unit, performing operations such as:
   - `ADD`: Adds two register values.
   - `SUB`: Subtracts the value of one register from another.
   - `LOAD`: Loads a value from memory to a register.
   - `STORE`: Stores a register value into memory.

4. **`Registers.h`**: Simulates general-purpose registers, enabling:
   - Storage and retrieval of 8-bit values.
   - Display of current register states for debugging.

5. **`Memory.h`**: Provides a memory module with segmentation for:
   - **Code Segment**: Instructions.
   - **Data Segment**: Program variables.
   - **Stack Segment**: Temporary data storage.
   - **Heap Segment**: Dynamically allocated memory.

6. **`Assembler.h`**: Translates assembly code into binary machine code using the following format:
   - **Opcode** (2 bits): Specifies the operation.
   - **Source Register** (3 bits): Specifies the source operand.
   - **Destination Register** (3 bits): Specifies the target operand.

---

## **Supported Instructions**

### **Instruction Set**
| Instruction | Opcode (Binary) | Description                              |
|-------------|-----------------|------------------------------------------|
| `ADD`       | `00`            | Add values from two registers.           |
| `SUB`       | `01`            | Subtract second register value from first.|
| `LOAD`      | `10`            | Load a value from memory to a register.   |
| `STORE`     | `11`            | Store a register value into memory.       |

### **Machine Code Format**
| Bit(s)       | Description                 |
|--------------|-----------------------------|
| 7-6          | Opcode                      |
| 5-3          | Source Register             |
| 2-0          | Destination Register        |

---

## **How It Works**

### **1. Input Assembly Code**
The user inputs assembly code via the console. Each instruction specifies an operation (`ADD`, `SUB`, `LOAD`, `STORE`) and operands (registers `R0` to `R3`).

Example:
```assembly
LOAD R1 R2
ADD R1 R3
STORE R1 R2
```

### **2. Assembly Process**
- The `Assembler` component converts the assembly code into 8-bit machine code.
- Format:
  - First 2 bits: Opcode (operation type).
  - Next 3 bits: Source register.
  - Last 3 bits: Destination register.

Example Conversion:
- `ADD R1 R2` -> `0b00000110`.

### **3. CPU Execution**
#### **Fetch**:
The instruction is fetched from memory using the program counter.

#### **Decode**:
The instruction is split into opcode, source register, and destination register.

#### **Execute**:
The ALU performs the operation, and results are stored in the destination register or memory.

### **4. Output**
The emulator displays the execution process, including:
- Current instruction.
- Register states.
- Memory updates.

---

## **Execution Steps**

1. **Run the program**:
   ```bash
   ./VirtualCPU
   ```

2. **Input assembly code**:
   Enter instructions, ending with an empty line.

3. **Observe output**:
   - Machine code translation.
   - Fetch-decode-execute cycle.
   - Register and memory updates.

---

## **Example Run**

### Input:
```assembly
LOAD R1 R2
ADD R1 R3
STORE R1 R2
```

### Execution:
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

## **Project Files**

- **`main.cpp`**: Entry point and user interaction.
- **`CPU.h`**: CPU implementation.
- **`ALU.h`**: Arithmetic Logic Unit.
- **`Registers.h`**: Register simulation.
- **`Memory.h`**: Memory segmentation and operations.
- **`Assembler.h`**: Assembly-to-machine code conversion.

---

## **Contributing**
Contributions are welcome! Fork the repository, make changes, and submit a pull request.

---

## **License**
This project is licensed under the MIT License.
