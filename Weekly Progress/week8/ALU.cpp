#include "ALU.h"

int ALU::performOperation(const std::string& opcode, int operand1, int operand2) {
    if (opcode == "ADD") return operand1 + operand2;
    if (opcode == "SUB") return operand1 - operand2;
    if (opcode == "MUL") return operand1 * operand2;  // Multiplication
    if (opcode == "DIV") {
        if (operand2 == 0) {
            std::cerr << "Error: Division by zero!" << std::endl;
            return 0;
        }
        return operand1 / operand2;  // Division
    }
    if (opcode == "CMP") return operand1 == operand2 ? 1 : 0;  // Comparison (set flag)
    if (opcode == "SHL") return operand1 << operand2;  // Shift Left
    if (opcode == "SHR") return operand1 >> operand2;  // Shift Right
    if (opcode == "LOAD") return operand2;
    if (opcode == "STORE") return operand1;
    return 0;  // Unknown opcode
}
