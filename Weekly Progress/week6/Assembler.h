#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <vector>
#include <string>
#include <iostream>
#include <bitset>

class Assembler {
public:
    static std::vector<int> assemble(const std::vector<std::string> &assembly_code) {
        std::vector<int> machine_code;
        for (const auto &line : assembly_code) {
            if (line == "IN R0") {
                machine_code.push_back(0b10000000); // IN R0
                std::cout << "[Assembler] Assembly: IN R0 -> Machine Code: " << std::bitset<8>(0b10000000) << std::endl;
            } else if (line == "OUT R0") {
                machine_code.push_back(0b10100000); // OUT R0
                std::cout << "[Assembler] Assembly: OUT R0 -> Machine Code: " << std::bitset<8>(0b10100000) << std::endl;
            } else {
                std::cerr << "[Assembler] Unknown instruction: " << line << std::endl;
            }
        }
        return machine_code;
    }
};

#endif