#include "NandGateColumn.h"

/*
Author: Ethan Steidl
Default constructor

param none
return NandGateColumn object
*/
NandGateColumn::NandGateColumn()
{

}

/*
Author: Ethan Steidl
Constructor with input, row, column, and output pin counts
Builds NAND gate array of rows by columns with inputs input
pins and outputs output pins.

param inputs (int) - Count of input pins
param rows (int) - Count of rows in array
param cols (int) - Count of columns in array
param outputs (int) - Count of output pins in array
return NandGateColumn object
*/
NandGateColumn::NandGateColumn(int inputs, int rows, int cols, int outputs)
{
	
	count_inputs = inputs;
	count_rows = rows;
	count_cols = cols;
	count_outputs = outputs;
	

	//solve for gate count
	gates = count_rows * count_cols;

	//input connections are wires going to NAND gates,
	//add a spot to the input_connections vector for each gate input
	//pin
	int size = count_rows * count_cols *2  + count_outputs;
	for (int i = 0; i < size; i++)
		input_connections.push_back(0);

	//This is the first output pin to write a gate to
	first_output_pin = count_inputs;
	
}


/*
Author: Ethna Steidl
Given a pin number and vector containing NAND operations already done,
The function will find all NAND operations completed useing the pin.
This operations will be pushed onto a new vector and returned.

param pin (int) - pin to backpropagate data on
param prev_list (&vector<vector<int>>) - NAND operations already done
return occurances (vector<vector<int>>) - NAND operations already done with pin
*/
vector<vector<int>> NandGateColumn::previous_uses(int pin, vector<vector<int>> &prev_list)
{
	vector<vector<int>> occurances;
	//prevlist [0] = operand 1 [1] = operand 2 [2] = ouput pin #
	for (int i = 0; i < prev_list.size(); i++)
	{
		//walks through finding where operand 1 or 2 was pin and adds it to list
		if (prev_list[i][0] == pin || prev_list[i][1] == pin)
		{
			occurances.push_back(prev_list[i]);
		}
	}
	return occurances;
}


/*
Author: Ethna Steidl
Recursive decent on pins that have already been read and need to update
for example if pin 2 and 3 were used to set pin 4 but pin 4 and 5 were used to set pin
2, this would recursivly go back and alter the previous pins using the correct value of
pin 2 for their calculations.

param prev_list (&vector<vector<int>>) - Previous NAND operations performed
param output_pins (&vector<int>) - output pins values

return void
*/
void NandGateColumn::repair_output(vector<vector<int>>& prev_list, vector<int> &output_pins)
{
	//walk through each previous NAND operation
	for (int i = 0; i < prev_list.size(); i++)
	{
		//extract operands
		int pin = prev_list[i][2];
		int connectionA = prev_list[i][0];
		int connectionB = prev_list[i][1];

		//nand the operands and set the appropriave corrected value
		output_pins[pin] = nand(output_pins[connectionA], output_pins[connectionB]);

		//find where this corrected value has been previously used
		vector<vector<int>> past_uses = previous_uses(pin, prev_list);

		//correct new value there
		if (past_uses.size() > 0)
		{
			repair_output(past_uses, output_pins);
		}
	}

}

/*
Author: Ethna Steidl
Performs a NAND operation on all the connection pins that are linked.
The result is placed on the appropriate ouput_pins. If the output would
be a display pin, it is placed there instead. Display pins are what the user
would see as output from the Gate Array.

param output_pins (&vector<int>) - 0 or 1 values for the state of the output 
								   pin at an index
param disp_pins (&vector<int>) - 0 or 1 values for the state of the display 
								   pin at an index
return void
*/
void NandGateColumn::operate(vector<int>& output_pins, vector<int>& disp_pins)
{
	//clears out display pins since this method using appending later
	disp_pins.clear();

	//This is the first pin to output that does not interfere with input pins
	int pin = first_output_pin;

	//Walk through each gate applying the nand operation to its tied components
	//input connections are the wire number associated to what input pin #
	int i = 0;
	vector<vector<int>> previous_list;
	for (; i < gates*2; i+=2) 
	{
		//Create an entry of input pins used to solve a output pin
		vector<int> entry = { input_connections[i] , input_connections[i + 1], pin };
		
		//perform NAND on two connected pins and save it to the correct output pin
		output_pins[pin] = nand(output_pins[input_connections[i]], output_pins[input_connections[i + 1]]);

		//find where output pin has been used as a connection previously
		vector<vector<int>> past_uses = previous_uses(pin, previous_list);

		//Recursive decent on pins that have already been read from and just now updated
		//for example if pin 2 and 3 were used to set pin 4 but pin 4 and 5 were used to set pin
		//2, this would recursivly go back and alter the previous pins that would have this.
		//The end result is a correct pin representation.
		if (past_uses.size() > 0)
		{
			repair_output(past_uses, output_pins);
		}

		//place our new NAND operation on the previous list
		previous_list.push_back(entry);

		//move to next pin
		pin++;
	}
	
	//set the correct values of the display pins
	for (; i < count_rows*count_cols*2 + count_outputs; i++)
	{
		disp_pins.push_back(output_pins[input_connections[i]]);
	}

}


/*
Author: Ethna Steidl
Sets a gate input to a specifict input pin

param gate_pin (int) - input connection to a gate
param input_pin (int) - pin # that connects to that connection

return void
*/
void NandGateColumn::set_pin(int gate_pin, int input_pin)
{
	input_connections[gate_pin] = input_pin;
}


/*
Author: Ethna Steidl
Nands the inputs and returns result as 0 or 1

param left (int) - left value
param right (int) - right value

return (int) 0 or 1 nand result
*/
int NandGateColumn::nand(int left, int right)
{
	if (left && right)
		return 0;
	return 1;
}