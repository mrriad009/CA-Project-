## Objective:
The goal for Week 7 was to implement advanced CPU features, which include branching and control flow instructions, support for subroutines and interrupts, and integration of a simple pipeline mechanism. These features aim to enhance the CPU’s functionality, making it capable of handling more complex programs and improving performance through parallel execution.

### 1. Implement Branching and Control Flow Instructions
**Task:** Add support for branching instructions like conditional and unconditional jumps (e.g., JUMP, CALL, RET) to allow the CPU to control the execution flow based on specific conditions.

**Changes:**

**Branch Instructions:**

- **JUMP:** The JUMP instruction changes the `programCounter` to a specified address, causing the CPU to jump to that location in the instruction memory.
- **CALL:** The CALL instruction pushes the return address (current `programCounter`) to memory and then changes the `programCounter` to a new address, which simulates a function call.
- **RET:** The RET instruction pops the return address from memory and sets the `programCounter` back to that address, returning control to the point after the function call.

**Implementation:**

- During CALL, the `programCounter` is saved to memory (or a stack).
- During RET, the `programCounter` is restored from memory (or the stack).
- The JUMP instruction directly modifies the `programCounter`.

**Example:**
```cpp
if (opcodeStr == "JUMP") {
    programCounter = operand2;
    cout << "Jumping to address " << operand2 << endl;
} else if (opcodeStr == "CALL") {
    memory.write(memory.memorySpace.size() - 1, programCounter);
    programCounter = operand2;
    cout << "Calling subroutine at address " << operand2 << endl;
} else if (opcodeStr == "RET") {
    programCounter = memory.read(memory.memorySpace.size() - 1);
    cout << "Returning from subroutine to address " << programCounter << endl;
}
```

### 2. Add Support for Subroutines and Interrupts
**Task:** Implement support for subroutine calls (via the CALL and RET instructions) and interrupts, allowing the CPU to handle function calls and asynchronous events.

**Changes:**

**Subroutine Support:** The CALL and RET instructions were implemented to simulate a stack-based subroutine system. The `programCounter` is saved on the stack when entering a subroutine, and it is restored upon returning, allowing for nested function calls.

**Implementation:**

- **CALL:** Stores the current `programCounter` in memory and jumps to the subroutine address.
- **RET:** Pops the return address from memory, effectively allowing the program to return to the calling point after executing the subroutine.

**Example:**
```cpp
// Simulate a subroutine call
memory.write(memory.memorySpace.size() - 1, programCounter);
programCounter = operand2;
```

**Interrupt Handling (Basic Support):** For simplicity, interrupts were simulated as a JUMP to a special interrupt service routine (ISR) address when an interrupt occurs. This is a simplified version of interrupt handling, where the CPU halts its current execution and jumps to a predefined interrupt address.

**Implementation:**

- Interrupts were handled by triggering a JUMP instruction to a pre-configured ISR address whenever an interrupt occurs.

### 3. Integrate a Simple Pipeline Mechanism
**Task:** Implement a basic pipeline mechanism to simulate the execution of multiple instructions in parallel, allowing the CPU to fetch, decode, and execute instructions in different stages.

**Changes:**

**Pipeline Stages:**

- The pipeline simulates the process of instruction fetch, decode, and execution in different stages, allowing each stage to operate in parallel.
- The pipeline implementation includes three basic stages:
  - **Fetch:** Fetch the next instruction from memory.
  - **Decode:** Decode the instruction to identify the operation and operands.
  - **Execute:** Perform the operation specified by the decoded instruction.

**Pipeline Implementation:**

- The CPU class was modified to introduce pipeline stages. While one instruction is being decoded or executed, the next instruction is fetched, enabling a higher throughput.
- Pipeline control was introduced to manage the flow of instructions between stages.

**Example:**
```cpp
void fetchInstruction() {
    currentInstruction = instructionMemory[programCounter];
    programCounter++;
}

void decodeInstruction() {
    int opcode = (currentInstruction >> 6) & 0x03;
    int reg1 = (currentInstruction >> 3) & 0x07;
    int reg2 = currentInstruction & 0x07;
    // Decoding logic...
}

void executeInstruction() {
    // Execute the decoded instruction using ALU and memory...
}

void pipelineCycle() {
    fetchInstruction();
    decodeInstruction();
    executeInstruction();
}
```

**Simple Pipeline Cycle:** A single cycle in the pipeline consists of fetching an instruction, decoding it, and executing it. Instructions move through the pipeline in stages, overlapping their execution.

### 4. Changes in Code and Execution Flow
**Task:** Modify the CPU class to incorporate the pipeline mechanism and branching/subroutine features.

**Changes:**

**Pipeline Integration in the CPU Class:**

- Added stages for instruction fetch, decode, and execution.
- Managed the flow of instructions through the pipeline by calling `fetchInstruction()`, `decodeInstruction()`, and `executeInstruction()` in a cycle.

**Example:**
```cpp
void pipelineCycle() {
    fetchInstruction();
    decodeInstruction();
    executeInstruction();
}
```

**Control Flow Instructions:**

- The JUMP, CALL, and RET instructions were handled in the `decodeAndExecute` method to control the program’s flow by modifying the `programCounter` directly.

**Subroutine and Interrupt Handling:**

- During a CALL instruction, the program counter is saved in memory to simulate a subroutine stack, and the program counter is updated to the subroutine's address.
- During a RET instruction, the program counter is restored from memory, resuming execution after the subroutine.

### 5. Execution Flow with Advanced Features
**Task:** Implement an advanced execution flow that handles branching, subroutines, and interrupt simulation with a pipeline.

**Changes:**

**Handling Jumps and Subroutines:**
- The execution flow was adjusted to handle JUMP, CALL, and RET instructions appropriately by modifying the `programCounter` based on these instructions.

**Pipeline Stage Synchronization:**
- Instructions are fetched, decoded, and executed in parallel. However, proper synchronization is needed to ensure that no instruction is decoded or executed before being fetched, avoiding race conditions in the pipeline.
