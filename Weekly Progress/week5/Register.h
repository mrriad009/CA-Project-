#ifndef REGISTER_H
#define REGISTER_H

class Register {
private:
    int value;
public:
    Register() : value(0) {}
    void set(int v);
    int get() const;
};

#endif
