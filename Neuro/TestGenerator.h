#include <iostream>
#include <ctime>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

class TestGenerator{
public:
	//TestGenerator(){};
	string generate(int numOfVars,int numOfTests);

private:
	inline bool isT0(){ return !function[0];};
	inline bool isT1(){ return function[len-1];};

	bool isLinear();
	bool isMonotonic(bool *n1, bool *n2, int len);
	bool isSelfDual();
	//////////////////////////////////////////////
	bool *function;
	int len;
};