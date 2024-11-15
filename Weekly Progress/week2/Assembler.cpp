#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <bitset>

using namespace std;

// Instruction Set with binary opcodes
unordered_map<string, string> instructionSet = {
    {"ADD", "0001"},
    {"SUB", "0010"},
    {"LOAD", "0011"},
    {"STORE", "0100"},
    {"JUMP", "0101"},
    {"JZ", "0110"},
    {"JNZ", "0111"},
    {"READ", "1000"},
    {"WRITE", "1001"}
};

// Register encoding (R0 to R7 as 3-bit binary)
unordered_map<string, string> registerMap = {
    {"R0", "000"},
    {"R1", "001"},
    {"R2", "010"},
    {"R3", "011"},
    {"R4", "100"},
    {"R5", "101"},
    {"R6", "110"},
    {"R7", "111"}
};

// Convert a string number (e.g., "100") to an 8-bit binary representation
string toBinary8(int number) {
    return bitset<8>(number).to_string();
}

// Function to check if a string is a valid register
bool isRegister(const string& operand) {
    return registerMap.find(operand) != registerMap.end();
}

string assemble(const string &instruction) {
    istringstream iss(instruction);
    string opcode, R1, R2;
    iss >> opcode;

    // Check for valid opcode
    if (instructionSet.find(opcode) == instructionSet.end()) {
        return "Error: Invalid Instruction";
    }

    // Start with opcode's binary representation
    string binaryCode = instructionSet[opcode];

    // Handle ADD, SUB (two registers)
    if (opcode == "ADD" || opcode == "SUB") {
        iss >> R1 >> R2;
        if (!isRegister(R1) || !isRegister(R2)) {
            return "Error: Invalid register in operands";
        }
        string reg1 = registerMap[R1];
        string reg2 = registerMap[R2];
        binaryCode += " " + reg1 + " " + reg2;
    }
    // Handle LOAD, STORE (one register and one address)
    else if (opcode == "LOAD" || opcode == "STORE") {
        iss >> R1 >> R2;
        if (!isRegister(R1)) {
            return "Error: Invalid register in operand";
        }
        string reg = registerMap[R1];
        string address = toBinary8(stoi(R2));  // Convert address to 8-bit binary
        binaryCode += " " + reg + " " + address;
    }
    // Handle JUMP, JZ, JNZ (one address or register)
    else if (opcode == "JUMP" || opcode == "JZ" || opcode == "JNZ") {
        iss >> R1;
        string address;
        // For JUMP, JZ, and JNZ, the operand could be a register or an address
        if (isRegister(R1)) {
            address = registerMap[R1];
        } else {
            address = toBinary8(stoi(R1));  // Convert address to 8-bit binary
        }
        binaryCode += " " + address;
    }
    // Handle READ and WRITE (one register)
    else if (opcode == "READ" || opcode == "WRITE") {
        iss >> R1;
        if (!isRegister(R1)) {
            return "Error: Invalid register in operand";
        }
        string reg = registerMap[R1];
        binaryCode += " " + reg;
    }

    return binaryCode;
}

int main() {
    vector<string> testInstructions = {
        "ADD R1 R2",
        "SUB R4 R5",
        "LOAD R1 100",
        "STORE R2 200",
        "JUMP 300",
        "JZ R1 400",
        "WRITE R2"
    };

    for (const auto &instruction : testInstructions) {
        cout << "Assembly: " << instruction << "\n";
        cout << "Machine Code: " << assemble(instruction) << "\n\n";
    }

    return 0;
}
