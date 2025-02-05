#include <iostream>
#include <fstream>
#include <sstream>
#include "CPU.h"
#include "Assembler.h"

int main() {
    CPU cpu;
    std::string assemblyCode;

    std::cout << "Enter your assembly code (end with an empty line):\n";

    std::string line;
    while (std::getline(std::cin, line) && !line.empty()) {
        assemblyCode += line + "\n";
    }

    std::cout << "\n[Input Assembly Code]:\n" << assemblyCode << std::endl;

    std::cout << "[Assembling Code...]\n";
    std::vector<int> machineCode = assemble(assemblyCode);

    std::cout << "[Generated Machine Code]:\n";
    for (int code : machineCode) {
        std::cout << code << " ";
    }
    std::cout << "\n";

    cpu.loadProgram(machineCode);

    std::cout << "\n[Starting Program Execution...]\n";
    cpu.executeProgram(std::cout);

    return 0;
}
