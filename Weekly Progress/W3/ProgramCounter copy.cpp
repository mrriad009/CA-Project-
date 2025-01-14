// include/ProgramCounter.h
#ifndef PROGRAMCOUNTER_H
#define PROGRAMCOUNTER_H

class ProgramCounter {
public:
    int pc = 0;

    void increment() {
        pc++;
    }

    void set(int address) {
        pc = address;
    }

    int get() const {
        return pc;
    }
};

#endif
