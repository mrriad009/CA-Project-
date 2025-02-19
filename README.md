
# Project Name: Virtual CPU Emulator

## Group Members 
- 1 . Mahamudul Islam Riad  || ID : 11220320898
- 2 . Mahatab Hossain       || ID : 11220320997
- 3 . Muzahidur Rahman      || ID : 11220120780

## Course Details
- Course Name: Computer Architecture
- Course Code: 3101
- Section: 5F
- Department: Computer Science & Engineering
- Instructor: Vashkar Kar (Lecturer)
- Institute: Northern University of Business & Technology Khulna
- Website: www.nubtkhulna.ac.bd

##  Project Overview
The goal of this project is to build a virtual CPU emulator. The emulator will replicate basic CPU functionality, including instruction execution, memory management, and I/O operations, in a simplified environment. This project will allow users to write and run assembly programs on a simulated CPU.

##  Project Goals
- To implement a basic instruction set architecture (ISA) with standard operations (e.g., ADD, SUB, LOAD, STORE).
- To simulate core CPU components, including an ALU, registers, program counter, and memory management.
- To support basic I/O operations.
- To optimize performance through pipelining and other techniques.

##  Key Features
- **Instruction Set**: A set of basic instructions for arithmetic, data transfer, and control flow.
- **ALU**: Handles arithmetic and logical operations.
- **Registers**: General-purpose registers for temporary storage.
- **Program Counter**: Tracks the address of the current instruction.
- **Memory Management**: Simulated memory space for instruction and data storage.
- **Input/Output**: Emulated keyboard input and display output.






# Virtual CPU Emulator

This project simulates a basic CPU with various components and operations. The code is divided into different weeks, each focusing on a specific aspect of the CPU. Below is a step-by-step explanation of the operations and their purposes.

## Week 1: Project Planning & Setup
- Setting up the project environment.
- Writing initial documentation and creating project scaffolding.

## Week 2: Define ISA and Create an Assembler

### Purpose
Define an Instruction Set Architecture (ISA) and create an assembler to convert assembly instructions to machine code.

### Operations
1. **ISA Definition**:
    - Define a set of instructions with their corresponding opcodes.
    - Example: `{"ADD", "0001"}` for addition.

2. **Assembler Function**:
    - Convert assembly instructions to machine code.
    - Example: `"ADD R1 10"` to `"0001 0001 00001010"`.

3. **Example Instructions**:
    - Convert a set of example instructions to machine code.

### Key Operation
```cpp
auto assembler = [&](const string& instruction) {
    string opcode;
    string reg;
    string value = "000000";

    stringstream ss(instruction);
    string cmd, reg_str;
    int num;
    ss >> cmd >> reg_str >> num;
    
    // Fetch opcode for the command
    for (const auto& pair : isa) {
        if (pair.first == cmd) {
            opcode = pair.second;
            break;
        }
    }
    
    reg = bitset<4>(stoi(reg_str.substr(1))).to_string(); // Register in binary (e.g., R1 -> 0001)
    value = bitset<8>(num).to_string();  // Value in binary (e.g., 10 -> 00001010)
    
    return opcode + " " + reg + " " + value;
};
```
- `auto assembler = [&](const string& instruction) {`: Define a lambda function named `assembler` that takes an instruction string as input.
- `string opcode; string reg; string value = "000000";`: Initialize strings to store the opcode, register, and value.
- `stringstream ss(instruction);`: Create a stringstream object to parse the instruction.
- `string cmd, reg_str; int num; ss >> cmd >> reg_str >> num;`: Extract the command, register string, and number from the instruction.
- `for (const auto& pair : isa) { if (pair.first == cmd) { opcode = pair.second; break; } }`: Loop through the ISA to find the opcode for the command.
- `reg = bitset<4>(stoi(reg_str.substr(1))).to_string();`: Convert the register string to a binary string.
- `value = bitset<8>(num).to_string();`: Convert the number to a binary string.
- `return opcode + " " + reg + " " + value;`: Return the concatenated opcode, register, and value.

## Week 3: Build Basic CPU Components

### Purpose
Simulate basic CPU components, specifically an Arithmetic Logic Unit (ALU) and a set of registers.

### Operations
1. **ALU Class**:
    - Perform arithmetic operations (ADD, SUB) based on opcodes.

2. **Registers Class**:
    - Store and retrieve values in registers.

3. **Example Operations**:
    - Perform example operations using the ALU and registers.

### Key Operation
```cpp
class ALU {
public:
    int operate(const string& opcode, int operand1, int operand2) {
        if (opcode == "0001") { // ADD
            return operand1 + operand2;
        } else if (opcode == "0010") { // SUB
            return operand1 - operand2;
        }
        return 0;
    }
};
```
- `class ALU {`: Define a class named `ALU`.
- `public: int operate(const string& opcode, int operand1, int operand2) {`: Define a public method named `operate` that takes an opcode and two operands as input.
- `if (opcode == "0001") { return operand1 + operand2; }`: If the opcode is "0001" (ADD), return the sum of the operands.
- `else if (opcode == "0010") { return operand1 - operand2; }`: If the opcode is "0010" (SUB), return the difference of the operands.
- `return 0;`: Return 0 if the opcode is not recognized.

