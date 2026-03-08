#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class TableResults
{
public:
	enum class DataStructure
	{
		SinglyLinkedList,
		CustomList,
		StdList,
		StdSet,
		StdString,
		StdUnorderedMultiset
	};

	TableResults();
	void setStructureValues(DataStructure structureName, const vector<string>& values);
	void displayTable(int power1, int power2) const;
	const vector<string>& getOperations() const;
	static vector<DataStructure> getAllStructures();
	static string getStructureName(DataStructure ds);

private:
	struct DataStructureResults
	{
		map<string, string> operations;
	};

	static const vector<string> OPERATIONS;
	static const vector<DataStructure> STRUCTURE_LIST;
	static const vector<string> STRUCTURENAME_LIST;
	map<DataStructure, DataStructureResults> data;

	static vector<string> initializeOperations();
	static vector<string> initializeStructureNames();
	static vector<DataStructure> initializeStructureList();
};