// include/ALU.h
#ifndef ALU_H
#define ALU_H

#include <iostream>
using namespace std;

class ALU {
public:
    int add(int a, int b) {
        return a + b;
    }

    int sub(int a, int b) {
        return a - b;
    }
};

#endif