## Week 4: Implement Fetch-Decode-Execute Cycle

### Purpose
Simulate the fetch-decode-execute cycle of a CPU.

### Operations
1. **Memory Initialization**:
    - Initialize memory with a set of instructions.

2. **Decode Function**:
    - Decode instructions into opcodes and operands.

3. **Execute Function**:
    - Execute instructions based on opcodes.

4. **Fetch-Decode-Execute Cycle**:
    - Simulate the cycle by fetching, decoding, and executing instructions.

### Key Operation
```cpp
auto decode = [](const string& instruction) {
    stringstream ss(instruction);
    string opcode;
    vector<string> operands;
    ss >> opcode;
    string operand;
    while (ss >> operand) {
        operands.push_back(operand);
    }
    return make_pair(opcode, operands);
};

auto execute = [&](const string& opcode, const vector<string>& operands) {
    if (opcode == "LOAD") {
        registers[operands[0]] = stoi(operands[1]);
    } else if (opcode == "ADD") {
        registers[operands[0]] += registers[operands[1]];
    } else if (opcode == "STORE") {
        cout << "Value at Memory Address " << operands[1] << ": " << registers[operands[0]] << endl;
    } else {
        cout << "Unknown instruction" << endl;
    }
};
```
- `auto decode = [](const string& instruction) {`: Define a lambda function named `decode` that takes an instruction string as input.
- `stringstream ss(instruction);`: Create a stringstream object to parse the instruction.
- `string opcode; vector<string> operands; ss >> opcode;`: Extract the opcode from the instruction.
- `string operand; while (ss >> operand) { operands.push_back(operand); }`: Extract the operands from the instruction.
- `return make_pair(opcode, operands);`: Return a pair containing the opcode and operands.
- `auto execute = [&](const string& opcode, const vector<string>& operands) {`: Define a lambda function named `execute` that takes an opcode and operands as input.
- `if (opcode == "LOAD") { registers[operands[0]] = stoi(operands[1]); }`: If the opcode is "LOAD", load the value into the register.
- `else if (opcode == "ADD") { registers[operands[0]] += registers[operands[1]]; }`: If the opcode is "ADD", add the value of the second register to the first register.
- `else if (opcode == "STORE") { cout << "Value at Memory Address " << operands[1] << ": " << registers[operands[0]] << endl; }`: If the opcode is "STORE", print the value of the register at the specified memory address.
- `else { cout << "Unknown instruction" << endl; }`: Print an error message if the opcode is not recognized.

## Week 5: Memory Management

### Purpose
Simulate basic memory management operations.

### Operations
1. **Memory Initialization**:
    - Initialize memory with a set of locations.

2. **Write Memory**:
    - Write values to specific memory addresses.

3. **Read Memory**:
    - Read values from specific memory addresses.

### Key Operation
```cpp
auto write_memory = [&](int address, int value) {
    memory[address] = value;
};

auto read_memory = [&](int address) {
    return memory[address];
};
```
- `auto write_memory = [&](int address, int value) {`: Define a lambda function named `write_memory` that takes an address and value as input.
- `memory[address] = value;`: Write the value to the specified memory address.
- `auto read_memory = [&](int address) {`: Define a lambda function named `read_memory` that takes an address as input.
- `return memory[address];`: Return the value at the specified memory address.

## Week 6: I/O Operations

### Purpose
Simulate basic I/O operations.

### Operations
1. **I/O Devices Initialization**:
    - Initialize I/O devices (keyboard, display).

2. **Read Input**:
    - Simulate reading input from a keyboard.

3. **Write Output**:
    - Simulate writing output to a display.

4. **Binary and Decimal Output**:
    - Display output in both binary and decimal formats.

### Key Operation
```cpp
auto read_input = [&](const string& device) {
    if (device == "keyboard") {
        int input_value = 98; // Simulate reading input from keyboard (e.g., entering the number 98)
        io_devices[device] = bitset<8>(input_value).to_string(); // Convert to binary string
    }
};

auto write_output = [&](const string& device) -> string {
    if (device == "display") {
        int decimal_value = bitset<8>(io_devices[device]).to_ulong(); // Convert binary string to decimal
        return "Display Output: " + io_devices[device] + " (Decimal: " + to_string(decimal_value) + ")";
    }
    return "";
};
```
- `auto read_input = [&](const string& device) {`: Define a lambda function named `read_input` that takes a device string as input.
- `if (device == "keyboard") { int input_value = 98; io_devices[device] = bitset<8>(input_value).to_string(); }`: If the device is "keyboard", simulate reading input and convert it to a binary string.
- `auto write_output = [&](const string& device) -> string {`: Define a lambda function named `write_output` that takes a device string as input and returns a string.
- `if (device == "display") { int decimal_value = bitset<8>(io_devices[device]).to_ulong(); return "Display Output: " + io_devices[device] + " (Decimal: " + to_string(decimal_value) + ")"; }`: If the device is "display", convert the binary string to a decimal value and return the output string.

