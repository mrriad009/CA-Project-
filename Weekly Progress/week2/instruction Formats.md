### Instruction Format Table


| Instruction  |        Format            |             Description                     |
|--------------|--------------------------|---------------------------------------------|
| ADD          | `ADD R1, R2, R3`         | Adds R2 and R3 and stores the result in R1  |
| SUB          | `SUB R1, R2, R3`         | Subtracts R3 from R2 and stores in R1       |
| LOAD         | `LOAD R1, address`       | Loads a value from memory into R1           |
| STORE        | `STORE R1, address`      | Stores the value of R1 into memory          |
| JUMP         | `JUMP address`           | Jumps to the specified address              |
| JZ           | `JZ R1, address`         | Jumps if R1 is zero                         |
| JNZ          | `JNZ R1, address`        | Jumps if R1 is not zero                     |
| READ         | `READ R1`                | Reads input into R1                         |
| WRITE        | `WRITE R1`               | Outputs the value of R1                     |