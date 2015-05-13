#pragma once
#include <iostream>
#include <fstream>
#include <string>

#define NUMOFNEURONS 5
#define SENSITIVITY 1000
#define THRESHOLD 400
#define PERCENT 0.7

using namespace std;

class NeuroWeb
{
public:
	NeuroWeb(void);

	//������ ���������� ���������� � �������
	void setAmountOfVariables(int value);

	void recognition();

	int * getAnswer();

	void study();


	~NeuroWeb(void);
private:
	struct Neuron
	{
		//��� ������� (���� �� 5 �������)
		string name;

		//������ ������� ������
		int * input;

		//������� �������
		int output;

		//���� ������� (� ������ ����������� �� �����)
		int * memory;

		int weight;
	};

	//���������� ���������� � �������
	int amountOfVariables;
	//����� ������� ��������
	int lengthInputVector;
	//��� ����� ������ (���� ������ ������� �� ���-�� ���������� � �������)
	string memoryFile;

	Neuron neuroWeb[NUMOFNEURONS];
	int answer[NUMOFNEURONS];
	bool recognitionDone;

	void initialStruct();
	//������� ������� ���� ������������ ����
	void memoryReset();
	void memoryRead();
	void inputRead();
	void memorySave();
	int round(double value);
	void calcAnswer();

};

