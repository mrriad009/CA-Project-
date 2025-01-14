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
        std::cout << "\n=== Starting Program Execution ===\n";

        while (programCounter < instructionMemory.size()) {
            std::cout << "\n--- Fetch-Decode-Execute Cycle ---\n";

            // Fetch
            uint8_t instruction = fetch();

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
    std::vector<uint8_t> instructionMemory;
    Registers registers;
    ALU alu;

    // Fetch: Get the next instruction and increment the program counter
    uint8_t fetch() {
        if (programCounter >= instructionMemory.size()) {
            throw std::out_of_range("Program counter out of bounds!");
        }
        uint8_t instruction = instructionMemory[programCounter++];
        std::cout << "[Fetch] Instruction: " << std::bitset<8>(instruction) << "\n";
        return instruction;
    }

    // Decode: Extract opcode and register indices from the instruction
    void decode(uint8_t instruction, uint8_t& opcode, uint8_t& reg1, uint8_t& reg2) {
        opcode = (instruction >> 6) & 0b00000011;
        reg1 = (instruction >> 3) & 0b00000111;
        reg2 = instruction & 0b00000111;

        std::cout << "[Decode] Opcode: " << std::bitset<2>(opcode)
                  << ", Reg1: R" << reg1
                  << ", Reg2: R" << reg2 << "\n";
    }

    // Execute: Perform the operation based on the opcode
    void execute(uint8_t opcode, uint8_t reg1, uint8_t reg2) {
        std::string opcodeStr = getOpcodeString(opcode);

        uint8_t operand1 = registers.get("R" + std::to_string(reg1));
        uint8_t operand2 = registers.get("R" + std::to_string(reg2));
        uint8_t result = alu.performOperation(opcodeStr, operand1, operand2);

        registers.set("R" + std::to_string(reg1), result);

        std::cout << "[Execute] " << opcodeStr
                  << " R" << reg1 << ", R" << reg2
                  << " => Updated R" << reg1 << ": " << std::bitset<8>(result) << "\n";
        registers.display();
    }

    // Map opcode to a human-readable string
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
