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

### Code
```cpp
vector<string> week_2_define_instructions() {
    // ISA definition
    vector<pair<string, string>> isa = {
        {"ADD", "0001"},  // Opcode for addition
        {"SUB", "0010"},  // Opcode for subtraction
        {"LOAD", "0011"}, // Opcode for loading from memory
        {"STORE", "0100"} // Opcode for storing to memory
    };

    // Assembler function to convert instruction to machine code
    auto assembler = [&](const string& instruction) {
        // ...existing code...
    };

    // Example assembly instructions
    vector<string> instructions = {"ADD R1 10", "SUB R2 5", "LOAD R1 20", "STORE R2 15"};
    vector<string> machine_code;
    
    for (const auto& inst : instructions) {
        machine_code.push_back(assembler(inst));
    }
    
    return machine_code;
}
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

### Code
```cpp
vector<string> week_3_cpu_components() {
    class ALU {
    public:
        int operate(const string& opcode, int operand1, int operand2) {
            // ...existing code...
        }
    };

    class Registers {
    public:
        vector<int> regs = {0, 0, 0, 0}; // Four 6-bit registers

        void write(int reg_num, int value) {
            // ...existing code...
        }

        int read(int reg_num) {
            // ...existing code...
        }
    };

    ALU alu;
    Registers registers;
    int pc = 0; // Program counter

    // Example operations
    registers.write(0, 2); // Write 2 to R0
    registers.write(1, 3); // Write 3 to R1
    int result = alu.operate("0001", registers.read(0), registers.read(1)); // ADD R0, R1

    vector<string> main_result;
    main_result.push_back("Result of ADD: " + to_string(result));
    main_result.push_back("Program Counter: " + to_string(pc));
    return main_result;
}
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

### Code
```cpp
vector<string> week_4_execute_instructions() {
    vector<string> memory = {"LOAD R1 10", "ADD R1 R2", "STORE R1 20"};
    unordered_map<string, int> registers = {{"R1", 0}, {"R2", 5}};
    int pc = 0;
    
    auto decode = [](const string& instruction) {
        // ...existing code...
    };

    auto execute = [&](const string& opcode, const vector<string>& operands) {
        // ...existing code...
    };

    vector<string> main_result;
    
    // Fetch-Decode-Execute Cycle
    while (pc < memory.size()) {
        string instruction = memory[pc]; // Fetch
        main_result.push_back("Fetched Instruction: " + instruction);
        
        auto decoded = decode(instruction); // Decode
        string opcode = decoded.first;
        vector<string> operands = decoded.second;
        main_result.push_back("Decoded Instruction: Opcode = " + opcode + ", Operands = ");
        for (const auto& operand : operands) {
            main_result.push_back(operand + " ");
        }
        
        execute(opcode, operands); // Execute
        main_result.push_back("Registers after execution: ");
        for (const auto& reg : registers) {
            main_result.push_back(reg.first + ": " + to_string(reg.second));
        }
        
        pc++; // Update Program Counter to the next instruction
    }
    return main_result;
}
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

### Code
```cpp
vector<string> week_5_memory_management() {
    vector<int> memory(16, 0); // 16 memory locations
    
    auto write_memory = [&](int address, int value) {
        // ...existing code...
    };

    auto read_memory = [&](int address) {
        // ...existing code...
    };

    // Example operations
    write_memory(2, 5);  // Write value 5 to address 2
    write_memory(5, 11); // Write value 11 to address 5

    vector<string> result;
    for (int i = 0; i < memory.size(); ++i) {
        result.push_back("Address " + to_string(i) + ": " + bitset<6>(memory[i]).to_string());
    }
    return result;
}
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

### Code
```cpp
vector<string> week_6_io_operations() {
    unordered_map<string, string> io_devices = {{"keyboard", "00000000"}, {"display", "00000000"}};

    auto read_input = [&](const string& device) {
        // ...existing code...
    };

    auto write_output = [&](const string& device) -> string {
        // ...existing code...
    };

    read_input("keyboard");
    io_devices["display"] = io_devices["keyboard"]; // Copy keyboard input to display

    vector<string> result;
    result.push_back(write_output("display"));
    return result;
}
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

### Code
```cpp
vector<string> week_7_advanced_features() {
    vector<string> memory = {"011000000001", "000101000001", "111100000000"};  // Branch to 1, ADD, HALT
    vector<int> registers(4, 0);
    int pc = 0;

    auto execute = [&](const string& instruction) -> bool {
        // ...existing code...
    };

    vector<string> result;
    
    // Pipeline: Fetch, Decode, Execute
    while (pc < memory.size()) {
        string instruction = memory[pc];
        bool pc_modified = execute(instruction);
        if (!pc_modified) {
            pc++;
        }
    }

    for (int i = 0; i < registers.size(); ++i) {
        result.push_back("R" + to_string(i) + ": " + bitset<6>(registers[i]).to_string());
    }

    return result;
}
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

### Code
```cpp
vector<string> week_8_optimization() {
    vector<string> memory = {"000101000010", "001010000001", "111100000000"}; // ADD, SUB, HALT
    vector<int> registers(4, 0);
    int pc = 0;

    auto execute = [&](const string& instruction) {
        // ...existing code...
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
    
    for (int i = 0; i < registers.size(); ++i) {
        result.push_back("R" + to_string(i) + ": " + bitset<6>(registers[i]).to_string());
    }

    return result;
}
```

## Main Function

### Purpose
Run all the weekly functions and display their outputs.

### Operations
1. **Week 2 Output**:
    - Display machine code output.

2. **Week 3 Output**:
    - Display CPU components output.

3. **Week 4 Output**:
    - Display execute instructions output.

4. **Week 5 Output**:
    - Display memory management output.

5. **Week 6 Output**:
    - Display I/O operations output.

6. **Week 7 Output**:
    - Display advanced features output.

7. **Week 8 Output**:
    - Display optimization output.

### Code
```cpp
int main() {
    vector<string> week_2_output = week_2_define_instructions();
    cout << "Week 2: Machine Code Output:" << endl;
    for (const auto& line : week_2_output) {
        cout << line << endl;
    }

    cout << "\nWeek 3: CPU Components Output:" << endl;
    vector<string> week_3_output = week_3_cpu_components();
    for (const auto& line : week_3_output) {
        cout << line << endl;
    }

    vector<string> week_4_output = week_4_execute_instructions();
    cout << "\nWeek 4: Execute Instructions Output:" << endl;
    for (const auto& line : week_4_output) {
        cout << line << endl;
    }

    vector<string> week_5_output = week_5_memory_management();
    cout << "\nWeek 5: Memory Management Output:" << endl;
    for (const auto& line : week_5_output) {
        cout << line << endl;
    }

    cout << "\nWeek 6: I/O Operations Output:" << endl;
    vector<string> week_6_output = week_6_io_operations();
    for (const auto& line : week_6_output) {
        cout << line << endl;
    }

    vector<string> week_7_output = week_7_advanced_features();
    cout << "\nWeek 7: Advanced Features Output:" << endl;
    for (const auto& line : week_7_output) {
        cout << line << endl;
    }

    vector<string> week_8_output = week_8_optimization();
    cout << "\nWeek 8: Optimization Output:" << endl;
    for (const auto& line : week_8_output) {
        cout << line << endl;
    }

    return 0;
}
```