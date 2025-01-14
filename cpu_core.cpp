#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

// ALU (Arithmetic Logic Unit)
class ALU {
public:
    std::bitset<8> execute(const std::string& operation, const std::bitset<8>& operand1, const std::bitset<8>& operand2) {
        if (operation == "ADD") {
            return std::bitset<8>(operand1.to_ulong() + operand2.to_ulong());
        } else if (operation == "SUB") {
            return std::bitset<8>(operand1.to_ulong() - operand2.to_ulong());
        } else {
            throw std::invalid_argument("Unsupported ALU operation: " + operation);
        }
    }
};

// General-Purpose Registers
class Registers {
private:
    std::unordered_map<std::string, std::bitset<8>> reg;

public:
    Registers() {
        // Initialize registers with predefined values
        reg["R0"] = std::bitset<8>("00000000"); // R0 = 0
        reg["R1"] = std::bitset<8>("00000101"); // R1 = 5
        reg["R2"] = std::bitset<8>("00000011"); // R2 = 3
        reg["R3"] = std::bitset<8>("00001000"); // R3 = 8
    }

    std::bitset<8> get(const std::string& regName) const {
        if (reg.find(regName) == reg.end()) {
            throw std::invalid_argument("Invalid register: " + regName);
        }
        return reg.at(regName);
    }

    void set(const std::string& regName, const std::bitset<8>& value) {
        if (reg.find(regName) == reg.end()) {
            throw std::invalid_argument("Invalid register: " + regName);
        }
        reg[regName] = value;
    }

    void display() const {
        // Define the order of registers explicitly
        std::vector<std::string> regOrder = {"R0", "R1", "R2", "R3"};
        
        for (const std::string& regName : regOrder) {
            std::cout << regName << ": " << reg.at(regName) << std::endl;
        }
    }
};

// Memory
class Memory {
private:
    std::unordered_map<int, std::bitset<8>> memory;

public:
    void store(int address, const std::bitset<8>& value) {
        memory[address] = value;
    }

    std::bitset<8> load(int address) const {
        if (memory.find(address) == memory.end()) {
            throw std::out_of_range("Memory address out of bounds");
        }
        return memory.at(address);
    }
};

// Program Counter (PC)
class ProgramCounter {
private:
    std::bitset<8> pc;

public:
    ProgramCounter() : pc(0) {}

    std::bitset<8> get() const {
        return pc;
    }

    void set(const std::bitset<8>& address) {
        pc = address;
    }

    void increment() {
        pc = std::bitset<8>(pc.to_ulong() + 1);
    }
};

// Instruction Register (IR)
class InstructionRegister {
private:
    std::string instruction;

public:
    void load(const std::string& instr) {
        instruction = instr;
    }

    std::string get() const {
        return instruction;
    }
};

// CPU
class CPU {
private:
    ALU alu;
    Registers registers;  // Fully defined before this point
    Memory memory;
    ProgramCounter pc;
    InstructionRegister ir;

public:
    void execute(const std::string& instruction) {
        std::istringstream iss(instruction);
        std::string operation, dest, src;
        int address;

        iss >> operation;

        if (operation == "ADD" || operation == "SUB") {
            iss >> dest >> src;
            std::bitset<8> result = alu.execute(operation, registers.get(dest), registers.get(src));
            registers.set(dest, result);
        } else if (operation == "LOAD") {
            iss >> dest >> address;
            registers.set(dest, memory.load(address));
        } else if (operation == "STORE") {
            iss >> src >> address;
            memory.store(address, registers.get(src));
        } else {
            throw std::invalid_argument("Unsupported instruction: " + operation);
        }

        pc.increment();
    }

    void run() {
        std::string instruction;
        while (true) {
            std::cout << "Enter assembler instruction (or 'EXIT' to quit): ";
            std::getline(std::cin, instruction);
            if (instruction == "EXIT") break;

            try {
                ir.load(instruction);
                execute(ir.get());
                std::cout << "Registers after execution:\n";
                registers.display();
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
};

// Main Function
int main() {
    CPU cpu;

    // Run the CPU with user input
    cpu.run();

    return 0;
}
