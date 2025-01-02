#include <iostream>

class Register {
private:
    int value;
public:
    Register() : value(0) {}
    void set(int v) { value = v; }
    int get() const { return value; }
};
