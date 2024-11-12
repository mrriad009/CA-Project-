# Machine Code Conversion for Virtual CPU Emulator

This document explains the conversion of assembly instructions into machine code for a virtual CPU emulator. Each instruction is broken down into its opcode, operands (registers, addresses), and the resulting machine code.

## 1. **ADD R1 R2**
**Assembly Instruction:** `ADD R1 R2`

- **Opcode:** `ADD` corresponds to `0001` in machine code.
- **Operands:** 
  - `R1` corresponds to `001` (binary for register 1).
  - `R2` corresponds to `010` (binary for register 2).
- **Machine Code:** `0001 001 010`

---

## 2. **SUB R4 R5**
**Assembly Instruction:** `SUB R4 R5`

- **Opcode:** `SUB` corresponds to `0010` in machine code.
- **Operands:**
  - `R4` corresponds to `100` (binary for register 4).
  - `R5` corresponds to `101` (binary for register 5).
- **Machine Code:** `0010 100 101`

---

## 3. **LOAD R1 100**
**Assembly Instruction:** `LOAD R1 100`

- **Opcode:** `LOAD` corresponds to `0011` in machine code.
- **Operands:**
  - `R1` corresponds to `001` (binary for register 1).
  - `100` is converted to 8-bit binary: `01100100`.
- **Machine Code:** `0011 001 01100100`

---

## 4. **STORE R2 200**
**Assembly Instruction:** `STORE R2 200`

- **Opcode:** `STORE` corresponds to `0100` in machine code.
- **Operands:**
  - `R2` corresponds to `010` (binary for register 2).
  - `200` is converted to 8-bit binary: `11001000`.
- **Machine Code:** `0100 010 11001000`

---

## 5. **JUMP 300**
**Assembly Instruction:** `JUMP 300`

- **Opcode:** `JUMP` corresponds to `0101` in machine code.
- **Operand:** `300` is converted to 8-bit binary: `00101100`.
- **Machine Code:** `0101 00101100`

---

## 6. **JZ R1 400**
**Assembly Instruction:** `JZ R1 400`

- **Opcode:** `JZ` corresponds to `0110` in machine code.
- **Operands:**
  - `R1` corresponds to `001` (binary for register 1).
  - `400` is converted to 8-bit binary: `11001000`.
- **Machine Code:** `0110 001 11001000`

---

## Summary of Output Structure

- **Opcode (4 bits):** The first part of the machine code corresponds to the operation (e.g., `0001` for `ADD`, `0010` for `SUB`).
- **Registers (3 bits each):** The next part is the binary encoding for the registers involved in the operation (e.g., `001` for `R1`, `010` for `R2`).
- **Address (8 bits):** If the operation involves an address (like `LOAD`, `STORE`, or `JUMP`), it's represented as an 8-bit binary value (e.g., `01100100` for address `100`).

