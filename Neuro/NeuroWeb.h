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

	//Задать количество переменных в функции
	void setAmountOfVariables(int value);

	void recognition();

	int * getAnswer();

	void study();


	~NeuroWeb(void);
private:
	struct Neuron
	{
		//Имя нейрона (один из 5 классов)
		string name;

		//Массив входных данных
		int * input;

		//Решение нейрона
		int output;

		//Опыт нейрона (в начале считывается из файла)
		int * memory;

		int weight;
	};

	//Количество переменных в функции
	int amountOfVariables;
	//Длина вектора значений
	int lengthInputVector;
	//Имя файла памяти (файл памяти зависит от кол-ва переменных в функции)
	string memoryFile;

	Neuron neuroWeb[NUMOFNEURONS];
	int answer[NUMOFNEURONS];
	bool recognitionDone;

	void initialStruct();
	//Функция удаляет весь накопившийся опыт
	void memoryReset();
	void memoryRead();
	void inputRead();
	void memorySave();
	int round(double value);
	void calcAnswer();

};

