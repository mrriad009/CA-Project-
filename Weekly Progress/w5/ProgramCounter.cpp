class ProgramCounter {
private:
    int counter;
public:
    ProgramCounter() : counter(0) {}
    void increment() { counter++; }
    void set(int address) { counter = address; }
    int get() const { return counter; }
};
