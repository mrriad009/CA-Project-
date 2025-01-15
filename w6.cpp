#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

// Enum for instruction types
enum InstructionType { ADD, SUB, LOAD, STORE, INPUT, OUTPUT, UNKNOWN };

// ALU class
class ALU {
public:
    int performOperation(const string& opcode, int operand1, int operand2) {
        if (opcode == "ADD") return operand1 + operand2;
        if (opcode == "SUB") return operand1 - operand2;
        if (opcode == "LOAD") return operand2;
        if (opcode == "STORE") return operand1;
        return 0;
    }
};

// General-purpose registers class
class Registers {
public:
    map<string, int> regs;
    Registers() {
        regs["R0"] = 0; regs["R1"] = 4; regs["R2"] = 9; regs["R3"] = 10;
    }
    int get(const string& reg) { return regs[reg]; }
    void set(const string& reg, int value) { regs[reg] = value; }
    void display(ostream& outputStream) {
        for (const auto& reg : regs) {
            outputStream << reg.first << ": " << reg.second << " ";
        }
        outputStream << endl;
    }
};

// Memory management class
class Memory {
public:
    vector<int> memorySpace;
    Memory(int size) : memorySpace(size, 0) {}
    int read(int address) {
        if (address < 0 || address >= memorySpace.size()) {
            cout << "Memory read error: Address out of bounds" << endl;
            return -1;
        }
        return memorySpace[address];
    }
    void write(int address, int value) {
        if (address < 0 || address >= memorySpace.size()) {
            cout << "Memory write error: Address out of bounds" << endl;
            return;
        }
        cout << "Writing value " << value << " to memory address " << address << endl;
        memorySpace[address] = value;
    }
    void display(ostream& outputStream) {
        for (int i = 0; i < memorySpace.size(); ++i) {
            outputStream << "Address " << i << ": " << memorySpace[i] << " ";
        }
        outputStream << endl;
    }
};

// CPU class
class CPU {
public:
    int programCounter;
    vector<int> instructionMemory;
    Registers registers;
    ALU alu;
    Memory memory;

    CPU() : programCounter(0), memory(25) {} // Initialize with memory size 25
    void loadProgram(const vector<int>& program) {
        instructionMemory = program;
    }
    void executeProgram(ostream& outputStream) {
        while (programCounter < instructionMemory.size()) {
            int instruction = instructionMemory[programCounter];
            outputStream << "Fetching instruction at address " << programCounter << ": " << instruction << endl;
            programCounter++;
            decodeAndExecute(instruction, outputStream);
        }
    }

private:
    void decodeAndExecute(int instruction, ostream& outputStream) {
        int opcode = (instruction >> 6) & 0x03;
        int reg1 = (instruction >> 3) & 0x07;
        int reg2 = instruction & 0x07;
        string opcodeStr = getOpcodeString(opcode);

        outputStream << "Decoding instruction: " << instruction << " as (" << opcodeStr << " R" << reg1 << " R" << reg2 << ")" << endl;

        int operand1 = registers.get("R" + to_string(reg1));
        int operand2 = registers.get("R" + to_string(reg2));

        outputStream << "Operands: " << "operand1 = " << operand1 << ", operand2 = " << operand2 << endl;

        if (opcodeStr == "INPUT") {
            int value;
            cout << "Enter value for R" << reg1 << ": ";
            cin >> value;
            registers.set("R" + to_string(reg1), value);
            outputStream << "Input value " << value << " into R" << reg1 << endl;
        } else if (opcodeStr == "OUTPUT") {
            int value = registers.get("R" + to_string(reg1));
            cout << "Output value from R" << reg1 << ": " << value << endl;
            outputStream << "Output value from R" << reg1 << ": " << value << endl;
        } else {
            int result = alu.performOperation(opcodeStr, operand1, operand2);
            if (opcodeStr == "LOAD") {
                int value = memory.read(operand2);
                registers.set("R" + to_string(reg1), value);
                outputStream << "Loaded value " << value << " into R" << reg1 << endl;
            } else if (opcodeStr == "STORE") {
                memory.write(operand2, operand1);
                outputStream << "Stored value " << operand1 << " at memory address " << operand2 << endl;
            } else {
                registers.set("R" + to_string(reg1), result);
                outputStream << "Executing instruction: " << instruction << " (" << opcodeStr << " R" << reg1 << " R" << reg2 << ")" << endl;
                outputStream << "Updated R" << reg1 << " to " << result << endl;
            }
        }

        outputStream << "Current Register States: ";
        registers.display(outputStream);
        outputStream << "Current Memory State: ";
        memory.display(outputStream);
        outputStream << endl;
    }

    string getOpcodeString(int opcode) {
        switch (opcode) {
            case 0: return "ADD";
            case 1: return "SUB";
            case 2: return "LOAD";
            case 3: return "STORE";
            case 4: return "INPUT";
            case 5: return "OUTPUT";
            default: return "UNKNOWN";
        }
    }
};

// Assembler function
vector<int> assemble(const string& assemblyCode) {
    map<string, int> opcodes = {{"ADD", 0}, {"SUB", 1}, {"LOAD", 2}, {"STORE", 3}, {"INPUT", 4}, {"OUTPUT", 5}};
    map<string, int> registers = {{"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3}};
    istringstream iss(assemblyCode);
    string line;
    vector<int> machineCode;
    while (getline(iss, line)) {
        istringstream linestream(line);
        string opcode, reg1, reg2;
        linestream >> opcode >> reg1 >> reg2;
        int machineInstruction = (opcodes[opcode] << 6) | (registers[reg1] << 3) | registers[reg2];
        machineCode.push_back(machineInstruction);
    }
    return machineCode;
}

int main() {
    CPU cpu;
    string assemblyCode;

    // Load assembly code from a file
    ifstream inputFile("input.txt");
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            assemblyCode += line + "\n";
        }
        inputFile.close();
        cout << "Input loaded from input.txt" << endl;
    } else {
        cout << "Unable to open input.txt" << endl;
        return 1;
    }

    cout << "Sample Assembly Code:\n" << assemblyCode << endl;

    // Convert assembly to machine code
    cout << "\nAssembling code...\n";
    vector<int> machineCode = assemble(assemblyCode);
    cout << "Converted Machine Code:\n";
    for (int code : machineCode) {
        cout << code << " ";
    }
    cout << endl;

    // Display initial register states
    cout << "\nInitial Register States:\n";
    cpu.registers.display(cout);

    // Load and execute program
    cpu.loadProgram(machineCode);
    cout << "\nExecuting program...\n";

    // Redirect output to both console and file
    ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        ostringstream outputBuffer;
        cpu.executeProgram(outputBuffer);

        // Write buffer to file
        outputFile << outputBuffer.str();
        outputFile.close();

        cout << "Output saved in output.txt" << endl;
        cout << outputBuffer.str(); // Display buffer content to console
    } else {
        cout << "Unable to open output.txt" << endl;
    }

    // Display final register states
    cout << "Final Register States:\n";
    cpu.registers.display(cout);

    return 0;
}