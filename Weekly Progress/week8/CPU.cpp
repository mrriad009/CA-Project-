#include "CPU.h"

CPU::CPU() : programCounter(0), memory(25) {}

void CPU::loadProgram(const std::vector<int>& program) {
    instructionMemory = program;
}

void CPU::executeProgram(std::ostream& outputStream) {
    while (programCounter < instructionMemory.size()) {
        outputStream << "Program Counter: " << programCounter << std::endl;
        int instruction = instructionMemory[programCounter];
        outputStream << "Fetching instruction at address " << programCounter << ": " << instruction << std::endl;
        programCounter++;
        decodeAndExecute(instruction, outputStream);
    }
}

void CPU::decodeAndExecute(int instruction, std::ostream& outputStream) {
    // Optimized opcode lookup using an array
    int opcode = (instruction >> 6) & 0x03;  // Adjust opcode extraction for 6-bit opcode
    int reg1 = (instruction >> 3) & 0x07;
    int reg2 = instruction & 0x07;

    static const std::string opcodeStrings[] = {
        "ADD", "SUB", "MUL", "DIV", "CMP", "SHL", "SHR", "LOAD", "STORE"
    };

    std::string opcodeStr = opcodeStrings[opcode];

    int operand1 = registers.get("R" + std::to_string(reg1));
    int operand2 = registers.get("R" + std::to_string(reg2));

    if (opcodeStr == "MUL" || opcodeStr == "DIV" || opcodeStr == "CMP" || opcodeStr == "SHL" || opcodeStr == "SHR") {
        int result = alu.performOperation(opcodeStr, operand1, operand2);
        registers.set("R" + std::to_string(reg1), result);
        outputStream << "Executed instruction: " << opcodeStr << " R" << reg1 << " R" << reg2 << std::endl;
        outputStream << "Updated R" << reg1 << " to " << result << std::endl;
    } 
    // Other instruction cases...
    else {
        int result = alu.performOperation(opcodeStr, operand1, operand2);
        registers.set("R" + std::to_string(reg1), result);
        outputStream << "Executing instruction: " << instruction << " (" << opcodeStr << " R" << reg1 << " R" << reg2 << ")" << std::endl;
        outputStream << "Updated R" << reg1 << " to " << result << std::endl;
    }

    outputStream << "Current Register States: ";
    registers.display(outputStream);
    outputStream << "Current Memory State: ";
    memory.display(outputStream);
    outputStream << std::endl;
}

std::string CPU::getOpcodeString(int opcode) {
    // Optimized with an array lookup
    static const std::string opcodeStrings[] = {
        "ADD", "SUB", "MUL", "DIV", "CMP", "SHL", "SHR", "LOAD", "STORE"
    };
    return opcodeStrings[opcode];
}
