#include "TableResults.h"
#include "Tester.h"
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
	try
	{

		int power1, power2;
		cout << "Пчелинцев Д. А. 24ВП1 Курсовая работа" << endl;
		cout << "Введите можность множеств:" << endl;
		
		cout << "  A: ";
		while (!(cin >> power1)) {
			cout << "Ошибка! Введите число для A: ";
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		}

		
		cout << "  B: ";
		while (!(cin >> power2)) {
			cout << "Ошибка! Введите число для B: ";
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		}

		Tester* tester = new Tester(power1, power2);
		tester->runTest();

		TableResults tbl = tester->getResultsTable();
		tbl.displayTable();
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	

	return 0;
}