## Week 7: Advanced Features

### Purpose
Simulate advanced CPU features, including branching and halting.

### Operations
1. **Memory Initialization**:
    - Initialize memory with a set of instructions.

2. **Execute Function**:
    - Execute instructions based on opcodes (branching, adding, halting).

3. **Fetch-Decode-Execute Cycle**:
    - Simulate the cycle by fetching, decoding, and executing instructions.

4. **Register Values**:
    - Display final register values in binary format.

### Key Operation
```cpp
auto execute = [&](const string& instruction) -> bool {
    string opcode = instruction.substr(0, 4);
    bool pc_modified = false;
    if (opcode == "0110") { // Branch to address
        pc = stoi(instruction.substr(4), nullptr, 2);
        pc_modified = true;
    } else if (opcode == "0001") { // ADD
        int reg_num = stoi(instruction.substr(4, 2), nullptr, 2);
        int value = stoi(instruction.substr(6), nullptr, 2);
        registers[reg_num] += value;
    } else if (opcode == "1111") { // HALT
        pc = memory.size();
        pc_modified = true;
    }
    return pc_modified;
};
```
- `auto execute = [&](const string& instruction) -> bool {`: Define a lambda function named `execute` that takes an instruction string as input and returns a boolean.
- `string opcode = instruction.substr(0, 4);`: Extract the opcode from the instruction.
- `bool pc_modified = false;`: Initialize a boolean to track if the program counter is modified.
- `if (opcode == "0110") { pc = stoi(instruction.substr(4), nullptr, 2); pc_modified = true; }`: If the opcode is "0110" (branch), update the program counter and set `pc_modified` to true.
- `else if (opcode == "0001") { int reg_num = stoi(instruction.substr(4, 2), nullptr, 2); int value = stoi(instruction.substr(6), nullptr, 2); registers[reg_num] += value; }`: If the opcode is "0001" (ADD), add the value to the specified register.
- `else if (opcode == "1111") { pc = memory.size(); pc_modified = true; }`: If the opcode is "1111" (HALT), set the program counter to the end of memory and set `pc_modified` to true.
- `return pc_modified;`: Return whether the program counter was modified.

## Week 8: Performance Optimization

### Purpose
Profile and optimize the performance of the CPU emulator.

### Operations
1. **Memory Initialization**:
    - Initialize memory with a set of instructions.

2. **Execute Function**:
    - Execute instructions based on opcodes (adding, subtracting).

3. **Profile Execution Time**:
    - Measure and display the execution time of the emulator.

### Key Operation
```cpp
auto execute = [&](const string& instruction) {
    string opcode = instruction.substr(0, 4);
    int reg_num = stoi(instruction.substr(4, 2), nullptr, 2);
    int value = stoi(instruction.substr(6), nullptr, 2);
    if (opcode == "0001") { // ADD
        registers[reg_num] += value;
    } else if (opcode == "0010") { // SUB
        registers[reg_num] -= value;
    }
};

// Profile the emulator
clock_t start_time = clock();
while (pc < memory.size()) {
    execute(memory[pc]);
    pc++;
}
clock_t end_time = clock();

vector<string> result;
result.push_back("Execution Time: " + to_string(double(end_time - start_time) / CLOCKS_PER_SEC) + " seconds");
```
- `auto execute = [&](const string& instruction) {`: Define a lambda function named `execute` that takes an instruction string as input.
- `string opcode = instruction.substr(0, 4);`: Extract the opcode from the instruction.
- `int reg_num = stoi(instruction.substr(4, 2), nullptr, 2);`: Extract the register number from the instruction.
- `int value = stoi(instruction.substr(6), nullptr, 2);`: Extract the value from the instruction.
- `if (opcode == "0001") { registers[reg_num] += value; }`: If the opcode is "0001" (ADD), add the value to the specified register.
- `else if (opcode == "0010") { registers[reg_num] -= value; }`: If the opcode is "0010" (SUB), subtract the value from the specified register.
- `clock_t start_time = clock();`: Record the start time.
- `while (pc < memory.size()) { execute(memory[pc]); pc++; }`: Execute instructions in memory until the end.
- `clock_t end_time = clock();`: Record the end time.
- `vector<string> result; result.push_back("Execution Time: " + to_string(double(end_time - start_time) / CLOCKS_PER_SEC) + " seconds");`: Calculate and store the execution time.