#include <iostream>
#include <vector>
#include <bitset>  // For binary conversion
#include "ALU.h"
#include "Register.h"
#include "ProgramCounter.h"
#include "Memory.h"
#include "Assembler.h"

using namespace std;

// Function to convert integer to 4-bit binary string
string toBinary(int number) {
    return bitset<4>(number).to_string();  // Convert to 4-bit binary string
}

int main() {
    // Initialize CPU components
    ALU alu;
    Register regA, regB;  // General-purpose registers
    ProgramCounter pc;
    Memory memory;
    cout<<endl;
    // Store initial values in memory (simulate assembly program)
    memory.store(0, 10);  // Store value 10 at address 0
    memory.store(1, 20);  // Store value 20 at address 1
    memory.store(2, 11);  // Store value 11 at address 2
    memory.store(3, -1);  // Store value -1 at address 3 (used for termination)

    // Display memory contents
    for (int i = 0; i < 4; ++i) {
        cout << "Memory: Stored value " << memory.load(i) << " at address " << i << endl;
    }

    cout << "----------------------------" << endl;
    cout << "Starting Fetch-Decode-Execute Cycle..." << endl;
    cout << "----------------------------" << endl;

    // Fetch-Decode-Execute cycle
    vector<string> instructions = {"ADD", "SUB", "MOV"};  // ADD and SUB first, then MOV
    vector<int> operands1 = {0, 1, 2};  // Using memory addresses as operands
    vector<int> operands2 = {1, 2, 3};

    // First, execute ADD and SUB operations
    for (int i = 0; i < 2; ++i) {  // Only loop through ADD and SUB
        // Fetch instruction and operands (from memory)
        string opcodeBinary = Assembler::assemblerToMachineCode(instructions[i]);
        int operand1 = memory.load(operands1[i]);  // Load operands from memory
        int operand2 = memory.load(operands2[i]);

        // Check if any operand is -1, which indicates termination
        if (operand1 == -1 || operand2 == -1) {
            cout << "Encountered -1. Terminating program..." << endl;
            break;  // Exit the loop and terminate the program
        }
        cout <<endl;
        // Output: Instruction and its machine code (in binary format)
        cout << "Memory: Loaded value " << operand1 << " from address " << operands1[i] << endl;
        cout << "Program Counter: Incremented to " << pc.get() + 1 << " (Machine Code: " << toBinary(pc.get() + 1) << ")" << endl;
        pc.increment();

        cout << "Instruction: " << instructions[i] << " (Machine Code: " << opcodeBinary << ")" << endl;
        cout << "CPU Understands: " << "Opcode (binary): " << opcodeBinary << " Operand1: " << toBinary(operand1) << " Operand2: " << toBinary(operand2) << endl;

        // Decode and execute the instruction
        int result = alu.execute(instructions[i], operand1, operand2);

        // Store the result in the register
        if (instructions[i] == "ADD" || instructions[i] == "SUB") {
            regA.set(result);  // Update register A with the result
        }

        cout << "ALU: " << instructions[i] << " " << operand1 << " " << operand2 << " = " << result << " (Binary: " << toBinary(result) << ")" << endl;
        cout << "Register A: Set value to " << regA.get() << " (Binary: " << toBinary(regA.get()) << ")" << endl;
    }

    // Then execute the MOV operation
    regB.set(regA.get());
    cout<<endl;
      // MOV: Copy the value from regA to regB, without modifying regA
    cout << "MOV Operation: Register A value " << regA.get() << " moved to Register B." << endl;
    cout << "Register B: Set value to " << regB.get() << " (Binary: " << toBinary(regB.get()) << ")" << endl;
cout<<endl;
    // Final register values
    cout << "Final Register A: " << regA.get() << " (Binary: " << toBinary(regA.get()) << ")" << endl;
    cout << "Final Register B: " << regB.get() << " (Binary: " << toBinary(regB.get()) << ")" << endl;

    cout << "Terminating program..." << endl;

    return 0;
}
