#include "Registers.h"

Registers::Registers() {
    regs["R0"] = 0; regs["R1"] = 4; regs["R2"] = 9; regs["R3"] = 10;
}

int Registers::get(const std::string& reg) {
    return regs[reg];
}

void Registers::set(const std::string& reg, int value) {
    regs[reg] = value;
}

void Registers::display(std::ostream& outputStream) {
    for (const auto& reg : regs) {
        outputStream << reg.first << ": " << reg.second << " ";
    }
    outputStream << std::endl;
}
