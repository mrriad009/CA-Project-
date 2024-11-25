#ifndef REGISTER_H
#define REGISTER_H

#include <iostream>
using namespace std;

class Register {
public:
    int value = 0;

    void set(int newValue) {
        value = newValue;
        cout << "Register: Set value to " << value << endl;
         cout<<endl;

    }

    int get() const {
        cout << "Register: Current value is  " << value << endl;
        return value;
       
    }
};

#endif
