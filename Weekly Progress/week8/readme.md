# Week 8 Progress

## 1. Profiling the Emulator to Identify Bottlenecks
**Task:** Profile the emulator to determine where the performance bottlenecks exist, such as inefficient algorithms, excessive memory access, or slow operations.

**Changes:**

### Profiling with `std::chrono`
- Added a profiling mechanism using `std::chrono::high_resolution_clock` to measure the time taken for executing key parts of the emulator.
- A function `profileExecution()` was introduced to wrap the entire program execution, measuring its performance.
- The execution time for loading, assembling, and running the program is now captured and displayed.

**Example:**
```cpp
auto start = chrono::high_resolution_clock::now();

// Your code to be profiled (for example, execute the program)
CPU cpu;
string filename = "input.txt";
string assemblyCode = loadAssemblyCode(filename);
vector<int> machineCode = assemble(assemblyCode);
executeProgram(cpu, machineCode);

auto end = chrono::high_resolution_clock::now();
chrono::duration<double> duration = end - start;
cout << "\nExecution Time: " << duration.count() << " seconds." << endl;
```
This enables you to analyze execution times and identify potential performance bottlenecks in the program.

## 2. Optimize Critical Code Paths
**Task:** Optimize critical code paths in the emulator to improve execution speed, particularly those that are executed frequently (e.g., register accesses, memory operations).

**Changes:**

### Optimized Access to `unordered_map` for Registers and Opcodes
- Replaced the `map` container with `unordered_map` for faster key-value lookups when accessing registers and opcodes.
- This reduces the overhead of balancing the tree structure of `map` and allows for constant-time lookups, improving the efficiency of instruction decoding and register access.

**Example:**
```cpp
unordered_map<string, int> regs;
```

### Reduced Redundant Operations
- Inside critical code paths (e.g., `decodeAndExecute`), intermediate results (like register values) are now stored in variables to avoid redundant calls.

**Example:**
```cpp
int operand1 = registers.get("R" + to_string(reg1));
int operand2 = registers.get("R" + to_string(reg2));
```

### Streamlined Instruction Decoding
- The instruction decoding process was simplified by removing unnecessary branching and computations.
- The key operation was the `assemble()` function, where redundant checks were removed, making it more efficient.

## 3. Enhance the Assembler for Better Instruction Encoding
**Task:** Modify the assembler to ensure more efficient encoding of instructions and reduce unnecessary space usage or memory accesses.

**Changes:**

### Optimized Instruction Encoding
- The assembler was optimized to handle instruction encoding in a more efficient way.
- Used `unordered_map` for faster opcode and register lookup, which significantly improves the encoding process.
- The encoded instructions are stored in a vector, reducing unnecessary memory reallocation.

**Example:**
```cpp
int encodedInstruction = (opcodes[opcode] << 6) | (registers[reg1] << 3) | registers[reg2];
machineCode.push_back(encodedInstruction);
```

### Improved Handling of Invalid Lines
- The assembler now skips invalid or empty lines, ensuring only valid instructions are processed.
- This helps in reducing the overhead of unnecessary processing and improves performance.

## 4. Optimized Memory Access and Register Operations
**Task:** Ensure that memory and register operations are as efficient as possible, particularly in the context of frequently accessed registers or memory locations.

**Changes:**

### Optimized Memory Access
- Instead of repeatedly calling the `regs` or `memorySpace` for values, results are stored in local variables, ensuring faster access to values in later operations.

**Example:**
```cpp
int operand1 = registers.get("R" + to_string(reg1));
int operand2 = registers.get("R" + to_string(reg2));
```

### Improved Memory Writing
- In the `Memory` class, the `write()` method now includes better checks for out-of-bound memory writes and reduces logging to only the most critical parts of the code.

## 5. Profiling Execution Time
**Task:** Measure and display the time it takes to execute the program, so improvements in performance can be tracked.

**Changes:**

### Time Measurement with `std::chrono`
- We encapsulated the entire program execution in the `profileExecution()` function to measure how long the program takes to execute, including loading assembly, converting to machine code, and running the CPU instructions.
- This allows you to easily measure the impact of optimizations made throughout the emulator.

## 6. Cleaner Code and Function Separation
**Task:** Improve code readability and organization by separating different concerns into distinct functions.

**Changes:**

### Function Separation
- A new function `profileExecution()` was created to manage the profiling aspect, making the `main()` function cleaner and more focused.
- The `loadAssemblyCode()`, `assemble()`, and `executeProgram()` functions were separated for better modularity and easier maintenance.

**Example:**
```cpp
string loadAssemblyCode(const string& filename) {
    // Load code from file
}

vector<int> assemble(const string& assemblyCode) {
    // Assemble instructions into machine code
}

void executeProgram(CPU& cpu, const vector<int>& machineCode) {
    // Execute program with given machine code
}
```

## Summary of Changes:
### Profiling:
- Introduced profiling to measure and track execution time using `std::chrono`.
- Provided clear timing results to help identify performance bottlenecks.

### Optimized Code Paths:
- Replaced `map` with `unordered_map` for faster lookups.
- Reduced redundant operations in frequently called functions.
- Simplified instruction decoding to minimize processing overhead.

### Instruction Encoding Enhancement:
- Streamlined the instruction encoding process to minimize unnecessary operations and improve performance.

### Memory and Register Operations:
- Optimized access to registers and memory to reduce overhead.

### Cleaner Code:
- Separated concerns into smaller, more manageable functions.
- Simplified the `main()` function to focus on high-level tasks.