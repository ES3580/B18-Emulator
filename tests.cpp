#include "tests.h"

/*
Author: Ethan Steidl
Runs test cases for program

Return void
*/
void test()
{
	test_D_tier();
	test_C_tier();
	test_B_tier();
	test_A_tier();
}


/*
Author: Ethan Steidl
Tests a set of input pins against their expected result
If input pin count is smaller than what is output, the coresponding value is padded from the found vector

Compares the GateArray ouput to the expected given the input pins. If they match
nothing will output. If failure occures, output will show

param ga (GateArray&) - GateArray representing circuit
param test (vector<int>&) - input pin values
param expected (vector<int>&) - expected output pin values
param msg (string) - Error message to output on test fail

Return void
*/
void test_row(GateArray& ga, vector<int>& test, vector<int>& expected, string msg)
{
	//Gets results from GateArray
	vector<int> results = ga.get_single_row(test);

	//make vectors same size by padding expected output
	if (expected.size() < results.size())
	{
		for (int i = expected.size(); i < (int)results.size(); i++)
		{
			expected.push_back(results[i]);
		}
	}

	//if the expected and found ouputs dont match, output error
	if (expected != ga.get_single_row(test))
	{
		cout << msg << " Incosisstency found\nInput:" << endl;
		for (int i = 0; i < (int)test.size(); i++)
		{
			cout << test[i] << " ";
		}
		cout << "\nExpected Output:" << endl;
		for (int i = 0; i < (int)expected.size(); i++)
		{
			cout << expected[i] << " ";
		}
		cout << "\nDiscoverd Output:" << endl;
		for (int i = 0; i < (int)results.size(); i++)
		{
			cout << results[i] << " ";
		}
		cout << endl << endl;
	}
}

/*
Author: Ethan Steidl
Test cases for tier D

Param none
Returns void
*/
void test_D_tier()
{
	//test 1
	cout << "\nD TIER\n" << endl;
	char infileD[] = "D_tier.txt\0";
	GateArray ga(4, 2, 3, 2, infileD);
	//cout << ga.results();

	string msg = "D test";

	vector<int> test = { 0,0,0,0 };
	vector<int> expected = { 0,0 };
	test_row(ga, test, expected, msg);
	test = { 0,0,0,1 };
	expected = { 0,1 };
	test_row(ga, test, expected, msg);
	test = { 0,0,1,1 };
	expected = { 0,1 };
	test_row(ga, test, expected, msg);
	test = { 1,1,1,1 };
	expected = { 1,1 };
	test_row(ga, test, expected, msg);
	test = { 1,0,0,0 };
	expected = { 0,0 };
	test_row(ga, test, expected, msg);
	test = { 1,1,0,0 };
	expected = { 1,0 };
	test_row(ga, test, expected, msg);
}

/*
Author: Ethan Steidl
Perform test cases for tier C

param none
returns void
*/
void test_C_tier()
{
	//Performs test case 1 XOR gate
	cout << "\nC TIER\n" << endl;
	char infileC1[] = "C_tier_XOR.txt\0";
	GateArray ga(4, 4, 2, 4, infileC1);
	//cout << ga.results();

	string msg = "C XOR";
	vector<int> test = { 0,0,0,0 };
	vector<int> expected = { 0,0,0,0 };
	test_row(ga, test, expected, msg);
	test = { 0,1,0,0 };
	expected = { 1,1,1,1 };
	test_row(ga, test, expected, msg);
	test = { 1,0,0,0 };
	expected = { 1,1,1,1 };
	test_row(ga, test, expected, msg);
	test = { 1,1,0,0 };
	expected = { 0,0,0,0 };
	test_row(ga, test, expected, msg);


	//perform test case 2 2to4 decoder
	char infileC2[] = "C_tier_2_4_Decoder.txt\0";
	ga = GateArray(4, 4, 2, 4, infileC2);
	//cout << ga.results();

	msg = "C 2_4 decoder";
	test = { 0,0,0,0 };
	expected = { 0,1,1,1 };
	test_row(ga, test, expected, msg);
	test = { 0,1,0,0 };
	expected = { 1,0,1,1 };
	test_row(ga, test, expected, msg);
	test = { 1,0,0,0 };
	expected = { 1,1,0,1 };
	test_row(ga, test, expected, msg);
	test = { 1,1,0,0 };
	expected = { 1,1,1,0 };
	test_row(ga, test, expected, msg);
}

