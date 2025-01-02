#include <string>
#include <bitset>

class Assembler {
public:
    static std::string assemblerToMachineCode(const std::string& instruction) {
        if (instruction == "MOV") {
            return std::bitset<8>(0b00000010).to_string();
        } else if (instruction == "ADD") {
            return std::bitset<8>(0b00000000).to_string();
        } else if (instruction == "SUB") {
            return std::bitset<8>(0b00000001).to_string();
        } else {
            return "Unknown";
        }
    }
};
