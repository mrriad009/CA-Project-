#include "CPU.h"

CPU::CPU() : programCounter(0), memory(25) {}

void CPU::loadProgram(const std::vector<int>& program) {
    instructionMemory = program;
}

void CPU::executeProgram(std::ostream& outputStream) {
    while (programCounter < instructionMemory.size()) {
        int instruction = instructionMemory[programCounter];
        outputStream << "Fetching instruction at address " << programCounter << ": " << instruction << std::endl;
        programCounter++;
        decodeAndExecute(instruction, outputStream);
    }
}

void CPU::decodeAndExecute(int instruction, std::ostream& outputStream) {
    int opcode = (instruction >> 6) & 0x03;
    int reg1 = (instruction >> 3) & 0x07;
    int reg2 = instruction & 0x07;
    std::string opcodeStr = getOpcodeString(opcode);

    outputStream << "Decoding instruction: " << instruction << " as (" << opcodeStr << " R" << reg1 << " R" << reg2 << ")" << std::endl;

    int operand1 = registers.get("R" + std::to_string(reg1));
    int operand2 = registers.get("R" + std::to_string(reg2));

    outputStream << "Operands: " << "operand1 = " << operand1 << ", operand2 = " << operand2 << std::endl;

    if (opcodeStr == "INPUT") {
        int value;
        std::cout << "Enter value for R" << reg1 << ": ";
        std::cin >> value;
        registers.set("R" + std::to_string(reg1), value);
        outputStream << "Input value " << value << " into R" << reg1 << std::endl;
    } else if (opcodeStr == "OUTPUT") {
        int value = registers.get("R" + std::to_string(reg1));
        std::cout << "Output value from R" << reg1 << ": " << value << std::endl;
        outputStream << "Output value from R" << reg1 << ": " << value << std::endl;
    } else if (opcodeStr == "JUMP") {
        programCounter = operand2;
        outputStream << "Jumping to address " << operand2 << std::endl;
    } else if (opcodeStr == "CALL") {
        memory.write(memory.memorySpace.size() - 1, programCounter);
        programCounter = operand2;
        outputStream << "Calling subroutine at address " << operand2 << std::endl;
    } else if (opcodeStr == "RET") {
        programCounter = memory.read(memory.memorySpace.size() - 1);
        outputStream << "Returning from subroutine to address " << programCounter << std::endl;
    } else {
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
            outputStream << "Executing instruction: " << instruction << " (" << opcodeStr << " R" << reg1 << " R" << reg2 << ")" << std::endl;
            outputStream << "Updated R" << reg1 << " to " << result << std::endl;
        }
    }

    outputStream << "Current Register States: ";
    registers.display(outputStream);
    outputStream << "Current Memory State: ";
    memory.display(outputStream);
    outputStream << std::endl;
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
        default: return "UNKNOWN";
    }
}
