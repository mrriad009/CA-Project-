#include <iostream>
#include "ALU.h"
#include "Register.h"
#include "ProgramCounter.h"
#include "Assembler.h"

using namespace std;

int main() {
    // Initialize CPU components
    ALU alu;
    Register reg1, reg2;
    ProgramCounter pc;
    Assembler assembler;

    // Initial Register Values
    reg1.set(42);  // Register R1 = 42
    reg2.set(84);  // Register R2 = 84

    // Initial Program Counter Value
    pc.set(0);  // PC starts at 0

    // Display initial values
    cout << "Initial Register Values:" << endl;
    cout << "R1: " << reg1.get() << " (" << bitset<8>(reg1.get()) << ")" << endl;
    cout << "R2: " << reg2.get() << " (" << bitset<8>(reg2.get()) << ")" << endl;
    cout << "-------------------------" << endl;
    cout << "Program Counter (PC) Initial Value: " << pc.get() << " (" << bitset<8>(pc.get()) << ")" << endl;
    cout << "-------------------------" << endl;

    // Test interaction with Program Counter and Assembler Instructions
    cout << "\nTesting with Program Counter interacting with Assembler Instructions:" << endl;

    // ADD operation
    string currentInstruction = "ADD";
    string machineCode = assembler.assemblerToMachineCode(currentInstruction);
    cout << "Assembler: " << currentInstruction << " -> Machine Code: " << machineCode << " (" << bitset<8>(stoi(machineCode, nullptr, 2)) << ")" << endl;
    cout << "PC = " << pc.get() << " (" << bitset<8>(pc.get()) << "): " << currentInstruction << endl;
    int resultAdd = alu.add(reg1.get(), reg2.get());
    cout << "ADD R1, R2 -> Result = " << resultAdd << " (" << bitset<8>(resultAdd) << ")" << endl;

    // Increment Program Counter
    pc.increment();
    
    // SUB operation
    currentInstruction = "SUB";
    machineCode = assembler.assemblerToMachineCode(currentInstruction);
    cout << "Assembler: " << currentInstruction << " -> Machine Code: " << machineCode << " (" << bitset<8>(stoi(machineCode, nullptr, 2)) << ")" << endl;
    cout << "PC = " << pc.get() << " (" << bitset<8>(pc.get()) << "): " << currentInstruction << endl;
    int resultSub = alu.sub(reg1.get(), reg2.get());
    cout << "SUB R1, R2 -> Result = " << resultSub << " (" << bitset<8>(resultSub) << ")" << endl;

    // Increment Program Counter
    pc.increment();

    // Final values
    cout << "\nFinal Register Values:" << endl;
    cout << "R1: " << reg1.get() << " (" << bitset<8>(reg1.get()) << ")" << endl;
    cout << "R2: " << reg2.get() << " (" << bitset<8>(reg2.get()) << ")" << endl;

    cout << "\nFinal Program Counter: " << pc.get() << " (" << bitset<8>(pc.get()) << ")" << endl;

    return 0;
}
