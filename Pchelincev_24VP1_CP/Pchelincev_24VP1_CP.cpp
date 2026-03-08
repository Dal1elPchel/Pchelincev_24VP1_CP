#include "TableResults.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 0xF0);
	system("cls");

	TableResults table;

	int power1, power2;
	cout << "Пчелинцев Д. А. 24ВП1 Курсовая работа" << endl;
	cout << "Введите можность множеств:" << endl;
	cout << "  A: ";
	cin >> power1;
	cout << "  B: ";
	cin >> power2;
	
	table.displayTable(power1, power2);

	return 0;
}