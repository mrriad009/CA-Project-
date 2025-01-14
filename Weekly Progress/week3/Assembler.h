// Assembler.h
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <sstream>
#include <vector>
#include <map>
#include <bitset>

std::vector<uint8_t> assemble(const std::string& assemblyCode) {
    std::map<std::string, uint8_t> registers = {{"R0", 0b000}, {"R1", 0b001}, {"R2", 0b010}, {"R3", 0b011}};
    std::istringstream iss(assemblyCode);
    std::string line;
    std::vector<uint8_t> machineCode;

    while (std::getline(iss, line)) {
        std::istringstream linestream(line);
        std::string opcode, reg1, reg2;
        linestream >> opcode >> reg1 >> reg2;
        uint8_t opcodeNum = (opcode == "ADD" ? 0b00 : opcode == "SUB" ? 0b01 : opcode == "LOAD" ? 0b10 : opcode == "STORE" ? 0b11 : 0b00);
        uint8_t machineInstruction = (opcodeNum << 6) | (registers[reg1] << 3) | registers[reg2];
        machineCode.push_back(machineInstruction);
    }

    return machineCode;
}

#endif
