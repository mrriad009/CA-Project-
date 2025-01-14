#include "Register.h"

void Register::set(int v) {
    value = v;
}

int Register::get() const {
    return value;
}
