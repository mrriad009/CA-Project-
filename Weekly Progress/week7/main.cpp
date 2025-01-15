#include "CPU.h"
#include "Assembler.h"
#include <iostream>
#include <string>
#include "Assembler.h"


int main() {
    CPU cpu;

    std::string assemblyCode;
    std::cout << "Enter your assembly code (end with an empty line):" << std::endl;
    std::string line;
    while (std::getline(std::cin, line) && !line.empty()) {
        assemblyCode += line + "\n";
    }

    std::cout << "\n[Input Assembly Code]:\n" << assemblyCode << std::endl;

    std::cout << "[Assembling Code...]\n";
    std::vector<uint8_t> machineCode = assemble(assemblyCode);

    std::cout << "[Generated Machine Code]:\n";
    for (uint8_t code : machineCode) {
        std::cout << std::bitset<8>(code) << " ";
    }
    std::cout << "\n";

    cpu.loadProgram(machineCode);

    std::cout << "\n[Starting Program Execution...]\n";
    cpu.executeProgram();

    return 0;
}
