#include <iostream>
#include <fstream>
#include "GateArray.h"
#include <string>
#include "tests.h"
#include <limits>
using namespace std;

void prebuilt_circuit();
void custom_circuit();

/*
Author: Ethan Steidl
B18 Emulator. Allows user to see the truth table of prebuilt B18 circuits.
Users can see the truth table of their designed circuits.
*/
int main()
{
	//test();

	//Print menue and get input
	int option;
	cout << "Welcome to the B18 Emulator! Created by Ethan Steidl.\n\n";
	string menue = "Select and option:\n1) Custom Circuit\n2) Prebuilt Circuit\n3) Run tests\n0) Exit";
	cout << menue << "\n\nChoice: ";
	cin >> option;

	//exits if input is 0
	while (option != 0)
	{
		if (option == 1)
		{
			//Creates custom circuit
			custom_circuit();
		}
		else if (option == 2)
		{
			//Displays prebuilt circut
			prebuilt_circuit();
		}
		else if (option == 3)
		{
			//runs tests
			cout << "No output from test cases is PASS\n";
			test();
		}

		cout << "\n" << menue << "\n\nChoice: ";
		cin >> option;
	}

	return 0;
}

/*
Author: Ethan Steidl
Allows the user to see the truth table of a prebuilt circuit.
The user is also shown the j,k,m, and n parameters of the circuit.
*/
void prebuilt_circuit()
{

	//Display menue and get input
	string menue = "Select a Circuit:\n1) inputs=4 rows=2 columns=3 outputs=2    D grading circuit\n2) inputs=4 rows=4 columns=2 outputs=4    XOR 2 input\n";
	menue += "3) inputs=4 rows=4 columns=2 outputs=4    Decoder 2 to 4\n4) inputs=8 rows=4 columns=10 outputs=10  XOR 2 input\n5) inputs=8 rows=4 columns=10 outputs=10  Decoder 2 to 4\n";
	menue += "6) inputs=8 rows=4 columns=10 outputs=10  Multiplexor 4 to 1\n7) inputs=8 rows=4 columns=10 outputs=10  Full Adder\n8) inputs=8 rows=4 columns=10 outputs=10  XOR 4 input\n";
	menue += "9) inputs=2 rows=1 columns=2 outputs=2    S/R Nand Latch\n10) inputs=4 rows=4 columns=4 outputs=2   Full Subtractor\n11) inputs=2 rows=2 columns=2 outputs=2   D Latch\n0) Exit";

	cout << "\n" << menue << "\n\n" << "Choice: ";
	int choice;
	cin >> choice;

	//if 0 exit
	//Anything else will show the results of a prebuilt circuit
	while (choice != 0)
	{
		if (choice == 1)
		{
			cout << "Description: Performs the circuit stated in the writup for a D." << endl;
			char infileD[] = "D_tier.txt\0";
			GateArray ga(4, 2, 3, 2, infileD);
			cout << ga.results();
		}
		else if (choice == 2)
		{
			cout << "Description: Performs XOR on pin 0 and 1. Output is duplicated on pins 16-19." << endl;
			char infileC1[] = "C_tier_XOR.txt\0";
			GateArray ga(4, 4, 2, 4, infileC1);
			cout << ga.results();
		}
		else if (choice == 3)
		{
			cout << "Description: 2 to 4 decoder from pins 0-1 to pins 16-19." << endl;
			char infileC2[] = "C_tier_2_4_Decoder.txt\0";
			GateArray ga(4, 4, 2, 4, infileC2);
			cout << ga.results();
		}
		else if (choice == 4)
		{
			cout << "Description: Performs XOR on pin 0 and 1. Opuut is duplicated on pins 80-89." << endl;
			char infileB1[] = "B_tier_XOR.txt\0";
			GateArray ga(8, 4, 10, 10, infileB1);
			cout << ga.results();
		}
		else if (choice == 5)
		{
			cout << "Description: 2 to 4 decoder from pins 0-1 to pins 80-83." << endl;
			char infileB2[] = "B_tier_2_4_Decoder.txt\0";
			GateArray ga(8, 4, 10, 10, infileB2);
			cout << ga.results();
		}
		else if (choice == 6)
		{
			cout << "Description: 4 to 1 mux from pins 0-3 to pin 80. Control pins are 4-5." << endl;
			char infileB3[] = "B_tier_4_1_Mux.txt\0";
			GateArray ga(8, 4, 10, 10, infileB3);
			cout << ga.results();
		}
		else if (choice == 7)
		{
			cout << "Description: Performs a full add on pins 0-1 with pin 2 as carry. Ouput is pin 80 carry out is 81." << endl;
			char infileB4[] = "B_tier_Full_Adder.txt\0";
			GateArray ga(8, 4, 10, 10, infileB4);
			cout << ga.results();
		}
		else if (choice == 8)
		{
			cout << "Description: 4 way XOR on pins 0-3. Ouput is duplicated on pins 80-89." << endl;
			char infileB5[] = "B_tier_4way_XOR.txt\0";
			GateArray ga(8, 4, 10, 10, infileB5);
			cout << ga.results();
		}
		else if (choice == 9)
		{
			cout << "Description: SR latch where pin 0 is S and 1 is R. Q outputs on 4 and Not Q on 5." << endl;
			char infileA1[] = "A_tier_SR.txt\0";
			GateArray ga(2, 1, 2, 2, infileA1);
			cout << ga.results();

		}
		else if (choice == 10)
		{
			cout << "Description: Performs a full subtract on pins 0-1 with pin 2 as carry. Ouput is pin 32 carry out is 33." << endl;
			char infileA2[] = "A_tier_Full_Subtractor.txt\0";
			GateArray ga(4, 4, 4, 2, infileA2);
			cout << ga.results();

		}
		else if (choice == 11)
		{
			cout << "Description: D latch where pin 0 is D and 1 is clock. Clock updates before D always in this truth table.\n Q outputs on 8 and Not Q on 9." << endl;
			char infileA3[] = "A_tier_D_latch.txt\0";
			GateArray ga(2, 2, 2, 2, infileA3);
			cout << ga.results();

		}
		cout << "\n" << menue << "\n\n" << "Choice: ";
		cin >> choice;
	}

}

