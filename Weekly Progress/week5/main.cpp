#include <iostream>
#include <bitset>  // For binary conversion
#include "ALU.h"
#include "Register.h"
#include "ProgramCounter.h"
#include "Memory.h"
#include "Assembler.h"

using namespace std;

string toBinary(int number) {
    return bitset<4>(number).to_string();
}

int main() {
    ALU alu;
    Register regA, regB;
    ProgramCounter pc;
    Memory memory;

    // Store initial values in memory segments
    memory.storeData(0, 10);  // Data Segment: Store value 10 at address 0
    memory.storeData(1, 20);  // Data Segment: Store value 20 at address 1
    memory.storeStack(0, 5);  // Stack Segment: Store value 5 at address 0
    memory.storeHeap(0, 15);  // Heap Segment: Store value 15 at address 0

    // Display memory contents
    memory.printMemory();

    cout << "----------------------------" << endl;
    cout << "Starting Fetch-Decode-Execute Cycle..." << endl;
    cout << "----------------------------" << endl;

    vector<string> instructions = {"ADD", "SUB", "MOV"};
    vector<int> operands1 = {0, 1, 2};
    vector<int> operands2 = {1, 2, 3};

    for (int i = 0; i < 2; ++i) {
        string opcodeBinary = Assembler::assemblerToMachineCode(instructions[i]);
        int operand1 = memory.loadData(operands1[i]);
        int operand2 = memory.loadData(operands2[i]);

        if (operand1 == -1 || operand2 == -1) {
            cout << "Encountered -1. Terminating program..." << endl;
            break;
        }

        cout <<endl;
        cout << "Memory: Loaded value " << operand1 << " from address " << operands1[i] << endl;
        cout << "Program Counter: Incremented to " << pc.get() + 1 << " (Machine Code: " << toBinary(pc.get() + 1) << ")" << endl;
        pc.increment();

        cout << "Instruction: " << instructions[i] << " (Machine Code: " << opcodeBinary << ")" << endl;
        cout << "CPU Understands: " << "Opcode (binary): " << opcodeBinary << " Operand1: " << toBinary(operand1) << " Operand2: " << toBinary(operand2) << endl;

        int result = alu.execute(instructions[i], operand1, operand2);

        if (instructions[i] == "ADD" || instructions[i] == "SUB") {
            regA.set(result);
        }

        cout << "ALU: " << instructions[i] << " " << operand1 << " " << operand2 << " = " << result << " (Binary: " << toBinary(result) << ")" << endl;
        cout << "Register A: Set value to " << regA.get() << " (Binary: " << toBinary(regA.get()) << ")" << endl;
    }

    regB.set(regA.get());
    cout << endl << "MOV Operation: Register A value " << regA.get() << " moved to Register B." << endl;
    cout << "Register B: Set value to " << regB.get() << " (Binary: " << toBinary(regB.get()) << ")" << endl;

    cout << "Final Register A: " << regA.get() << " (Binary: " << toBinary(regA.get()) << ")" << endl;
    cout << "Final Register B: " << regB.get() << " (Binary: " << toBinary(regB.get()) << ")" << endl;

    cout << "Terminating program..." << endl;

    return 0;
}