/*
Author: Ethan Steidl
Perform test cases for tier B

param none
returns void
*/
void test_B_tier()
{
	//test case 1 XOR
	cout << "\nB TIER\n" << endl;
	char infileB1[] = "B_tier_XOR.txt\0";
	GateArray ga(8, 4, 10, 10, infileB1);
	//cout << ga.results();

	string msg = "B XOR";
	vector<int> test = { 0,0,0,0,0,0,0,0 };
	vector<int> expected = { 0,0,0,0,0,0,0,0,0,0 };
	test_row(ga, test, expected, msg);
	test = { 0,1,0,0,0,0,0,0 };
	expected = { 1,1,1,1,1,1,1,1,1,1 };
	test_row(ga, test, expected, msg);
	test = { 1,0,0,0,0,0,0,0 };
	expected = { 1,1,1,1,1,1,1,1,1,1 };
	test_row(ga, test, expected, msg);
	test = { 1,1,0,0,0,0,0,0 };
	expected = { 0,0,0,0,0,0,0,0,0,0 };
	test_row(ga, test, expected, msg);


	//Test case 2 2to4 decoder
	char infileB2[] = "B_tier_2_4_Decoder.txt\0";
	ga = GateArray(8, 4, 10, 10, infileB2);
	//cout << ga.results();

	msg = "B 2_4 decoder";
	test = { 0,0 };
	expected = { 0,1,1,1 };
	test_row(ga, test, expected, msg);
	test = { 0,1 };
	expected = { 1,0,1,1 };
	test_row(ga, test, expected, msg);
	test = { 1,0 };
	expected = { 1,1,0,1 };
	test_row(ga, test, expected, msg);
	test = { 1,1 };
	expected = { 1,1,1,0 };
	test_row(ga, test, expected, msg);



	//test case 3 4to1 mutiplexer
	char infileB3[] = "B_tier_4_1_Mux.txt\0";
	ga = GateArray(8, 4, 10, 10, infileB3);
	//cout << ga.results();

	msg = "B 4_1 mux";
	test = { 0,0,0,0,0,0 };
	expected = { 0 };
	test_row(ga, test, expected, msg);
	test = { 1,0,0,0,0,0 };
	expected = { 1 };
	test_row(ga, test, expected, msg);
	test = { 0,0,0,0,0,1 };
	expected = { 0 };
	test_row(ga, test, expected, msg);
	test = { 0,1,0,0,0,1 };
	expected = { 1 };
	test_row(ga, test, expected, msg);
	test = { 0,0,0,0,1,1 };
	expected = { 0 };
	test_row(ga, test, expected, msg);
	test = { 0,0,0,1,1,1 };
	expected = { 1 };
	test_row(ga, test, expected, msg);
	test = { 0,0,0,0,1,0 };
	expected = { 0 };
	test_row(ga, test, expected, msg);
	test = { 0,0,1,0,1,0 };
	expected = { 1 };
	test_row(ga, test, expected, msg);


	//Test case 4 full adder
	char infileB4[] = "B_tier_Full_Adder.txt\0";
	ga = GateArray(8, 4, 10, 10, infileB4);
	//cout << ga.results();

	msg = "B Full Adder";
	test = { 0,0,0 };
	expected = { 0,0 };
	test_row(ga, test, expected, msg);
	test = { 0,0,1 };
	expected = { 1,0 };
	test_row(ga, test, expected, msg);
	test = { 0,1,0 };
	expected = { 1,0 };
	test_row(ga, test, expected, msg);
	test = { 1,0,0 };
	expected = { 1,0 };
	test_row(ga, test, expected, msg);
	test = { 1,1,0 };
	expected = { 0,1 };
	test_row(ga, test, expected, msg);
	test = { 1,0,1 };
	expected = { 0,1 };
	test_row(ga, test, expected, msg);
	test = { 0,1,1 };
	expected = { 0,1 };
	test_row(ga, test, expected, msg);
	test = { 1,1,1 };
	expected = { 1,1 };
	test_row(ga, test, expected, msg);


	//Test case 5 4way XOR
	char infileB5[] = "B_tier_4way_XOR.txt\0";
	ga = GateArray(8, 4, 10, 10, infileB5);
	//cout << ga.results();

	msg = "B 4way XOR";
	test = { 0,0,0,0 };
	expected = { 0 };
	test_row(ga, test, expected, msg);
	test = { 0,0,0,1 };
	expected = { 1 };
	test_row(ga, test, expected, msg);
	test = { 0,0,1,0 };
	expected = { 1 };
	test_row(ga, test, expected, msg);
	test = { 0,1,0,0 };
	expected = { 1 };
	test_row(ga, test, expected, msg);
	test = { 1,0,0,0 };
	expected = { 1 };
	test_row(ga, test, expected, msg);
	test = { 0,0,1,1 };
	expected = { 0 };
	test_row(ga, test, expected, msg);
	test = { 0,1,0,1 };
	expected = { 0 };
	test_row(ga, test, expected, msg);
	test = { 0,1,1,0 };
	expected = { 0 };
	test_row(ga, test, expected, msg);
	test = { 1,1,0,0 };
	expected = { 0 };
	test_row(ga, test, expected, msg);
	test = { 1,1,1,1 };
	expected = { 0 };
	test_row(ga, test, expected, msg);
	test = { 1,0,0,1 };
	expected = { 0 };
	test_row(ga, test, expected, msg);
	test = { 1,1,1,0 };
	expected = { 1 };
	test_row(ga, test, expected, msg);
	test = { 1,0,1,1 };
	expected = { 1 };
	test_row(ga, test, expected, msg);
}

