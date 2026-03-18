#include "Tester.h"
#include <iostream>
#include <chrono>
#include "Node.h"
#include "Set.h"
#include "SetContainer.h"
#include "SetList.h"
#include "SetString.h"
#include "SetUnorderedMultiset.h"
#include <vector>
#include <string.h>

using namespace std;

Tester::Tester()
{
	power1 = 10;
	power2 = 10;
	currentTable = new TableResults();
}

Tester::Tester(int p1, int p2)
{
	if (p1 < 0 || p2 < 0)
	{
		throw string{ "Введенная мощность множеств неверная! Мощность множества должна быть больше 0!" };
	}

	power1 = 10;
	power2 = 10;
	currentTable = new TableResults();
}

void Tester::runTest()
{
	auto start = chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	vector<TableResults::DataStructure> allStructs = TableResults::getAllStructures();
	for (auto structure : allStructs)
	{
		vector<string> values;
		switch (structure)
		{
			case TableResults::DataStructure::SinglyLinkedList:
				values = getAllResNode(power1, power2);
				currentTable->setStructureValues(TableResults::DataStructure::SinglyLinkedList, values);
			case TableResults::DataStructure::CustomList:
				values = Set::getAllResSet(power1, power2);
				currentTable->setStructureValues(TableResults::DataStructure::CustomList, values);
			case TableResults::DataStructure::StdList:
				values = SetList::getAllResList(power1, power2);
				currentTable->setStructureValues(TableResults::DataStructure::StdList, values);
			case TableResults::DataStructure::StdSet:
				values = SetContainer::getAllResSetContainer(power1, power2);
				currentTable->setStructureValues(TableResults::DataStructure::StdSet, values);
			case TableResults::DataStructure::StdString:
				values = SetString::getAllResString(power1, power2);
				currentTable->setStructureValues(TableResults::DataStructure::StdString, values);
			case TableResults::DataStructure::StdUnorderedMultiset:
				values = SetUnorderedMultiset::getAllResUnor(power1, power2);
				currentTable->setStructureValues(TableResults::DataStructure::StdUnorderedMultiset, values);
		}
	}

}

TableResults Tester::getResultsTable()
{
	return *currentTable;
}