#include <iostream>
#include <ctime>
#include <math.h>
#include <fstream>

using namespace std;

class TestGenerator{
public:


private:
	bool isT0();
	bool isT1();
	bool isMonotonic(bool *n1, bool *n2, int len);
	bool isLinear(const bool *arr, int len);
	bool isSelfDual();
};