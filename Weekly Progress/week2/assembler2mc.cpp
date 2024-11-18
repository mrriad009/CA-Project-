#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

// Define instruction and register sets
map<string, string> instructionSet = {
    {"MOV", "0001"},
    {"ADD", "0010"},
    {"SUB", "0011"},
    {"JMP", "0100"}
};

map<string, string> registerSet = {
    {"R0", "000"},
    {"R1", "001"},
    {"R2", "010"},
    {"R3", "011"},
    {"R4", "100"},
    {"R5", "101"},
    {"R6", "110"},
    {"R7", "111"}
};

// Function to convert an instruction line to machine code
string convertToMachineCode(const string &line) {
    istringstream ss(line);
    string instruction, operand1, operand2;
    ss >> instruction >> operand1 >> operand2;

    // Check if instruction exists in instructionSet
    if (instructionSet.find(instruction) == instructionSet.end()) {
        return "Error: Unknown instruction '" + instruction + "'";
    }

    // Retrieve the opcode
    string opcode = instructionSet[instruction];

    // Retrieve the register codes
    string reg1 = registerSet[operand1];
    string reg2 = (operand2.empty()) ? "000" : registerSet[operand2];

    // Return the final machine code in binary format
    return opcode + reg1 + reg2;
}

int main() {
    vector<string> assemblyCode = {
        "MOV R1 R2",
        "ADD R2 R3",
        "SUB R3 R1",
        "JMP R4   "
    };

    cout << "Assembly Code to Machine Code Conversion:\n";
    for (const string &line : assemblyCode) {
        string machineCode = convertToMachineCode(line);
        // Output the result directly with std::cout
        cout << line << " -> " << machineCode << endl;
    }

    return 0;
}