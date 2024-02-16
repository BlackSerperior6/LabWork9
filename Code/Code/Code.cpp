#include <iostream>
#include <string>
#include <fstream>

using namespace std;

char vowels[] = {'a', 'А', 'у', 'У', 'о', 'О', 'ы', 'и'};

bool CheckForReapets(string *Arr, string element, int index, int size) 
{
	bool flag = false;
	int counter = index + 1;

	while (counter < size && !flag)
	{
		flag = element == Arr[counter];
		counter++;
	}

	return flag;
};

bool CheckLine(string String) 
{
	string Arr[500];
	int counter = 0;
	int size = String.size();
	int ArrOfStringsCounter = 0;
	string buffer = "";
	bool flag = false;

	for (int i = 0; i < size + 1; i++) //Проходим по всей строке
	{
		if (String[i] == ' ' || i == size) //Если текущий элемент - пробел или же достигнут последний элемент
		{
			Arr[ArrOfStringsCounter] = buffer; //Заносим в массив строк значение буффера
			buffer = ""; //Опустошаем буффер
			ArrOfStringsCounter++; //Увеличиваем счетчик кол-ва элементов массива
		}
		else
			buffer += String[i]; //Иначе заносим в буффер текущий символ
	}

	while (counter < size && !flag)
	{
		flag = CheckForReapets(&Arr[0], Arr[counter], counter, ArrOfStringsCounter);
		counter++;
	}

	return flag;
}

int main()
{
	setlocale(LC_ALL, "rus");

	ifstream F1("F1.txt");
	ofstream F2("F2.txt");

	string buffer;

	while (getline(F1, buffer))
	{
		if (CheckLine(buffer))
			F2 << buffer << endl;
	}

	F1.close();
	F2.close();

	ifstream F3("F2.txt");

	string F3ByLines[500];
	int ArrayCounter;
	

	while (getline(F3, buffer))
	{
		F3ByLines[ArrayCounter] = buffer;
		ArrayCounter++;
	}

	for (int i = 0; i < F3ByLines[ArrayCounter].size() + 1; i++)
	{


	}

	F3.close();
}
