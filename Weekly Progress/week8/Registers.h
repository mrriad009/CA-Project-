#ifndef REGISTERS_H
#define REGISTERS_H

#include <map>
#include <string>
#include <iostream>

class Registers {
public:
    std::map<std::string, int> regs;

    Registers();
    int get(const std::string& reg);
    void set(const std::string& reg, int value);
    void display(std::ostream& outputStream);
};

#endif // REGISTERS_H
