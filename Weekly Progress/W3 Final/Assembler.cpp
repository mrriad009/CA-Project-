#include "Assembler.h"

std::string Assembler::assemblerToMachineCode(const std::string& instruction) {
    if (instruction == "ADD") {
        return std::bitset<8>(0b00000000).to_string();  // ADD opcode: 0b00000000
    } else if (instruction == "SUB") {
        return std::bitset<8>(0b00000001).to_string();  // SUB opcode: 0b00000001
    } else {
        return "Unknown";  // for any undefined instructions
    }
}
