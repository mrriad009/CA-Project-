# Virtual CPU Emulator with I/O Device Integration

This documentation describes the enhanced Virtual CPU Emulator, which now includes support for input and output (I/O) operations. This feature was introduced in Week 6 of the project.

---

## **Overview**
The Week 6 update integrates I/O capabilities into the Virtual CPU Emulator, enabling interactions between the emulator and simulated input/output devices.

### **Key Features**
- Simulated **keyboard input**.
- Simulated **display output**.
- Additional instructions: `IN` and `OUT` for I/O operations.

---

## **Components**

### **1. IODevice (`IODevice.h`)**
The I/O device simulates a basic keyboard and display.

#### **Features**
- **Keyboard Input (`keyboard_read`)**:
  - Simulates pressing a key (e.g., ASCII value `A` represented as `0b01000001`).
- **Display Output (`display_output`)**:
  - Simulates outputting data to a display.

#### **Code Snippet**
```cpp
static int keyboard_read() {
    int key = 0b01000001; // Simulated key press 'A'
    std::cout << "[Keyboard] Simulated key press: " << std::bitset<8>(key) << std::endl;
    return key;
}

static void display_output(int data) {
    std::cout << "[Display] Output: " << std::bitset<8>(data) << std::endl;
}
```

---

### **2. CPU (`CPU.h`)**
The CPU is extended to support the `IN` and `OUT` instructions.

#### **New Instructions**
| Instruction | Opcode | Description                              |
|-------------|--------|------------------------------------------|
| `IN`        | `100`  | Reads input from the keyboard into a register. |
| `OUT`       | `101`  | Outputs the value of a register to the display. |

#### **Execution Flow for I/O**
- **IN Instruction**:
  - Fetch: Retrieves the instruction from memory.
  - Decode: Extracts the opcode and target register.
  - Execute: Reads input from the keyboard and stores it in the specified register.

- **OUT Instruction**:
  - Fetch: Retrieves the instruction from memory.
  - Decode: Extracts the opcode and source register.
  - Execute: Outputs the value of the specified register to the display.

---

### **3. Assembler (`Assembler.h`)**
The assembler is updated to translate `IN` and `OUT` instructions into machine code.

#### **Instruction Format**
| Bit(s) | Description           |
|--------|-----------------------|
| 7-5    | Opcode                |
| 4-3    | Unused (0)            |
| 2-0    | Register Index        |

#### **Code Snippet**
```cpp
if (line == "IN R0") {
    machine_code.push_back(0b10000000); // IN R0
} else if (line == "OUT R0") {
    machine_code.push_back(0b10100000); // OUT R0
}
```

---

### **4. Memory (`Memory.h`)**
Memory operations remain unchanged, supporting the storage and retrieval of machine code instructions and data.

---

### **5. Main Program (`main.cpp`)**
The main program demonstrates the new I/O functionality.

#### **Execution Flow**
1. **Input Assembly Code**:
   - Users provide assembly instructions, including `IN` and `OUT`.
2. **Assembler**:
   - Converts instructions to machine code.
3. **CPU Execution**:
   - Fetch-decode-execute cycle processes the machine code, performing I/O as specified.

#### **Sample Assembly Code**
```assembly
IN R0
OUT R0
```

---

## **Example Run and Output Explanation**

### Input:
```assembly
IN R0
OUT R0
```

### Detailed Execution:
1. **Assembly Code Input**:
   ```plaintext
   IN R0
   OUT R0
   ```

2. **Assembling Code**:
   - `IN R0` -> Machine Code: `10000000`
   - `OUT R0` -> Machine Code: `10100000`
   ```plaintext
   [Assembling Code...]
   [Generated Machine Code]:
   10000000 10100000
   ```

3. **Program Execution**:
   - Fetch, Decode, and Execute cycle:
     - **Cycle 1**:
       - **Fetch**: Reads instruction `10000000`.
       - **Decode**: Opcode `100` (IN), Register `R0`.
       - **Execute**: Reads `0b01000001` from the keyboard into `R0`.
       - **Output**:
         ```plaintext
         [Keyboard] Simulated key press: 01000001
         [CPU] Updated R0: 01000001
         ```

     - **Cycle 2**:
       - **Fetch**: Reads instruction `10100000`.
       - **Decode**: Opcode `101` (OUT), Register `R0`.
       - **Execute**: Outputs `0b01000001` from `R0` to the display.
       - **Output**:
         ```plaintext
         [Display] Output: 01000001
         ```

4. **Final Output**:
   ```plaintext
   [Execution Complete]
   ```

---


