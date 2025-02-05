#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <chrono>
#include <unordered_map>

using namespace std;

// Enum for instruction types
enum InstructionType { ADD, SUB, LOAD, STORE, INPUT, OUTPUT, JUMP, CALL, RET, UNKNOWN };

// ALU class for arithmetic and logical operations
class ALU {
public:
    int executeOperation(const string& opcode, int operand1, int operand2) {
        if (opcode == "ADD") return operand1 + operand2;
        if (opcode == "SUB") return operand1 - operand2;
        if (opcode == "LOAD") return operand2;
        if (opcode == "STORE") return operand1;
        return 0;
    }
};

// Class for general-purpose registers
class Registers {
public:
    unordered_map<string, int> regs;
    Registers() {
        regs["R0"] = 0; regs["R1"] = 4; regs["R2"] = 9; regs["R3"] = 10;
    }
    int get(const string& reg) { return regs[reg]; }
    void set(const string& reg, int value) { regs[reg] = value; }
    void display() const {
        for (const auto& reg : regs) {
            cout << reg.first << ": " << reg.second << " ";
        }
        cout << endl;
    }
};

// Class for memory management
class Memory {
public:
    vector<int> memorySpace;
    Memory(int size) : memorySpace(size, 0) {}
    int read(int address) {
        if (address < 0 || address >= memorySpace.size()) {
            cout << "Error: Address out of bounds during read." << endl;
            return -1;
        }
        return memorySpace[address];
    }
    void write(int address, int value) {
        if (address < 0 || address >= memorySpace.size()) {
            cout << "Error: Address out of bounds during write." << endl;
            return;
        }
        cout << "Writing value " << value << " to address " << address << endl;
        memorySpace[address] = value;
    }
    void display() const {
        for (int i = 0; i < memorySpace.size(); ++i) {
            cout << "Addr " << i << ": " << memorySpace[i] << " ";
        }
        cout << endl;
    }
};

// CPU class to simulate the execution of a program
class CPU {
public:
    int programCounter;
    vector<int> instructionMemory;
    Registers registers;
    ALU alu;
    Memory memory;

    CPU() : programCounter(0), memory(25) {} // Initialize memory size to 25
    void loadProgram(const vector<int>& program) {
        instructionMemory = program;
    }
    void executeProgram() {
        while (programCounter < instructionMemory.size()) {
            int instruction = instructionMemory[programCounter];
            cout << "\nFetching instruction at address " << programCounter << ": " << instruction << endl;
            programCounter++;
            decodeAndExecute(instruction);
        }
    }

private:
    void decodeAndExecute(int instruction) {
        int opcode = (instruction >> 6) & 0x03;
        int reg1 = (instruction >> 3) & 0x07;
        int reg2 = instruction & 0x07;
        string opcodeStr = getOpcodeString(opcode);

        cout << "Decoding: " << opcodeStr << " R" << reg1 << " R" << reg2 << endl;

        int operand1 = registers.get("R" + to_string(reg1));
        int operand2 = registers.get("R" + to_string(reg2));

        cout << "Operands: " << "R" << reg1 << " = " << operand1 << ", R" << reg2 << " = " << operand2 << endl;

        if (opcodeStr == "INPUT") {
            int value;
            cout << "Enter a value for R" << reg1 << ": ";
            cin >> value;
            registers.set("R" + to_string(reg1), value);
        } else if (opcodeStr == "OUTPUT") {
            int value = registers.get("R" + to_string(reg1));
            cout << "Output value from R" << reg1 << ": " << value << endl;
        } else if (opcodeStr == "JUMP") {
            programCounter = operand2;
            cout << "Jumping to address " << operand2 << endl;
        } else if (opcodeStr == "CALL") {
            memory.write(memory.memorySpace.size() - 1, programCounter);
            programCounter = operand2;
            cout << "Calling subroutine at address " << operand2 << endl;
        } else if (opcodeStr == "RET") {
            programCounter = memory.read(memory.memorySpace.size() - 1);
            cout << "Returning from subroutine to address " << programCounter << endl;
        } else {
            int result = alu.executeOperation(opcodeStr, operand1, operand2);
            if (opcodeStr == "LOAD") {
                int value = memory.read(operand2);
                registers.set("R" + to_string(reg1), value);
                cout << "Loaded value " << value << " into R" << reg1 << endl;
            } else if (opcodeStr == "STORE") {
                memory.write(operand2, operand1);
                cout << "Stored value " << operand1 << " at memory address " << operand2 << endl;
            } else {
                registers.set("R" + to_string(reg1), result);
                cout << "Executing " << opcodeStr << ": R" << reg1 << " = " << result << endl;
            }
        }

        cout << "\nRegisters: ";
        registers.display();
        cout << "Memory: ";
        memory.display();
    }

    string getOpcodeString(int opcode) {
        switch (opcode) {
            case 0: return "ADD";
            case 1: return "SUB";
            case 2: return "LOAD";
            case 3: return "STORE";
            case 4: return "INPUT";
            case 5: return "OUTPUT";
            case 6: return "JUMP";
            case 7: return "CALL";
            case 8: return "RET";
            default: return "UNKNOWN";
        }
    }
};

// Function to assemble assembly code into machine code
vector<int> assemble(const string& assemblyCode) {
    map<string, int> opcodes = {{"ADD", 0}, {"SUB", 1}, {"LOAD", 2}, {"STORE", 3}, {"INPUT", 4}, {"OUTPUT", 5}, {"JUMP", 6}, {"CALL", 7}, {"RET", 8}};
    map<string, int> registers = {{"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3}};
    istringstream iss(assemblyCode);
    string line;
    vector<int> machineCode;
    
    // Optimized instruction encoding
    while (getline(iss, line)) {
        istringstream linestream(line);
        string opcode, reg1, reg2;
        
        // Only process valid instructions
        if (!(linestream >> opcode >> reg1 >> reg2)) {
            continue; // Skip invalid or empty lines
        }
        
        int encodedInstruction = (opcodes[opcode] << 6) | (registers[reg1] << 3) | registers[reg2];
        machineCode.push_back(encodedInstruction);
    }
    
    return machineCode;
}

// Function to load the assembly code from a file
string loadAssemblyCode(const string& filename) {
    ifstream inputFile(filename);
    string assemblyCode;
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            assemblyCode += line + "\n";
        }
        inputFile.close();
        cout << "Assembly Code Loaded from " << filename << endl;
    } else {
        cout << "Error: Unable to open " << filename << endl;
    }
    return assemblyCode;
}

// Function to execute the program with the given machine code
void executeProgram(CPU& cpu, const vector<int>& machineCode) {
    cpu.loadProgram(machineCode);
    cout << "\nExecuting Program...\n";
    cpu.executeProgram();
}

// Profiling function to measure execution time
void profileExecution() {
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
}

int main() {
    profileExecution();
    return 0;
}
