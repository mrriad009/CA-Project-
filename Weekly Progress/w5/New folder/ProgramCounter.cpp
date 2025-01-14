#include "ProgramCounter.h"

void ProgramCounter::increment() {
    counter++;
}

void ProgramCounter::set(int address) {
    counter = address;
}

int ProgramCounter::get() const {
    return counter;
}
