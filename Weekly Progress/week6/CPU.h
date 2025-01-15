#ifndef CPU_H
#define CPU_H

#include "Memory.h"
#include "IODevice.h"
#include <vector>
#include <iostream>
#include <bitset>

class CPU {
private:
    int registers[4] = {0}; // R0, R1, R2, R3
    Memory &memory;
    std::vector<int> program;

public:
    CPU(Memory &mem) : memory(mem) {}

    void load_program(const std::vector<int> &prog) {
        program = prog;
        for (size_t i = 0; i < program.size(); ++i) {
            memory.write(i, program[i]);
        }
        std::cout << "[CPU] Loading Program into Memory" << std::endl;
    }

    void execute() {
        std::cout << "\n=== Starting Program Execution ===\n";
        size_t pc = 0; // Program counter
        while (pc < program.size()) {
            int instruction = memory.read(pc);
            std::cout << "--- Fetch-Decode-Execute Cycle ---\n";
            std::cout << "[CPU] Fetch: Instruction = " << std::bitset<8>(instruction) << std::endl;

            int opcode = (instruction & 0b11100000) >> 5; // Extract first 3 bits for opcode
            int reg = instruction & 0b00000111;          // Extract last 3 bits for register

            switch (opcode) {
            case 0b100: // IN
                std::cout << "[CPU] Decode: Opcode = " << std::bitset<3>(opcode) << ", Reg1 = R" << reg << std::endl;
                registers[reg] = IODevice::keyboard_read();
                break;
            case 0b101: // OUT
                std::cout << "[CPU] Decode: Opcode = " << std::bitset<3>(opcode) << ", Reg1 = R" << reg << std::endl;
                IODevice::display_output(registers[reg]);
                break;
            default:
                std::cerr << "[CPU] Invalid Opcode: " << std::bitset<3>(opcode) << std::endl;
                return;
            }

            std::cout << "[CPU] Updated R" << reg << ": " << std::bitset<8>(registers[reg]) << std::endl;
            print_registers();

            pc++;
        }
        std::cout << "\n[Execution Complete]" << std::endl;
    }

    void print_registers() {
        std::cout << "=== Register States ===" << std::endl;
        for (int i = 0; i < 4; ++i) {
            std::cout << "R" << i << ": " << std::bitset<8>(registers[i]) << std::endl;
        }
        std::cout << "========================" << std::endl;
    }
};

#endif