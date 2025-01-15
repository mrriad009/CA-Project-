#ifndef IODEVICE_H
#define IODEVICE_H

#include <iostream>
#include <bitset>

class IODevice {
public:
    static int keyboard_read() {
        int key = 0b01000001; // Simulated key press 'A' (binary 01000001)
        std::cout << "[Keyboard] Simulated key press: " << std::bitset<8>(key) << std::endl;
        return key;
    }

    static void display_output(int data) {
        std::cout << "[Display] Output: " << std::bitset<8>(data) << std::endl;
    }
};

#endif