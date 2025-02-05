#ifndef CPU_H
#define CPU_H

#include <vector>
#include <string>
#include "ALU.h"
#include "Registers.h"
#include "Memory.h"

class CPU {
public:
    int programCounter;
    std::vector<int> instructionMemory;
    Registers registers;
    ALU alu;
    Memory memory;

    CPU();
    void loadProgram(const std::vector<int>& program);
    void executeProgram(std::ostream& outputStream);

private:
    void decodeAndExecute(int instruction, std::ostream& outputStream);
    std::string getOpcodeString(int opcode);
};

#endif // CPU_H
