#ifndef REGISTERS_H
#define REGISTERS_H

#include <map>
#include <string>
#include <iostream>
#include <bitset>

class Registers {
public:
    Registers() {
        regs = {{"R0", 0b00000000}, {"R1", 0b00000100}, {"R2", 0b00001001}, {"R3", 0b00001010}};
    }

    uint8_t get(const std::string& reg) { return regs[reg]; }
    void set(const std::string& reg, uint8_t value) { regs[reg] = value; }
    void display() {
        std::cout << "=== Register States ===\n";
        for (const auto& reg : regs) {
            std::cout << reg.first << ": " << std::bitset<8>(reg.second) << "\n";
        }
        std::cout << "========================\n";
    }

private:
    std::map<std::string, uint8_t> regs;
};

#endif
