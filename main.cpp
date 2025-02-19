#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <ctime>
#include <unordered_map>
#include <sstream>

using namespace std;

// Week 2: Define ISA and create an assembler to convert assembly to machine code
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

    // Example assembly instructions
    vector<string> instructions = {"ADD R1 10", "SUB R2 5", "LOAD R1 20", "STORE R2 15"};
    vector<string> machine_code;
    
    for (const auto& inst : instructions) {
        machine_code.push_back(assembler(inst));
    }
    
    return machine_code;
}

// Week 3: Build basic CPU components
vector<string> week_3_cpu_components() {
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

    class Registers {
    public:
        vector<int> regs = {0, 0, 0, 0}; // Four 6-bit registers

        void write(int reg_num, int value) {
            regs[reg_num] = value;
        }

        int read(int reg_num) {
            return regs[reg_num];
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

// Week 4: Implement fetch-decode-execute cycle
vector<string> week_4_execute_instructions() {
    vector<string> memory = {"LOAD R1 10", "ADD R1 R2", "STORE R1 20"};
    unordered_map<string, int> registers = {{"R1", 0}, {"R2", 5}};
    int pc = 0;
    
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

// Week 5: Memory Management
vector<string> week_5_memory_management() {
    vector<int> memory(16, 0); // 16 memory locations
    
    auto write_memory = [&](int address, int value) {
        memory[address] = value;
    };

    auto read_memory = [&](int address) {
        return memory[address];
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

// Week 6: I/O Operations
vector<string> week_6_io_operations() {
    unordered_map<string, string> io_devices = {{"keyboard", "00000000"}, {"display", "00000000"}};

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

    read_input("keyboard");
    io_devices["display"] = io_devices["keyboard"]; // Copy keyboard input to display

    vector<string> result;
    result.push_back(write_output("display"));
    return result;
}

// Week 7: Advanced Features
vector<string> week_7_advanced_features() {
    vector<string> memory = {"011000000001", "000101000001", "111100000000"};  // Branch to 1, ADD, HALT
    vector<int> registers(4, 0);
    int pc = 0;

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

// Week 8: Performance Optimization
vector<string> week_8_optimization() {
    vector<string> memory = {"000101000010", "001010000001", "111100000000"}; // ADD, SUB, HALT
    vector<int> registers(4, 0);
    int pc = 0;

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
    
    for (int i = 0; i < registers.size(); ++i) {
        result.push_back("R" + to_string(i) + ": " + bitset<6>(registers[i]).to_string());
    }

    return result;
}



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


