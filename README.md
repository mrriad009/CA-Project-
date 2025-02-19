# CPU Emulator Project

This project simulates a basic CPU with various components and operations. The code is divided into different weeks, each focusing on a specific aspect of the CPU. Below is a step-by-step explanation of the operations and their purposes.

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