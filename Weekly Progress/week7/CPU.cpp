#include "CPU.h"

CPU::CPU() : programCounter(0), stackPointer(0xFF), memory(256) {}

void CPU::loadProgram(const std::vector<int>& program) {
    instructionMemory = program;
}

void CPU::executeProgram(std::ostream& outputStream) {
    while (programCounter < instructionMemory.size()) {
        fetchDecodeExecute(outputStream);
    }
    outputStream << "[Execution Complete]" << std::endl;
}

void CPU::fetchDecodeExecute(std::ostream& outputStream) {
    // Fetch Stage
    int instruction = instructionMemory[programCounter];
    outputStream << "Fetching instruction at address " << programCounter << ": " << instruction << std::endl;
    programCounter++;

    // Decode and Execute
    decodeAndExecute(instruction, outputStream);
}

void CPU::decodeAndExecute(int instruction, std::ostream& outputStream) {
    int opcode = (instruction >> 6) & 0x03;  // Extract opcode (2 bits)
    int reg1 = (instruction >> 3) & 0x07;   // Extract the first register (3 bits)
    int reg2 = instruction & 0x07;          // Extract the second register (3 bits)
    std::string opcodeStr = getOpcodeString(opcode);

    outputStream << "Decoding instruction: " << instruction << " as (" << opcodeStr << " R" << reg1 << " R" << reg2 << ")" << std::endl;

    int operand1 = registers.get("R" + std::to_string(reg1));
    int operand2 = registers.get("R" + std::to_string(reg2));

    // Handle branching instructions (BEQ, BNE)
    if (opcodeStr == "BEQ" || opcodeStr == "BNE") {
        handleBranching(operand1, operand2, opcodeStr, operand2); // Handle branching
    }
    else if (opcodeStr == "CALL" || opcodeStr == "RET") {
        handleSubroutines(opcodeStr, operand2); // Handle subroutines
    }
    else {
        int result = alu.performOperation(opcodeStr, operand1, operand2);
        if (opcodeStr == "LOAD") {
            int value = memory.read(operand2);
            registers.set("R" + std::to_string(reg1), value);
            outputStream << "Loaded value " << value << " into R" << reg1 << std::endl;
        } else if (opcodeStr == "STORE") {
            memory.write(operand2, operand1);
            outputStream << "Stored value " << operand1 << " at memory address " << operand2 << std::endl;
        } else {
            registers.set("R" + std::to_string(reg1), result);
            outputStream << "Updated R" << reg1 << " to " << result << std::endl;
        }
    }

    outputStream << "Current Register States: ";
    registers.display(outputStream);
    outputStream << "Current Memory State: ";
    memory.display(outputStream);
}

std::string CPU::getOpcodeString(int opcode) {
    switch (opcode) {
        case 0: return "ADD";
        case 1: return "SUB";
        case 2: return "LOAD";
        case 3: return "STORE";
        case 4: return "INPUT";
        case 5: return "OUTPUT";
        case 6: return "JUMP";
        case 7: return "CALL";
        case 8: return "RET";
        case 9: return "BEQ";
        case 10: return "BNE";
        default: return "UNKNOWN";
    }
}

void CPU::handleBranching(int reg1, int reg2, std::string opcodeStr, int targetAddress) {
    if (opcodeStr == "BEQ") {
        if (reg1 == reg2) {
            programCounter = targetAddress;
        }
    } else if (opcodeStr == "BNE") {
        if (reg1 != reg2) {
            programCounter = targetAddress;
        }
    }
}

void CPU::handleSubroutines(std::string opcodeStr, int operand2) {
    if (opcodeStr == "CALL") {
        memory.write(--stackPointer, programCounter);  // Save the current program counter (PC) to the stack
        programCounter = operand2;  // Jump to the subroutine address (operand2)
    } else if (opcodeStr == "RET") {
        programCounter = memory.read(stackPointer++);  // Get the return address from the stack
    }
}