/*
Author: Ethan Steidl
Performs test cases for tier A

param none
returns void
*/
void test_A_tier()
{
	//Test case 1 SR latch
	cout << "\nA TIER\n" << endl;
	char infileA1[] = "A_tier_SR.txt\0";
	GateArray ga(2, 1, 2, 2, infileA1);
	//cout << ga.results();

	string msg = "A SR Latch";
	vector<int> test = { 0,0 };
	vector<int> expected = { 1,1 };
	test_row(ga, test, expected, msg);
	test = { 0,1 };
	expected = { 1,0 };
	test_row(ga, test, expected, msg);
	test = { 1,0 };
	expected = { 0,1 };
	test_row(ga, test, expected, msg);


	//Test case 2 full subtractor
	char infileA2[] = "A_tier_Full_Subtractor.txt\0";
	ga = GateArray(4, 4, 4, 2, infileA2);
	//cout << ga.results();

	msg = "A Full Subtractor";
	test = { 0,0,0 };
	expected = { 0,0 };
	test_row(ga, test, expected, msg);
	test = { 0,0,1 };
	expected = { 1,1 };
	test_row(ga, test, expected, msg);
	test = { 0,1,0 };
	expected = { 1,1 };
	test_row(ga, test, expected, msg);
	test = { 0,1,1 };
	expected = { 0,1 };
	test_row(ga, test, expected, msg);
	test = { 1,1,1 };
	expected = { 1,1 };
	test_row(ga, test, expected, msg);
	test = { 1,1,0 };
	expected = { 0,0 };
	test_row(ga, test, expected, msg);
	test = { 1,0,1 };
	expected = { 0,0 };
	test_row(ga, test, expected, msg);
	test = { 1,0,0 };
	expected = { 1,0 };
	test_row(ga, test, expected, msg);

	//test case 3 D latch
	char infileA3[] = "A_tier_D_latch.txt\0";
	ga = GateArray(2, 2, 2, 2, infileA3);
	//cout << ga.results();
}