# Project Name: Virtual CPU Emulator

## Group Members 
- 1 . Mahamudul Islam Riad  ID : 11220320898
- 2 . Mahatab Hossain       ID : 11220320997
- 3 . Muzahidur Rahman      ID : 11220120780

## Course Details
- Course Name: Computer Architecture
- Course Code: 3101
- Section: 5F
- Department: Computer Science & Engineering
- Instructor: Vashkar Kar (Lecturer)
- Institute: Northern University of Business & Technology Khulna
- Website: www.nubtkhulna.ac.bd

## 1. Project Overview
The goal of this project is to build a virtual CPU emulator. The emulator will replicate basic CPU functionality, including instruction execution, memory management, and I/O operations, in a simplified environment. This project will allow users to write and run assembly programs on a simulated CPU.

## 2. Project Goals
- To implement a basic instruction set architecture (ISA) with standard operations (e.g., ADD, SUB, LOAD, STORE).
- To simulate core CPU components, including an ALU, registers, program counter, and memory management.
- To support basic I/O operations.
- To optimize performance through pipelining and other techniques.

## 3. Key Features
- **Instruction Set**: A set of basic instructions for arithmetic, data transfer, and control flow.
- **ALU**: Handles arithmetic and logical operations.
- **Registers**: General-purpose registers for temporary storage.
- **Program Counter**: Tracks the address of the current instruction.
- **Memory Management**: Simulated memory space for instruction and data storage.
- **Input/Output**: Emulated keyboard input and display output.

## 4. Technology and Tools
- **Programming Language**: C++ (for low-level memory management).
- **Development Environment**: Visual Studio Code or other preferred IDE.
- **Version Control**: GitHub for collaboration and version management.
- **Documentation**: Markdown for text documentation and PPT for presentation.

---



**Technology and Tool Choices**:

- **Programming Language**: We chose **C++** because it provides low-level access to memory, making it suitable for emulating CPU architecture. Additionally, C++ is efficient and widely used in system programming.
- **Development Environment**: We will use **Visual Studio Code** as it is a lightweight and powerful IDE with excellent support for C++.
- **Version Control**: We will use **GitHub** for tracking project progress and for team collaboration. GitHub will store our codebase, documentation, and weekly submissions.
- **Documentation**: We will use Markdown for text-based documentation to keep our project organized and PPT for the final presentation.


## Project Folder Structure

Our project files are organized in a way that keeps everything neat and easy to find. Here’s how it’s set up:

    Virtual_CPU_Emulator/
    
    ├── README.md           # Overview of the project and setup instructions
    ├── Weekly Progress     # Folder for tracking progress each week
    │       ├── Week1       # Folder for Week 1’s goals and notes
    │       ├── Week2       # Folder for Week 2’s work
    │       ├── Week3       # And so on, each week’s work gets its own folder
    ├── docs/               # All documentation goes here
    ├── src/                # The main source code for the emulator ( i.e ALU,Memory,Register etc)
    ├── tests/              # Test programs to check if everything works
    └── results/            # Any profiling data, results, or debug logs

