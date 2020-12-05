#pragma once
#include "NandGateColumn.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "math.h"
#include <algorithm>

using namespace std;
/*
Author: Ethan Steidl
This gate array replicates a simple B18 FPGA (Field-Programmable Gate Array)
The inner workings of the array implements NAND gates.
When using this object, designate the number of input and output pins
Also designate the amound of rows and columns of nand gates.

Next an input file must be fed into the object to link pins to gates.
Input File description:

gate count = rows * columns
functional pin count = input pin count + gate count
functional pins include all input pins followed by all gate output pins
for example If there are three input pins and 4 gates
0,1,2 = input pints 3,4,5,6 = gate pins

Connection pin count = gates * 2
connection pins represent what pins are connected to each gate
connection pins are numberd where each set of two connections represents
the next gate where gates are ordered from top to bottom for the first to last column

display pins are what the user sees at the end. the index starts at the last index
of the connection pins

When wireing link a functional pin to a connection pin.
functional pins can be linked to display pins

Example: assume inputs=4 rows = 2 columns = 2 ouputs = 4
Functional pins inputs(0,1,2,3) gate outpus(4,5,6,7)
connection pins (0,1,2,3,4,5,6,7)
display pins (8,9,10,11)
 Wiring File example (only number space number):

 0 0
 0 1 This has linked input pin 0 to both inputs of NAND 1
 1 2
 2 3 This has linked pins 1 and 2 to both inputs of NAND 2
 4 4
 5 5 This has linked both NAND outputs to inputs of NAND 3
 6 8
 6 9
 6 10 This has linked the last NAND ouput to display pins 8,9,10

 */
class GateArray
{
private:

	NandGateColumn column;		//Nand gate array
	vector<int> out_pins;		//output pins
	vector<int> display_pins;	//display pins
	int count_inputs;			//input pin count
	int count_rows;				//row count
	int count_cols;				//column count
	int count_outputs;			//output pin count

public:

	GateArray(int new_j, int new_k, int new_m, int new_n, char* infile);
	int inputCount();
	int outputCount();
	string results();
	void operate(vector<int> pins);
	string row_output();
	vector<int> get_single_row(vector<int>& input_pin_values);

};

