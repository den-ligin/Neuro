#include "TestGenerator.h"

//TestGenerator::TestGenerator(){
//	for(int i =0; i<5; result[i]=false);
//};

bool TestGenerator::isLinear(){
	bool *arr1, *arr2, *temp;
	arr1 = new bool[len];
	arr2 = new bool[len];
	for(int i=0; i<len; i++){
		arr1[i] = function[i];
		arr2[i] = 0;
	}

	for(int j=1; j<len; j++){
		for(int i=0; i<len; i++){
			arr2[len-1-j-i] = (arr1[len-j-i] + arr1[len-1-i-j])%2;
		}
		if( ((j & (j-1)) != 0) && arr2[0]!=0)
			return false;
		temp = arr1;
		arr1 = arr2;
		arr2 = temp;
	}
	return true;
};

bool TestGenerator::isSelfDual(){
	bool z =true;
	for(int i=0; i<len/2; i++){
			if(function[i] == function[len-1 - i]){
				z=false;
				break;
			}
		}
	return z;
};

bool TestGenerator::isMonotonic(bool *n1, bool *n2, int len){
	if(len == 1)
		return n1[0]<=n2[0];
	for(int i=0; i<len; i++){
		if(n1[i]>n2[i])
			return false;
	}
	if(isMonotonic(n1, n1 + (len/2), len/2))
		return isMonotonic(n2, n2 + (len/2), len/2);
	else return false;
};

string TestGenerator::generate(int numOfVar,int numOfTests){
	setlocale(LC_CTYPE, "");
	time_t sec = time(0);
	struct tm * timedate = localtime(&sec);
	string tale = to_string(numOfVar)+"_"+to_string(numOfTests)+"_"+to_string(timedate->tm_mday)+"."+to_string((timedate->tm_mon)+1)+"."+to_string(timedate->tm_year+1900)+"_"+to_string(timedate->tm_hour)+"."+to_string(timedate->tm_min)+".txt";
	ofstream ofInput("Tests/input_"+tale, std::ofstream::out);
	ofstream ofAnswer("Tests/answers_"+tale, std::ofstream::out);
	///////////////
	srand(time(0));
	len = (int)pow(2,numOfVar);
	function = new bool[len];

	for(int j=0; j<numOfTests; j++){
		for(int i=0; i<len; i++)
			function[i] = (rand() % 2 == 0);

		for(int i=0; i<len; i++)
			ofInput<<function[i];
		ofInput<<endl;

		ofAnswer<<isT0()
				<<isT1()
				<<isLinear()
				<<isMonotonic(function, function+(len/2), len/2)
				<<isSelfDual()
				<<endl;
	}
	ofInput.close();
	ofAnswer.close();
	return tale;
};