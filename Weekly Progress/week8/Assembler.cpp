#include "Assembler.h"

std::vector<int> assemble(const std::string& assemblyCode) {
    static const std::map<std::string, int> opcodes = {
        {"ADD", 0}, {"SUB", 1}, {"MUL", 2}, {"DIV", 3}, {"CMP", 4},
        {"SHL", 5}, {"SHR", 6}, {"LOAD", 7}, {"STORE", 8}
    };
    static const std::map<std::string, int> registers = {
        {"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3}
    };

    std::istringstream iss(assemblyCode);
    std::string line;
    std::vector<int> machineCode;

    while (getline(iss, line)) {
        std::istringstream linestream(line);
        std::string opcode, reg1, reg2;
        linestream >> opcode >> reg1 >> reg2;

        int machineInstruction = (opcodes.at(opcode) << 6) | (registers.at(reg1) << 3) | registers.at(reg2);
        machineCode.push_back(machineInstruction);
    }

    return machineCode;
}
