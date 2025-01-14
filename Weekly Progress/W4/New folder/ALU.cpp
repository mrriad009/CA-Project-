#ifndef ALU_H
#define ALU_H

#include <iostream>
using namespace std;

class ALU {
public:
    int add(int a, int b) {
        cout << "ALU: Adding " << a << " + " << b << " = " << (a + b) << endl;
        return a + b;
    }

    int subtract(int a, int b) {
        cout << "ALU: Subtracting " << a << " - " << b << " = " << (a - b) << endl;
        return a - b;
    }
};

#endif
