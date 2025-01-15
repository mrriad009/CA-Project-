#ifndef CPU_H
#define CPU_H

#include "ALU.h"
#include "Registers.h"
#include "Memory.h"
#include <iostream>
#include <bitset>

class CPU {
public:
    CPU() : programCounter(0b00000000), memory(16) { // 16 bytes memory
        memory.segmentInfo(); // Display memory segmentation details
    }

    void loadProgram(const std::vector<uint8_t>& program) {
        std::cout << "[Loading Program into Memory]\n";
        for (size_t i = 0; i < program.size(); ++i) {
            memory.write(i, program[i]);
        }
    }

    void executeProgram() {
        std::cout << "\n=== Starting Program Execution ===\n";

        while (programCounter < 16) {
            std::cout << "\n--- Fetch-Decode-Execute Cycle ---\n";

            // Fetch
            uint8_t instruction = memory.read(programCounter++);

            // Decode
            uint8_t opcode, reg1, reg2;
            decode(instruction, opcode, reg1, reg2);

            // Execute
            execute(opcode, reg1, reg2);
        }

        std::cout << "\n[Execution Complete]\n";
    }

private:
    uint8_t programCounter;
    Memory memory; // Memory module instance
    Registers registers;
    ALU alu;

    void decode(uint8_t instruction, uint8_t& opcode, uint8_t& reg1, uint8_t& reg2) {
        opcode = (instruction >> 6) & 0b00000011;
        reg1 = (instruction >> 3) & 0b00000111;
        reg2 = instruction & 0b00000111;

        std::cout << "[Decode] Opcode: " << std::bitset<2>(opcode)
                  << ", Reg1: R" << reg1
                  << ", Reg2: R" << reg2 << "\n";
    }

    void execute(uint8_t opcode, uint8_t reg1, uint8_t reg2) {
        std::string opcodeStr = getOpcodeString(opcode);

        uint8_t operand1 = registers.get("R" + std::to_string(reg1));
        uint8_t operand2 = registers.get("R" + std::to_string(reg2));
        uint8_t result;

        if (opcodeStr == "LOAD") {
            result = memory.read(operand2); // Load from memory
        } else if (opcodeStr == "STORE") {
            memory.write(operand2, operand1); // Store to memory
            result = operand1; // No modification to register
        } else {
            result = alu.performOperation(opcodeStr, operand1, operand2);
        }

        registers.set("R" + std::to_string(reg1), result);

        std::cout << "[Execute] " << opcodeStr
                  << " R" << reg1 << ", R" << reg2
                  << " => Updated R" << reg1 << ": " << std::bitset<8>(result) << "\n";
        registers.display();
    }

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
