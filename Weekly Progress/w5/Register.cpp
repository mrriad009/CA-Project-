#include "ALU.h"

#ifndef REGISTERS_H
#define REGISTERS_H

#include <map>
#include <string>
#include <iostream>

class Registers {
public:
    std::map<std::string, int> regs;
    Registers() {
        regs["R0"] = 0; regs["R1"] = 4; regs["R2"] = 9; regs["R3"] = 10;
    }
    int get(const std::string& reg) { return regs[reg]; }
    void set(const std::string& reg, int value) { regs[reg] = value; }
    void display(std::ostream& outputStream) {
        for (const auto& reg : regs) {
            outputStream << reg.first << ": " << reg.second << " ";
        }
        outputStream << std::endl;
    }
};

#endif