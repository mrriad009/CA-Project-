#ifndef CPU_H
#define CPU_H

#include <vector>
#include <iostream>
#include "ALU.h"
#include "Registers.h"
#include "Memory.h"

class CPU {
public:
    int programCounter;  // The program counter that tracks which instruction to execute
    int stackPointer;    // Stack pointer for subroutine calls
    std::vector<int> instructionMemory;
    Registers registers;
    ALU alu;
    Memory memory;

    CPU();
    void loadProgram(const std::vector<int>& program);
    void executeProgram(std::ostream& outputStream);

private:
    void fetchDecodeExecute(std::ostream& outputStream);
    void decodeAndExecute(int instruction, std::ostream& outputStream);
    std::string getOpcodeString(int opcode);
    void handleBranching(int reg1, int reg2, std::string opcodeStr, int targetAddress);
    void handleSubroutines(std::string opcodeStr, int operand2);
};

#endif // CPU_H
