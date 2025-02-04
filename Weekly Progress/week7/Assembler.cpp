#include "Assembler.h"
#include <map>
#include <sstream>

std::vector<int> assemble(const std::string& assemblyCode) {
    std::map<std::string, int> opcodes = {{"ADD", 0}, {"SUB", 1}, {"LOAD", 2}, {"STORE", 3}, {"INPUT", 4}, {"OUTPUT", 5}, {"JUMP", 6}, {"CALL", 7}, {"RET", 8}};
    std::map<std::string, int> registers = {{"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3}};
    std::istringstream iss(assemblyCode);
    std::string line;
    std::vector<int> machineCode;

    while (getline(iss, line)) {
        std::istringstream linestream(line);
        std::string opcode, reg1, reg2;
        linestream >> opcode >> reg1 >> reg2;
        int machineInstruction = (opcodes[opcode] << 6) | (registers[reg1] << 3) | registers[reg2];
        machineCode.push_back(machineInstruction);
    }

    return machineCode;
}
