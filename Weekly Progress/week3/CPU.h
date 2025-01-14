// CPU.h
#ifndef CPU_H
#define CPU_H

#include "ALU.h"
#include "Registers.h"
#include <vector>
#include <iostream>
#include <bitset>

class CPU {
public:
    CPU() : programCounter(0b00000000) {}

    void loadProgram(const std::vector<uint8_t>& program) {
        instructionMemory = program;
    }

    void executeProgram() {
        while (programCounter < instructionMemory.size()) {
            uint8_t instruction = instructionMemory[programCounter++];
            uint8_t opcode = (instruction >> 6) & 0b00000011;
            uint8_t reg1 = (instruction >> 3) & 0b00000111;
            uint8_t reg2 = instruction & 0b00000111;

            std::string opcodeStr = getOpcodeString(opcode);
            uint8_t operand1 = registers.get("R" + std::to_string(reg1));
            uint8_t operand2 = registers.get("R" + std::to_string(reg2));
            uint8_t result = alu.performOperation(opcodeStr, operand1, operand2);

            registers.set("R" + std::to_string(reg1), result);

            // Output with machine code
            std::cout << "\n[Instruction]: " << std::bitset<8>(instruction)
                      << " (" << opcodeStr << " R" << reg1 << ", R" << reg2 << ")\n";
            std::cout << "=> Updated R" << reg1 << ": " << std::bitset<8>(result) << "\n";
            registers.display();
        }
        std::cout << "\n[Execution Complete]\n";
    }

private:
    uint8_t programCounter;
    std::vector<uint8_t> instructionMemory;
    Registers registers;
    ALU alu;

    std::string getOpcodeString(uint8_t opcode) {
        switch (opcode) {
            case 0b00: return "ADD";
            case 0b01: return "SUB";
            case 0b10: return "LOAD";
            case 0b11: return "STORE";
            default: return "UNKNOWN";
        }
    }
};

#endif
