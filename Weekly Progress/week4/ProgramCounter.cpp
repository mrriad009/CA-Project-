#ifndef PROGRAM_COUNTER_H
#define PROGRAM_COUNTER_H

#include <iostream>
using namespace std;

class ProgramCounter {
public:
    int pc = 0;

    void increment() {
        pc++;
        cout << "Program Counter: Incremented to " << pc << endl;
    }

    void set(int address) {
        pc = address;
        cout << "Program Counter: Set to " << pc << endl;
        cout << endl;
    }

    int get() const {
        return pc;
    }
};

#endif
