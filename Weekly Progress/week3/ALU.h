// ALU.h
#ifndef ALU_H
#define ALU_H

#include <iostream>

class ALU {
public:
    uint8_t performOperation(const std::string& opcode, uint8_t operand1, uint8_t operand2) {
        if (opcode == "ADD") return operand1 + operand2;
        if (opcode == "SUB") return operand1 - operand2;
        if (opcode == "LOAD") return operand2; // LOAD directly assigns
        if (opcode == "STORE") return operand1; // STORE does not modify
        return 0; // Default for unknown instructions
    }
};

#endif
