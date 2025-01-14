#include "CPU.h"
#include "Assembler.h"
#include <iostream>
#include <string>

int main() {
    CPU cpu(128); // Initialize CPU with 128 bytes of memory

    std::string assemblyCode;
    std::cout << "Enter your assembly code (end with an empty line):" << std::endl;
    std::string line;
    while (std::getline(std::cin, line) && !line.empty()) {
        assemblyCode += line + "\n";
    }

    std::cout << "\n[Input Assembly Code]:\n" << assemblyCode << std::endl;

    std::vector<uint8_t> machineCode = assemble(assemblyCode);

    std::cout << "[Generated Machine Code]:\n";
    for (uint8_t code : machineCode) {
        std::cout << std::bitset<8>(code) << " ";
    }
    std::cout << "\n";

    cpu.loadProgram(machineCode);
    cpu.executeProgram();

    return 0;
}
