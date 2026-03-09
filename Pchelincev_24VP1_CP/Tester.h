#pragma once
#include "TableResults.h"

class Tester
{
private:
	int power1;
	int power2;
	TableResults currentTable;
public:
	Tester();
	Tester(int p1, int p2);
	void runTest();
	TableResults getResultsTable();
};