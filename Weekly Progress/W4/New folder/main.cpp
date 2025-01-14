#include <iostream>
#include "ALU.h"
#include "Memory.h"
#include "Register.h"
#include "ProgramCounter.h"
using namespace std;

int main() {
    ALU alu;
    Memory memory(10);  // Initialize memory with 10 slots
    Register regA, regB;  // General-purpose registers
    ProgramCounter pc;    // Program counter to track instruction addresses

    // Load sample instructions into memory
    memory.store(0, 10);  // Load value 10 into memory address 0
    memory.store(1, 20);  // Load value 20 into memory address 1
    memory.store(2, 1);   // Store operation code (e.g., ADD) at address 2
    memory.store(3, -1);  // Termination signal at address 3


    // Fetch-Decode-Execute Cycle
    cout<<"------------------------------------------"<<endl;
    cout << "Starting Fetch-Decode-Execute Cycle..." << endl;
    cout<<"------------------------------------------"<<endl;

    while (true) {
        int instruction = memory.load(pc.get());            // Fetch
        pc.increment();

        if (instruction == -1) {                            // Terminate if -1
            cout << "Terminating program..." << endl;
            break;
        }

        // Decode and Execute
        if (pc.get() == 1) {                                    // Assume instruction 1 is to load regA
            regA.set(instruction);
        } else if (pc.get() == 2) {                             // Assume instruction 2 is to load regB
            regB.set(instruction);
        } else if (pc.get() == 3) {                             // Assume instruction 3 is to perform ADD
            int result = alu.add(regA.get(), regB.get());
            cout << "Result of addition: " << result << endl;
            cout<<endl;
        }
    }

    return 0;
}
