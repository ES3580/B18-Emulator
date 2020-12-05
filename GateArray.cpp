#include "GateArray.h"



/*
Author: Ethan Steidl
Creates a NAND gate array with 5 iput parameters. The NAND gate array is
given a set of input and output pins in addition to a width and height.
The connection of how NAND gates are configured is in the infile.
The infile must consist of rows of "pin#" "gate line #". For example
0 0
0 1
2 5

param inputs (int) - input pin count
param rows (int) - rows in gate array
param columns (int) - columns in gate array
param outputs (int) - output pin count
param infile (char*) - configureation file

Returns GateArray object
*/
GateArray::GateArray(int inputs, int rows, int columns, int outputs, char* infile)
{
	//set values
	count_inputs = inputs;
	count_rows = rows;
	count_cols = columns;
	count_outputs = outputs;

	//create a nand gate column
	column = NandGateColumn(count_inputs, count_rows, count_cols, count_outputs);
	
	//set out_pins to all zero
	//out_pins is defined as all array pins that have value
	//this is qual to inputs + outputs + each gates output
	int size = count_inputs + count_outputs + (count_rows * count_cols );
	for (int i = 0; i < size; i++)
	{
		out_pins.push_back(0);
	}

	//read input file
	ifstream fin;
	fin.open(infile);
	if (!fin.is_open())
	{
		cout << "Error opening file" << endl;
		throw(1);
		
	}
	else
	{
		int input_pin, gate_pin;
		while (fin >> input_pin && fin >> gate_pin)
		{
			//sets the connection for each line in the file
			column.set_pin(gate_pin, input_pin);
		}
		
	}
	fin.close();
}

/*
Author: Ethan Steidl
Returns input pin count

Returns (int) count of input pins
*/
int GateArray::inputCount()
{
	return count_inputs;
}

/*
Author: Ethan Steidl
Returns output pin count

Returns (int) count of output pins
*/
int GateArray::outputCount()
{
	return count_outputs;
}


/*
Author: Ethan Steidl
Creates a truth table as a string for the stored circuit.
Columns for each display pin and input pin are shown in the 
truth table.

param none
Returns (string) - outuput results table
*/
string GateArray::results()
{
	//creates a numbered column header for each input pin
	string out;
	out += string(6 * (count_inputs + count_outputs), '-') + '\n';
	for (int i = 0; i < count_inputs; i++)
	{
		if (i < 10)
			out += "  ";
		else
			out += " ";

		out += to_string(i);
		out += "  |";

	}

	//creates a numbered columnm header for each display pin
	//display pins are located at count_rows*count_cols*2 to 
	//(count_rows * count_cols * 2)+count_outputs
	for (int i = (count_rows*count_cols*2); i < (count_rows * count_cols * 2)+count_outputs; i++)
	{
		if (i < 10)
			out += "  ";
		else
			out += " ";

		out += to_string(i);
		out += "  |";

	}
	out += '\n';
	out += string(6 * (count_inputs + count_outputs), '-') + '\n';


	//Create an integer value for the amount of inputs as digits
	int counter = 0;
	int counter_index = 0;
	int max = (int)pow(2, count_inputs);

	//walk through permuting all possible combinations of 1's and 0's
	//bits are shifted out into an input vector to be used to operate
	//on and calculate outputs for the truth table
	for (counter = 0; counter < max; counter++)
	{
		vector<int> v;
		int shifted_counter = counter;
		//bit shift each value out of the number into an input 1 and 0 vector
		for (counter_index = 0; counter_index < count_inputs; counter_index++)
		{
			v.push_back( shifted_counter & 1);
			shifted_counter = shifted_counter >> 1;
		}

		//bits are calculated in reverse order, flip them
		reverse(v.begin(), v.end());

		//operate on input pins
		operate(v);

		//retrive output string and append to truth table
		out += row_output() + "\n";

	}

	//returns truth table as a string
	return out;
}


/*
Author: Ethan Steidl
Calculates the display pins of a single row given a set of input pins

param input_pin_values (<vector<int>&) - input pin values
returns (vector<int>) - display pin values
*/
vector<int> GateArray::get_single_row(vector<int>& input_pin_values)
{
	//Runs simulation circuit
	operate(input_pin_values);
	vector<int> retval;

	//extract display pins and place them in return value
	for (int i = 0; i < count_outputs; i++)
	{
		retval.push_back(display_pins[i]);
	}
	return retval;
}


/*
Author: Ethan Steidl
Formats the ouput of a single row of a table using
already solved ouput and display pins

param none
returns (string) - Formatted row of truth table
*/
string GateArray::row_output()
{
	string out;
	//place input pins and their values
	for (int i = 0; i < count_inputs; i++)
	{
		out += "  ";
		out += to_string(out_pins[i]);
		out += "  |";
	}

	//place display pins and their values
	for (int i = 0; i < count_outputs; i++)
	{
		out += "  ";
		out += to_string(display_pins[i]);
		out += "  |";
	}

	return out;
}

/*
Author: Ethan Steidl
Solves the results of a circuit given a set of input pin values

param pins (vector<int>) - input pin values
returns void
*/
void GateArray::operate(vector<int> pins)
{
	//copies the input pin values into the output pins
	//overrideing previous input pin values
	for (int i = 0; i < (int)pins.size(); i++)
	{
		out_pins[i] = pins[i];
	}

	//operates circuit on the values given
	column.operate(out_pins, display_pins);

}