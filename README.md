# B18-Emulator
B18 Emulator

This emulator is meant to replicate the B18 Gate Array

## Usage

This repository does not require the b18.cpp, tests.cpp, or tests.h to run the emulator
In addition, all the .txt files in this repository are sample circuits. These circuits are described
when runnint b18.cpp in the prebuilt circuits tab.

To use this project, place GateArray.cpp .h, and NandGateColumn.cpp .h in your working directory.
Type "#include "GateArray.h" to have access to the proejct. Next call the GateArray constructor passing
it five variables. The input count, row count, column count, and output count, and wiring file.
The class then has two main public functions. GateArray.results() will print a truth table of the circuit.
GateArray.get_single_row() will, given a vector of integers 0-1 representing input pin values, will return
a vector of integers 0-1 representing output pin values.


