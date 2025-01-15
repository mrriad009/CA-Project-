
# Virtual CPU Emulator with I/O Device Integration

This repository contains a simple Virtual CPU Emulator that simulates a basic CPU with memory, I/O devices, and an assembler. The emulator supports input and output operations, allowing it to interact with simulated keyboard and display devices. This document provides an overview of the components, their functionality, and how they work together.

---

## **Overview**

The Virtual CPU Emulator is a simulation of a basic CPU that can execute simple assembly instructions. The emulator includes memory management, I/O device simulation, and an assembler to convert assembly code into machine code. The key features of the emulator include:

- **Memory Management**: Simulates a 16-byte memory with segments for code, data, stack, and heap.
- **I/O Devices**: Simulates a keyboard for input and a display for output.
- **Assembler**: Converts assembly instructions into machine code.
- **CPU Execution**: Executes machine code instructions, including I/O operations.

---

## **Components**

### **1. Memory (`Memory.h`)**
The `Memory` class simulates a 16-byte memory with four segments: code, data, stack, and heap. It provides methods to read from and write to memory.

#### **Key Features**
- **Memory Segments**: The memory is divided into segments for code, data, stack, and heap.
- **Read/Write Operations**: The `read` and `write` methods allow the CPU to interact with memory.
- **Memory Initialization**: The memory is initialized to a specified size, and all locations are set to 0.

#### **Code Snippet**
```cpp
void write(size_t address, int data) {
    if (address < memory.size()) {
        memory[address] = data;
        std::cout << "[Memory Write] Address: " << std::bitset<8>(address) << ", Data: " << std::bitset<8>(data) << std::endl;
    }
}

int read(size_t address) {
    if (address < memory.size()) {
        int data = memory[address];
        std::cout << "[Memory Read] Address: " << std::bitset<8>(address) << ", Data: " << std::bitset<8>(data) << std::endl;
        return data;
    }
}
```

---

### **2. CPU (`CPU.h`)**
The `CPU` class simulates a basic CPU with four registers (R0, R1, R2, R3). It can execute machine code instructions, including I/O operations.

#### **Key Features**
- **Registers**: The CPU has four registers (R0-R3) for storing data.
- **Fetch-Decode-Execute Cycle**: The CPU fetches instructions from memory, decodes them, and executes them.
- **I/O Operations**: The CPU supports IN and OUT instructions for interacting with I/O devices.

#### **Code Snippet**
```cpp
void execute() {
    size_t pc = 0; // Program counter
    while (pc < program.size()) {
        int instruction = memory.read(pc);
        int opcode = (instruction & 0b11100000) >> 5; // Extract opcode
        int reg = instruction & 0b00000111;          // Extract register

        switch (opcode) {
        case 0b100: // IN
            registers[reg] = IODevice::keyboard_read();
            break;
        case 0b101: // OUT
            IODevice::display_output(registers[reg]);
            break;
        default:
            std::cerr << "[CPU] Invalid Opcode: " << std::bitset<3>(opcode) << std::endl;
            return;
        }
        pc++;
    }
}
```

---

### **3. IODevice (`IODevice.h`)**
The `IODevice` class simulates a keyboard and a display. It provides methods for reading input from the keyboard and writing output to the display.

#### **Key Features**
- **Keyboard Input**: Simulates a key press and returns the corresponding ASCII value.
- **Display Output**: Simulates outputting data to a display.

#### **Code Snippet**
```cpp
static int keyboard_read() {
    int key = 0b01000001; // Simulated key press 'A'
    std::cout << "[Keyboard] Simulated key press: " << std::bitset<8>(key) << std::endl;
    return key;
}

static void display_output(int data) {
    std::cout << "[Display] Output: " << std::bitset<8>(data) << std::endl;
}
```

---

### **4. Assembler (`Assembler.h`)**
The `Assembler` class converts assembly instructions into machine code. It currently supports IN and OUT instructions.

#### **Key Features**
- **Instruction Translation**: Converts assembly instructions like `IN R0` and `OUT R0` into machine code.
- **Error Handling**: Reports unknown instructions.

#### **Code Snippet**
```cpp
static std::vector<int> assemble(const std::vector<std::string> &assembly_code) {
    std::vector<int> machine_code;
    for (const auto &line : assembly_code) {
        if (line == "IN R0") {
            machine_code.push_back(0b10000000); // IN R0
        } else if (line == "OUT R0") {
            machine_code.push_back(0b10100000); // OUT R0
        } else {
            std::cerr << "[Assembler] Unknown instruction: " << line << std::endl;
        }
    }
    return machine_code;
}
```

---

### **5. Main Program (`main.cpp`)**
The `main.cpp` file is the entry point of the program. It initializes the memory, CPU, and assembler, and allows the user to input assembly code for execution.

#### **Execution Flow**
1. **Memory Initialization**: The memory is initialized with a size of 16 bytes.
2. **Assembly Code Input**: The user inputs assembly code, which is stored in a vector.
3. **Assembling Code**: The assembler converts the assembly code into machine code.
4. **CPU Execution**: The CPU loads the machine code into memory and executes it.

#### **Code Snippet**
```cpp
int main() {
    Memory memory(16);
    std::vector<std::string> assembly_code;
    std::string line;
    while (std::getline(std::cin, line) && !line.empty()) {
        assembly_code.push_back(line);
    }

    std::vector<int> machine_code = Assembler::assemble(assembly_code);
    CPU cpu(memory);
    cpu.load_program(machine_code);
    cpu.execute();

    return 0;
}
```

---

### **Example Run and Output Explanation**

#### **Input Assembly Code**
```assembly
IN R0
OUT R0
```

#### **Execution Steps**
1. **Assembling Code**:
   - `IN R0` is converted to machine code `10000000`.
   - `OUT R0` is converted to machine code `10100000`.
2. **CPU Execution**:
   - **Cycle 1**:
     - **Fetch**: Fetches the instruction `10000000` (`IN R0`).
     - **Decode**: Decodes the opcode `100` (`IN`) and register `R0`.
     - **Execute**: Reads the simulated key press `01000001` (ASCII `'A'`) from the keyboard and stores it in `R0`.
   - **Cycle 2**:
     - **Fetch**: Fetches the instruction `10100000` (`OUT R0`).
     - **Decode**: Decodes the opcode `101` (`OUT`) and register `R0`.
     - **Execute**: Outputs the value `01000001` from `R0` to the display.

#### **Output**
```
[Keyboard] Simulated key press: 01000001
[CPU] Updated R0: 01000001
[Display] Output: 01000001
[Execution Complete]
```

---
