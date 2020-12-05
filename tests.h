#pragma once

#include <iostream>
#include <fstream>
#include "GateArray.h"
#include <string>

using namespace std;
void test_row(GateArray& ga, vector<int>& test, vector<int>& expected, string msg);
void test_D_tier();
void test_C_tier();
void test_B_tier();
void test_A_tier();
void test();