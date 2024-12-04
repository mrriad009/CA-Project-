#include "ALU.h"
#include <iostream>

int ALU::execute(const std::string& instruction, int operand1, int operand2) {
    int result = 0;

    if (instruction == "MOV") {
        result = operand1;
    } else if (instruction == "ADD") {
        result = operand1 + operand2;
    } else if (instruction == "SUB") {
        result = operand1 - operand2;
    }

    return result;
}
