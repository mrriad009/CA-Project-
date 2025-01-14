// main.cpp
#include "CPU.h"
#include "Assembler.h"
#include <iostream>
#include <string>

int main() {
    CPU cpu;

    // Get assembly code input from the user
    std::string assemblyCode;
    std::cout << "Enter your assembly code (end with an empty line):" << std::endl;
    std::string line;
    while (std::getline(std::cin, line) && !line.empty()) {
        assemblyCode += line + "\n";
    }

    // Display the entered assembly code
    std::cout << "\n[Input Assembly Code]:\n" << assemblyCode << std::endl;

    // Convert assembly to machine code
    std::cout << "[Assembling Code...]\n";
    std::vector<uint8_t> machineCode = assemble(assemblyCode);

    // Display the generated machine code
    std::cout << "[Generated Machine Code]:\n";
    for (uint8_t code : machineCode) {
        std::cout << std::bitset<8>(code) << " ";
    }
    std::cout << "\n";

    // Load the program into the CPU
    cpu.loadProgram(machineCode);

    // Execute the program
    std::cout << "\n[Starting Program Execution...]\n";
    cpu.executeProgram();

    return 0;
}
