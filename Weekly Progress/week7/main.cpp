#include <iostream>
#include <fstream>
#include <sstream>
#include "CPU.h"
#include "Assembler.h"

int main() {
    CPU cpu;
    std::string assemblyCode;

    // Load assembly code from a file
    std::ifstream inputFile("input.txt");
    if (inputFile.is_open()) {
        std::string line;
        while (getline(inputFile, line)) {
            assemblyCode += line + "\n";
        }
        inputFile.close();
        std::cout << "Input loaded from input.txt" << std::endl;
    } else {
        std::cout << "Unable to open input.txt" << std::endl;
        return 1;
    }

    // Display Sample Assembly Code
    std::cout << "Sample Assembly Code:\n" << assemblyCode << std::endl;

    // Convert assembly to machine code
    std::cout << "\nAssembling code...\n";
    std::vector<int> machineCode = assemble(assemblyCode);
    std::cout << "Converted Machine Code:\n";
    for (int code : machineCode) {
        std::cout << code << " ";
    }
    std::cout << std::endl;

    // Display initial register states
    std::cout << "\nInitial Register States:\n";
    cpu.registers.display(std::cout);

    // Load and execute program
    cpu.loadProgram(machineCode);
    std::cout << "\nExecuting program...\n";

    // Redirect output to both console and file
    std::ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        std::ostringstream outputBuffer;
        cpu.executeProgram(outputBuffer);

        // Write buffer to file
        outputFile << outputBuffer.str();
        outputFile.close();

        std::cout << "Output saved in output.txt" << std::endl;
        std::cout << outputBuffer.str(); // Display buffer content to console
    } else {
        std::cout << "Unable to open output.txt" << std::endl;
    }

    // Display final register states
    std::cout << "Final Register States:\n";
    cpu.registers.display(std::cout);

    return 0;
}
