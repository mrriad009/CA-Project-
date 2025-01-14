#ifndef CPU_H
#define CPU_H

#include "Registers.h"
#include "ALU.h"
#include "Memory.h"
#include <vector>
#include <iostream>
#include <bitset>
#include <string>

class CPU {
public:
    CPU(size_t memorySize) : programCounter(0), memory(memorySize), halted(false) {}

    void loadProgram(const std::vector<uint8_t>& program) {
        for (size_t i = 0; i < program.size(); ++i) {
            memory.write(i, program[i]);
        }
    }

    void executeProgram() {
        std::cout << "\n=== Starting Program Execution ===\n";

        while (programCounter < memory.size() && !halted) {
            std::cout << "\n--- Fetch-Decode-Execute Cycle ---\n";

            uint8_t instruction = fetch();
            uint8_t opcode, reg1, reg2;
            decode(instruction, opcode, reg1, reg2);
            execute(opcode, reg1, reg2);

            std::cout << "\nCurrent Register States: ";
            registers.display();

            std::cout << "\nCurrent Memory State: ";
            memory.display();
        }

        std::cout << "\n[Execution Complete]\n";
    }

private:
    uint8_t programCounter;
    Memory memory;
    Registers registers;
    ALU alu;
    bool halted;

    uint8_t fetch() {
        uint8_t instruction = memory.read(programCounter);
        std::cout << "Fetching instruction at address " << static_cast<int>(programCounter)
                  << ": " << static_cast<int>(instruction) << "\n";
        programCounter++;
        return instruction;
    }

    void decode(uint8_t instruction, uint8_t& opcode, uint8_t& reg1, uint8_t& reg2) {
        opcode = (instruction >> 6) & 0b00000011;
        reg1 = (instruction >> 3) & 0b00000111;
        reg2 = instruction & 0b00000111;

        std::string opcodeStr = getOpcodeString(opcode);
        std::cout << "Decoding instruction: " << static_cast<int>(instruction)
                  << " as (" << opcodeStr << " R" << reg1 << " R" << reg2 << ")\n";
    }

    void execute(uint8_t opcode, uint8_t reg1, uint8_t reg2) {
        std::string opcodeStr = getOpcodeString(opcode);

        if (opcodeStr == "HALT") {
            halted = true;
            std::cout << "HALT instruction encountered. Stopping execution.\n";
            return;
        }

        uint8_t operand1 = registers.get("R" + std::to_string(reg1));
        uint8_t operand2 = registers.get("R" + std::to_string(reg2));

        std::cout << "Operands: operand1 = " << static_cast<int>(operand1)
                  << ", operand2 = " << static_cast<int>(operand2) << "\n";

        uint8_t result = alu.performOperation(opcodeStr, operand1, operand2);

        if (opcodeStr == "STORE") {
            memory.write(operand2, operand1);
            std::cout << "Stored value " << static_cast<int>(operand1)
                      << " at memory address " << static_cast<int>(operand2) << "\n";
        } else {
            registers.set("R" + std::to_string(reg1), result);
        }
    }

    std::string getOpcodeString(uint8_t opcode) {
        switch (opcode) {
            case 0b00: return "ADD";
            case 0b01: return "SUB";
            case 0b10: return "LOAD";
            case 0b11: return "STORE";
            case 0b100: return "HALT";
            default: return "UNKNOWN";
        }
    }
};

#endif