/*
Author: Ethan Steidl
Allows the user to set the parameters of their circuit and upload a circuit file
*/
void custom_circuit()
{
	int inputs;	//input count
	int cols;	//column count
	int rows;	//row count
	int outputs;	//output count
	string name;	//filename

	//get inputs
	cout << "Enter number of inputs: ";
	cin >> inputs;
	cout << "Enter number of gate columns: ";
	cin >> cols;
	cout << "Enter number of gate rows: ";
	cin >> rows;
	cout << "Enter number of outputs: ";
	cin >> outputs;
	cout << "Enter name of wireing file: ";
	cin >> name;

	//convert filename string to c string
	char* c_string;
	c_string = new char[name.length()];
	for (int index = 0; index < (int)name.length(); index++)
	{
		c_string[index] = name[index];
	}
	c_string[name.length()] = '\0';

	//Will load the file with the given parameters
	try
	{
		//loads file with parameters into the gatearray
		GateArray ga(inputs, cols, rows, outputs, c_string);

		//prints menue and gets input
		string menue = "\nSelect and option:\n1) Display truth table\n0) Exit\n\nChoice: ";
		int choice;
		cout << menue;
		cin >> choice;

		//If 0 exit loop
		while (choice != 0)
		{
			if (choice == 1)
			{
				//shows the truth table of the input
				cout << ga.results();
			}

			cout << menue;
			cin >> choice;
		}
	}
	//Catches a failure on file load preventing a crash
	catch (int e)
	{
		e += 1; //THIS does nothing!! removes compile warning for unused var
		cout << "\nAn error occured with the inputs given" << endl;
		return;
	}
}

