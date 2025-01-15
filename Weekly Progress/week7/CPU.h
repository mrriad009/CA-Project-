#ifndef CPU_H
#define CPU_H

#include "ALU.h"
#include "Registers.h"
#include "Memory.h"
#include <iostream>
#include <bitset>

class CPU {
public:
    CPU() : programCounter(0b00000000), stackPointer(0b00001111), memory(16) { // 16 bytes memory
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
            if_id = memory.read(programCounter++);

            // Decode
            decode(if_id, id_ex_opcode, id_ex_reg1, id_ex_reg2);

            // Execute
            execute(id_ex_opcode, id_ex_reg1, id_ex_reg2);
        }

        std::cout << "\n[Execution Complete]\n";
    }

private:
    uint8_t programCounter;
    uint8_t stackPointer;
    Memory memory;
    Registers registers;
    ALU alu;

    uint8_t if_id;  // Fetch-Decode pipeline register
    uint8_t id_ex_opcode, id_ex_reg1, id_ex_reg2; // Decode-Execute pipeline registers

    void decode(uint8_t instruction, uint8_t& opcode, uint8_t& reg1, uint8_t& reg2) {
        opcode = (instruction >> 6) & 0b00000011; // Extract the opcode (2 bits)
        reg1 = (instruction >> 3) & 0b00000111;   // Extract the first register (3 bits)
        reg2 = instruction & 0b00000111;          // Extract the second register (3 bits)

        std::cout << "[Decode] Opcode: " << std::bitset<2>(opcode)
                  << ", Reg1: R" << static_cast<int>(reg1) // Print register index as number
                  << ", Reg2: R" << static_cast<int>(reg2) << "\n";
    }

    void execute(uint8_t opcode, uint8_t reg1, uint8_t reg2) {
        switch (opcode) {
            case 0b100: // JMP
                programCounter = reg1;
                break;
            case 0b101: // JEQ
                if (registers.get("R" + std::to_string(reg1)) == 0)
                    programCounter = reg2;
                break;
            case 0b110: // CALL
                memory.write(--stackPointer, programCounter);
                programCounter = reg1;
                break;
            case 0b111: // RET
                programCounter = memory.read(stackPointer++);
                break;
            default:
                executeArithmetic(opcode, reg1, reg2);
                break;
        }
    }

    void executeArithmetic(uint8_t opcode, uint8_t reg1, uint8_t reg2) {
        std::string opcodeStr = getOpcodeString(opcode);

        std::string reg1Name = "R" + std::to_string(reg1);
        std::string reg2Name = "R" + std::to_string(reg2);

        uint8_t operand1 = registers.get(reg1Name);
        uint8_t operand2 = registers.get(reg2Name);
        uint8_t result = alu.performOperation(opcodeStr, operand1, operand2);

        registers.set(reg1Name, result);

        std::cout << "[Execute] " << opcodeStr
                  << " " << reg1Name << ", " << reg2Name
                  << " => Updated " << reg1Name << ": " << std::bitset<8>(result) << "\n";
        registers.display();
    }

    std::string getOpcodeString(uint8_t opcode) {
        switch (opcode) {
            case 0b00: return "ADD";
            case 0b01: return "SUB";
            case 0b10: return "LOAD";
            case 0b11: return "STORE";
            case 0b100: return "JMP";
            case 0b101: return "JEQ";
            case 0b110: return "CALL";
            case 0b111: return "RET";
            default: return "UNKNOWN";
        }
    }
};

#endif
