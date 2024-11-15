
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
