#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>

using namespace std;

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

string assemble(const string &instruction) {
    istringstream iss(instruction);
    string opcode, R1, R2, R3;
    iss >> opcode >> R1 >> R2 >> R3;

    if (instructionSet.find(opcode) == instructionSet.end()) {
        return "Error: Invalid Instruction";
    }

    string binaryCode = instructionSet[opcode];

    // Construct binary code for specific instruction types
    if (opcode == "ADD" || opcode == "SUB") {
        binaryCode += " " + R1 + " " + R2 + " " + R3;
    } else if (opcode == "LOAD" || opcode == "STORE") {
        binaryCode += " " + R1 + " " + R2; // R1 and memory address
    } else if (opcode == "JUMP" || opcode == "JZ" || opcode == "JNZ") {
        binaryCode += " " + R1; // Only address
    } else if (opcode == "READ" || opcode == "WRITE") {
        binaryCode += " " + R1; // Only register
    }

    return binaryCode;
}

int main() {
    vector<string> testInstructions = {
        "ADD R1 R2 R3",
        "SUB R4 R5 R6",
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
