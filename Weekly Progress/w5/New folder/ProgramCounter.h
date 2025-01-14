#ifndef PROGRAMCOUNTER_H
#define PROGRAMCOUNTER_H

class ProgramCounter {
private:
    int counter;
public:
    ProgramCounter() : counter(0) {}
    void increment();
    void set(int address);
    int get() const;
};

#endif
