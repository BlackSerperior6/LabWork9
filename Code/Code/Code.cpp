#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Массив всех гласных букв русского и английского алфавитов
char vowels[] = {'а', 'А', 'е', 'Е', 'ё', 'Ё', 'э', 'Э', 'у', 'У', 'о', 'О', 'ы', 'и', 'И', 'ю', 'Ю', 'я', 'Я', 'a', 'A', 'o', 'O', 'e', 'E', 'i', 'I', 'u', 'U', 'y', 'Y'};

bool CheckForReapets(string *Arr, string element, int index, int size) //Функция поверки элемента массива на повторение
{
	bool flag = false; //Флаг
	int counter = index + 1; //Счетчик, проверки ведем со следующего элемента

	while (counter < size && !flag) //Пока не нашли повтор или же пока не достигли конца массива
	{
		flag = element == Arr[counter]; //Проверить элемент на совпадение
		counter++; //Увеличить счетчик
	}

	return flag; //Вернуть флаг
};

bool IsVowel(char symbol)  //Проверка символа на гласную букву, логика аналогична функции выше
{
	bool flag = false;
	int counter = 0;

	while (counter < 31 && !flag)
	{
		flag = symbol == vowels[counter];
		counter++;
	}

	return flag;
}

bool CheckLine(string String)  //Функция на проверку строки на наличие повторяющихся слов
{
	string Arr[500]; //Массив строк
	int ArrOfStringsCounter = 0; //Счетчик массива
	int counter = 0; //Счетчик
	int size = String.size(); //Размер строки
	string buffer = ""; //Буффер 
	bool flag = false; //Флаг

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

	while (counter < ArrOfStringsCounter && !flag) //Пока не дошли до конца массива строк или же пока не нашли повтор
	{
		if (Arr[counter].size() > 1) //Если строка по счетчику в массиве по размеру больше единицы
			flag = CheckForReapets(&Arr[0], Arr[counter], counter, ArrOfStringsCounter); //То проверяем её на повтор

		counter++; //Увеличиваем счетчик
	}

	return flag; //Возвращаем флаг
}

int main()
{
	setlocale(LC_ALL, "rus"); //Подключаем русский язык

	//Открываем файлы
	ifstream F1("F1.txt"); 
	ofstream F2("F2.txt");

	//Проверка на то, что файлы открылись
	if (!F1.is_open() || !F2.is_open())
	{
		cout << "Не найдены нужные файлы" << endl;
		return 0;
	}

	string buffer;

	//Пока в F1 есть, что читать
	while (getline(F1, buffer))
	{
		if (CheckLine(buffer)) //Если есть одинаковые слова
			F2 << buffer << endl; //Записать в F2
	}

	//Закрыть оба файла
	F1.close();
	F2.close();

	//Открыть второй файл в качестве входного потока
	ifstream F3("F2.txt");

	//Если фаил пустой, то закончить программу
	if (F3.peek() == EOF)
	{
		cout << "В файле F2 не было ничего передано" << endl;
		return 0;
	}

	cout << "Успешно записали все нужные строки в фаил F2" << endl;

	string F3ByLines[500]; //Переменная массива строк
	int ArrayCounter = 0; //Счетчик массива
	int vowelsCounter = 0; //Счетчик кол-ва гласных букв

	while (getline(F3, buffer)) //Пока в третьем файле есть, что читать
	{
		F3ByLines[ArrayCounter] = buffer; //Добавить в массив строку
		ArrayCounter++; //Увеличить счетчик
	}

	string lastLine = F3ByLines[ArrayCounter - 1]; //Получаем последний элемент массива строк (будет равен последней строке F2)

	for (int i = 0; i < lastLine.size() + 1; i++) //Пока не достигли последней строки
	{
		if (IsVowel(lastLine[i])) //Если встретилась гласная буква
			vowelsCounter++; //Увеличить счетчик гласных
	}

	cout << "Кол-во гласных букв в последней строке файла F2: " << vowelsCounter << endl;

	//Закрываем фаил F2
	F3.close();
}
