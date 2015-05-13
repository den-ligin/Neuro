#include "NeuroWeb.h"

NeuroWeb::NeuroWeb(void)
{
	lengthInputVector = 1;
	recognitionDone = false;
}

//По заданному количеству переменных функция сразу устанавливает длину вектора значений.
void NeuroWeb::setAmountOfVariables(int value)
{
	amountOfVariables = value;
	lengthInputVector <<= amountOfVariables;

	memoryFile = "Memory/memory" + to_string(amountOfVariables) + ".txt";

	initialStruct(); 
}

//Функция выделяет память для векторов входных значений, памяти. Задает имена нейронам.
void NeuroWeb::initialStruct()
{
	for (int i = 0; i < NUMOFNEURONS; ++i)
	{
		neuroWeb[i].input = new int[lengthInputVector];
		neuroWeb[i].memory = new int[lengthInputVector];
		neuroWeb[i].output = 0;
		neuroWeb[i].weight = 0;
	}
	neuroWeb[0].name = "T0";
	neuroWeb[1].name = "T1";
	neuroWeb[2].name = "Linear";
	neuroWeb[3].name = "Self-dual";
	neuroWeb[4].name = "Monotonic";

	memoryRead();
}

void NeuroWeb::memoryReset()
{
	ofstream file;
	file.open(memoryFile);
	for (int i = 0; i < NUMOFNEURONS; ++i)
	{
		for (int j = 0; j < lengthInputVector; ++j)
			file << "0 ";
		file << endl;
	}
	file.close();
}

void NeuroWeb::memoryRead()
{
	//Считываем память в массив. Если памяти нет - создаем пустую память и считываем ее.
	if (ifstream(memoryFile) == NULL)
	{
		cout << "The NeuroWeb is not trained." << endl;
		cout << "It was loaded with zero experience." << endl;
		memoryReset();
	}

	ifstream file;
	file.open(memoryFile);
	for (int i = 0; i < NUMOFNEURONS; ++i)
	{
		for (int j = 0; j < lengthInputVector; ++j)
			file >> neuroWeb[i].memory[j];
	}
	file.close();
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!доработать
void NeuroWeb::inputRead()
{
	//Сделать проверку на существование файла

	ifstream inputFile;
	inputFile.open("input.txt");
	for (int i = 0; i < NUMOFNEURONS; ++i)
	{
		for (int j = 0; j < lengthInputVector; ++j)
		{
			int temp;
			inputFile >> temp;
			neuroWeb[i].input[j] = temp * SENSITIVITY;
		}
	}
	inputFile.close();
}

void NeuroWeb::memorySave()
{
	ofstream file;
	file.open(memoryFile);
	for (int i = 0; i < NUMOFNEURONS; ++i)
	{
		for (int j = 0; j < lengthInputVector; ++j)
			file << neuroWeb[i].memory[j] << " ";
		file << endl;
	}
	file.close();
}

int NeuroWeb::round(double value)
{
   return (int)floor(value + 0.5);
}

void NeuroWeb::recognition()
{
	int n, m;

	for (int i = 0; i < NUMOFNEURONS; ++i)
		for (int j = 0; j < lengthInputVector; ++j)
		{
			n = neuroWeb[i].memory[j];
			m = neuroWeb[i].input[j];

			if(abs(m-n) < THRESHOLD)
			{
				neuroWeb[i].weight++;

				//Что-то кладем в память
				if(m != 0)
				neuroWeb[i].memory[j] = round((n+(n+m)/2)/2);
			}
		}

	calcAnswer();
	recognitionDone = true;
}

void NeuroWeb::calcAnswer()
{
	int temp = round(PERCENT * amountOfVariables);

	for (int i = 0; i < NUMOFNEURONS; ++i)
		answer[i] = 0;

	for (int i = 0; i < NUMOFNEURONS; ++i)
		if (neuroWeb[i].weight >= temp)
			answer[i] = 1;
}

int* NeuroWeb::getAnswer()
{
	if (recognitionDone)
		return answer;
	else
		cout << "There was not recognition, please, do it at first." << endl;
}

void NeuroWeb::study()
{
	int n, m;

	memoryRead();
	inputRead();

	for (int i = 0; i < INPUT; ++i)
	{
		n = neuroWeb[mystery].memory[i];
		m = neuroWeb[mystery].input[i];

		if(m != 0)
			neuroWeb[mystery].memory[i] = round((n+(n+m)/2)/2);
	}
}


NeuroWeb::~NeuroWeb(void)
{
}
