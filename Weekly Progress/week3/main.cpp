#include <iostream>
#include "ALU.h"
#include "Register.h"
#include "ProgramCounter.h"

using namespace std;

int main() {
    // Initialize CPU components
    ALU alu;
    Register regA, regB;
    ProgramCounter pc;

    // Demonstrate ALU functionality
    cout << "Testing ALU -------:" << endl;
    int sum = alu.add(10, 20);
    cout << "10 + 20 = " << sum << endl;

    int difference = alu.sub(30, 15);
    cout << "30 - 15 = " << difference << endl;

    // Demonstrate Register functionality
    cout << "\nTesting Registers --------:" << endl;
    regA.set(42);
    regB.set(84);
    cout << "Register A value: " << regA.get() << endl;
    cout << "Register B value: " << regB.get() << endl;

    // Demonstrate Program Counter functionality
    cout << "\nTesting Program Counter --------:" << endl;
    pc.set(5);
    cout << "Program Counter set to: " << pc.get() << endl;
    pc.increment();
    cout << "Program Counter incremented to: " << pc.get() << endl;

    return 0;
}
