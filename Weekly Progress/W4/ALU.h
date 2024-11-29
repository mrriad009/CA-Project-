#ifndef ALU_H
#define ALU_H

#include <string>

class ALU {
public:
    int execute(const std::string& instruction, int operand1, int operand2);
};

#endif
