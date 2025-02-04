#include "ALU.h"

int ALU::performOperation(const std::string& opcode, int operand1, int operand2) {
    if (opcode == "ADD") return operand1 + operand2;
    if (opcode == "SUB") return operand1 - operand2;
    if (opcode == "LOAD") return operand2;
    if (opcode == "STORE") return operand1;
    return 0;
}
