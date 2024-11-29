#include <iostream>
#include <vector>
#include "ALU.h"
#include "Register.h"
#include "ProgramCounter.h"
#include "Memory.h"
#include "Assembler.h"

using namespace std;

int main() {
    // Initialize CPU components
    ALU alu;
    Register regA, regB, regC;  // General-purpose registers
    ProgramCounter pc;
    Memory memory;

    // Store initial values in memory (simulate assembly program)
    memory.store(0, 10);  // Store value 10 at address 0
    memory.store(1, 20);  // Store value 20 at address 1
    memory.store(2, 1);   // Store value 1 at address 2
    memory.store(3, -1);  // Store value -1 at address 3 (used for termination)

    cout << "----------------------------" << endl;
    cout << "Starting Fetch-Decode-Execute Cycle..." << endl;
    cout << "----------------------------" << endl;

    // Fetch-Decode-Execute cycle
    vector<string> instructions = {"MOV", "ADD", "SUB"};
    vector<int> operands1 = {0, 1, 2};  // Using memory addresses as operands
    vector<int> operands2 = {1, 2, 3};

    for (int i = 0; i < instructions.size(); ++i) {
        // Fetch instruction and operands (from memory)
        string opcodeBinary = Assembler::assemblerToMachineCode(instructions[i]);
        int operand1 = memory.load(operands1[i]);  // Load operands from memory
        int operand2 = memory.load(operands2[i]);

        // Check if any operand is -1, which indicates termination
        if (operand1 == -1 || operand2 == -1) {
            cout << "Encountered -1. Terminating program..." << endl;
            break;  // Exit the loop and terminate the program
        }

        // Output: Instruction and its machine code (in binary format)
        cout << "Memory: Loaded value " << operand1 << " from address " << operands1[i] << endl;
        cout << "Program Counter: Incremented to " << pc.get() + 1 << endl;
        pc.increment();
        
        cout << "Instruction: " << instructions[i] << " (Machine Code: " << opcodeBinary << ")" << endl;
        cout << "CPU Understands: " << "Opcode (binary): " << opcodeBinary << " Operand1: " << operand1 << " Operand2: " << operand2 << endl;

        // Decode and execute the instruction
        int result = alu.execute(instructions[i], operand1, operand2);

        // Store the result in the register
        if (instructions[i] == "MOV") {
            regC.set(result);  // MOV instruction moves the value to a register
        } else if (instructions[i] == "ADD" || instructions[i] == "SUB") {
            regA.set(result);  // Update register A with the result
        }

        cout << "Register: Set value to " << regA.get() << endl;
        cout << "ALU: " << instructions[i] << " " << operand1 << " " << operand2 << " = " << result << endl;
    }

    // Final register values (only displayed if the loop isn't terminated early)
    cout << "Final Register A: " << regA.get() << endl;
    cout << "Final Register C: " << regC.get() << endl;

    cout << "Terminating program..." << endl;

    return 0;
}
