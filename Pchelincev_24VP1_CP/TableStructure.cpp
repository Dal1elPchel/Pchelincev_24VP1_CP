#include "TableResults.h"

const vector<string> TableResults::OPERATIONS = TableResults::initializeOperations();
const vector<string> TableResults::STRUCTURENAME_LIST = TableResults::initializeStructureNames();
const vector<TableResults::DataStructure> TableResults::STRUCTURE_LIST = TableResults::initializeStructureList();

TableResults::TableResults()
{
	for(const auto& sd : STRUCTURE_LIST)
	{
		DataStructureResults results;
		for (const auto& operation : OPERATIONS)
		{
			results.operations[operation] = "0";
		}
		data[sd] = results;
	}
}

void TableResults::setStructureValues(DataStructure structureName, const vector<string>& values)
{
	if (values.size() != OPERATIONS.size())
	{
		throw runtime_error("Количество значений не соответствует количеству операций");
	}

	if (data.find(structureName) != data.end())
	{
		for (size_t i = 0; i < OPERATIONS.size(); ++i)
		{
			data[structureName].operations[OPERATIONS[i]] = values[i];
		}
	}
}

void TableResults::displayTable() const
{
	const int FIRST_WIDTH_COL = 25;
	const int WIDTH_COL = 20;

	const auto specLine = [FIRST_WIDTH_COL, WIDTH_COL, this]() {
		cout << string(FIRST_WIDTH_COL, '-') << "+";
		for (size_t i = 0; i < STRUCTURE_LIST.size(); i++)
		{
			cout << string(WIDTH_COL, '-') << "+";
		}
		cout << endl;
		};

	specLine();
	cout << left << setw(FIRST_WIDTH_COL) << "|";
	for (const auto& structure : STRUCTURE_LIST)
	{
		cout << "| " << left << setw(WIDTH_COL-1) << TableResults::getStructureName(structure);
	}
	cout << "|" << endl;

	specLine();
	
	for (const auto& operation : OPERATIONS)
	{
		cout << left << setw(FIRST_WIDTH_COL) << operation << "|";

		for (const auto& structure : STRUCTURE_LIST)
		{
			string value = data.at(structure).operations.at(operation);
			cout << " " << left << setw(WIDTH_COL - 1) << value << "|";
		}
		cout << endl;
		specLine();
	}

}

const vector<string>& TableResults::getOperations() const
{
	return OPERATIONS;
}

vector<TableResults::DataStructure> TableResults::getAllStructures()
{
	return STRUCTURE_LIST;
}

string TableResults::getStructureName(DataStructure ds)
{
	size_t index = static_cast<size_t>(ds);
	if (index < STRUCTURENAME_LIST.size())
	{
		return STRUCTURENAME_LIST[index];
	}
	return "Unknown";
}

vector<string> TableResults::initializeOperations()
{
	return {
		"Создание множества",
		"Мощность",
		"Подмножество A-A",
		"Подмножество A-B",
		"Равенство A-A",
		"Равенство A-B",
		"Объединение",
		"Пересечение",
		"Разность A-B",
		"Разность B-A",
		"Симметричная разность"
	};
}

vector<string> TableResults::initializeStructureNames()
{
	return {
		"Односвязный список",
		"Класс 'Список'",
		"List",
		"Set",
		"String",
		"Unordered_multiset"
	};
}

vector<TableResults::DataStructure> TableResults::initializeStructureList()
{
	return {
		 DataStructure::SinglyLinkedList,
		DataStructure::CustomList,
		DataStructure::StdList,
		DataStructure::StdSet,
		DataStructure::StdString,
		DataStructure::StdUnorderedMultiset
	};
}