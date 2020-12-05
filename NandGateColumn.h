#pragma once
#include <vector>
#include <iostream>

using namespace std;

/*
Author: Ethan Steidl
Holds a set of pin connections
When operate is called, the output pin is set to the NAND
of the connecting pins. The display pins are also set during
this process
*/
class NandGateColumn
{
private:

	vector<int> input_connections;	//list of pins that are connected to gate inputs

	int gates;			//gate count

	int count_inputs;	//input pin count
	int count_rows;		//row count
	int count_cols;		//column count
	int count_outputs;	//output pin count

	int first_output_pin;	//first output pin a gate can write to

public:
	NandGateColumn();
	NandGateColumn(int new_j, int new_k, int new_m, int new_n);
	void operate(vector<int> &output_pins, vector<int> &display_pins);
	vector<vector<int>> previous_uses(int pin, vector<vector<int>> &prev_list);
	void repair_output(vector<vector<int>>& prev_list, vector<int>& output_pins);
	void set_pin(int gate_pin, int input_pin);
	int nand(int left, int right);


};