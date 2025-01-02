#include "ALU.h"

#ifndef ALU_H
#define ALU_H

#include <string>

class ALU {
public:
    int performOperation(const std::string& opcode, int operand1, int operand2) {
        if (opcode == "ADD") return operand1 + operand2;
        if (opcode == "SUB") return operand1 - operand2;
        if (opcode == "LOAD") return operand2;
        if (opcode == "STORE") return operand1;
        return 0;
    }
};

#endif