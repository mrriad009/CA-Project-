#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>
#include <bitset>  // For converting to binary

class Assembler {
public:
    static std::string assemblerToMachineCode(const std::string& instruction);
};

#endif
