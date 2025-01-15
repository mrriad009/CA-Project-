#include "Memory.h"
#include "CPU.h"
#include "Assembler.h"
#include <vector>
#include <string>
#include <iostream>
#include <bitset>

int main() {
    Memory memory(16);
    memory.print_segments();

    std::cout << "Enter your assembly code (end with an empty line):" << std::endl;
    std::vector<std::string> assembly_code;
    std::string line;
    while (std::getline(std::cin, line) && !line.empty()) {
        assembly_code.push_back(line);
    }

    std::cout << "\n[Input Assembly Code]:" << std::endl;
    for (const auto &line : assembly_code) {
        std::cout << line << std::endl;
    }

    std::cout << "\n[Assembling Code...]" << std::endl;
    std::vector<int> machine_code = Assembler::assemble(assembly_code);

    std::cout << "\n[Generated Machine Code]:" << std::endl;
    for (const auto &code : machine_code) {
        std::cout << std::bitset<8>(code) << " ";
    }
    std::cout << std::endl;

    CPU cpu(memory);
    cpu.load_program(machine_code);
    cpu.execute();

    return 0;
}