
# Instruction Format Table

| **Instruction** | **Description**                                   | **Binary Format**             |
|------------------|--------------------------------------------------|-------------------------------|
| `ADD R1, R2, R3` | Adds the values in R2 and R3, stores in R1.      | `0010 R1 R2 R3`               |
| `SUB R1, R2, R3` | Subtracts the value in R3 from R2, stores in R1. | `0011 R1 R2 R3`               |
| `MUL R1, R2, R3` | Multiplies the values in R2 and R3, stores in R1.| `0101 R1 R2 R3`               |
| `DIV R1, R2, R3` | Divides the value in R2 by R3, stores in R1.     | `0110 R1 R2 R3`               |
| `LOAD R1, addr`  | Loads the value at memory address `addr` into R1.| `0111 R1 addr`                |
| `STORE R1, addr` | Stores the value in R1 into memory address `addr`| `1000 R1 addr`                |
| `READ R1`        | Reads input and stores it in R1.                 | `1001 R1`                     |
| `WRITE R1`       | Writes the value in R1 to output.                | `1010 R1`                     |
| `MOV R1, R2`     | Copies the value from R2 to R1.                  | `0001 R1 R2`                  |
| `JMP addr`       | Jumps to the specified memory address `addr`.    | `0100 addr`                   |

---

**Explanation:**
- **`R1`, `R2`, `R3`:** Represent register codes (e.g., `000` for `R0`, `001` for `R1`, etc.).
- **`addr`:** Represents a memory address in binary.
- Each instruction is converted into a fixed binary format for processing by the virtual CPU.



# Explanation of Binary Format 

The **binary format** specifies how assembly instructions are represented as machine code. Here's a detailed breakdown:

---

## **1. Instruction Opcode (Operation Code)**
- **What it is:** The first few bits in the binary format uniquely identify the type of instruction.
- **Example:**  
  - `0001` → Opcode for `MOV`
  - `0010` → Opcode for `ADD`
  - `0100` → Opcode for `JMP`

---

## **2. Register Codes (R1, R2, R3)**
- **What they are:** Each register is assigned a unique 3-bit code, allowing the CPU to identify which registers to use.
- **Register Encoding:**
  - `R0` → `000`
  - `R1` → `001`
  - `R2` → `010`
  - `R3` → `011`
  - `R4` → `100`
  - `R5` → `101`
  - `R6` → `110`
  - `R7` → `111`

---

## **3. Address**
- **What it is:** An 8-bit or larger binary representation of a memory location. Used in instructions like `LOAD`, `STORE`, and `JMP` to specify where in memory to read/write data or jump.
- **Example:**  
  Memory address `100` is represented as `01100100` (8 bits).

---

# Instruction Examples

### **1. `MOV R1, R2`**
- **Binary Format:** `0001 R1 R2`
- **Breakdown:**
  - `0001` → Opcode for `MOV`
  - `001` → Code for `R1`
  - `010` → Code for `R2`
- **Result:** `0001 001 010`

---

### **2. `ADD R1, R2, R3`**
- **Binary Format:** `0010 R1 R2 R3`
- **Breakdown:**
  - `0010` → Opcode for `ADD`
  - `001` → Code for `R1`
  - `010` → Code for `R2`
  - `011` → Code for `R3`
- **Result:** `0010 001 010 011`

---

### **3. `LOAD R1, 100`**
- **Binary Format:** `0111 R1 addr`
- **Breakdown:**
  - `0111` → Opcode for `LOAD`
  - `001` → Code for `R1`
  - `01100100` → Binary for address `100`
- **Result:** `0111 001 01100100`

---

### **4. `JMP 300`**
- **Binary Format:** `0100 addr`
- **Breakdown:**
  - `0100` → Opcode for `JMP`
  - `100101100` → Binary for address `300`
- **Result:** `0100 100101100`

---

# Summary
The **binary format** is structured as follows:
1. **Opcode:** Identifies the instruction type (e.g., `ADD`, `MOV`).
2. **Register Codes:** Specify which registers are involved (e.g., `R1`, `R2`).
3. **Memory Address (if applicable):** For instructions interacting with memory (e.g., `LOAD`, `JMP`).
