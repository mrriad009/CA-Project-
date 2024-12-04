#ifndef REGISTER_H
#define REGISTER_H

class Register {
public:
    int value = 0;

    void set(int v) {
        value = v;
    }

    int get() const {
        return value;
    }
};

#endif
