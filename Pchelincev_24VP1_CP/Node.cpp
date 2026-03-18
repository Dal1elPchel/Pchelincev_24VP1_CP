#include "Node.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "string"
#include <vector>
#include <chrono>

using namespace std;

Node* createEmpty()
{

	return nullptr;
}

bool isEmpty(Node* firstElem)
{
	return firstElem == nullptr;
}

bool isContain(Node* firstElem, int value)
{

	if (isEmpty(firstElem))
	{
		return false;
	}

	Node* current = firstElem;

	while (current != nullptr)
	{
		if (current->value == value)
		{
			return true;
		}

		current = current->next;
	}

	return false;
}

Node* add(Node* firstElem, int value)
{

	if (isContain(firstElem, value))
	{
		return firstElem;
	}

	Node* newNode = new Node;
	newNode->value = value;
	newNode->next = firstElem;

	return newNode;
}

Node* create(int count, int min, int max)
{

	if (count > (max - min + 1))
	{
		throw string{ "Невозможно создать множество: в диапазоне [" +
					  to_string(min) + ", " + to_string(max)};
	}

	Node* newNode = nullptr;

	while (count > 0)
	{
		int randValue = min + rand() % (max - min + 1);

		newNode = add(newNode, randValue);

		if (newNode->value == randValue)
		{
			count--;
		}

	}
	return newNode;
}

int getSize(Node* firstElem)
{

	if (isEmpty(firstElem)) return 0;

	int count = 0;
	Node* current = firstElem;

	while (current != nullptr)
	{
		count++;
		current = current->next;
	}

	return count;
}

string out(Node* firstElem, const string delimiter)
{
	string outString;

	if (isEmpty(firstElem))
	{
		outString = "Пустое множество";
		return outString;
	}

	Node* current = firstElem;

	while (current != nullptr)
	{
		outString += std::to_string(current->value) + delimiter;

		current = current->next;
	}

	outString.pop_back();

	return outString;
}

Node* deleteNode(Node* firstNode)
{
	if (isEmpty(firstNode)) return firstNode;

	Node* tmp;
	Node* prev;
	tmp = firstNode;

	while (tmp != nullptr)
	{

		prev = tmp;
		tmp = tmp->next;
		delete prev;
	}

	return nullptr;
}

Node* copyNode(Node* firstElem)
{
	Node* result = nullptr;
	Node* current = firstElem;

	while (current != nullptr)
	{
		result = add(result, current->value);
		current = current->next;
	}

	return result;
}

bool isSubNode(Node* inNode, Node* outNode)
{
	if (isEmpty(outNode)) return false;

	Node* tmp = inNode;

	while (tmp != nullptr)
	{
		if (!isContain(outNode, tmp->value)) return false;
		tmp = tmp->next;
	}

	return true;
}

bool isEquivalent(Node* inNode, Node* outNode)
{
	
	if (isSubNode(inNode, outNode) && isSubNode(outNode, inNode)) return true;
	return false;
}

Node* Union(Node* firstNode, Node* secondNode)
{
	if (isEmpty(firstNode)) return copyNode(secondNode);
	if (isEmpty(secondNode)) return copyNode(firstNode);

	Node* resultNode = nullptr;
	Node* tmp = firstNode;

	while (tmp != nullptr)
	{
		resultNode = add(resultNode, tmp->value);
		tmp = tmp->next;
	}

	tmp = secondNode;

	while (tmp != nullptr)
	{
		resultNode = add(resultNode, tmp->value);
		tmp = tmp->next;
	}

	return resultNode;
}

Node* Intersection(Node* firstNode, Node* secondNode)
{
	if (isEmpty(firstNode) || isEmpty(secondNode)) return nullptr;

	Node* resultNode = nullptr;
	Node* tmp = firstNode;

	while (tmp != nullptr)
	{
		if (isContain(secondNode, tmp->value))
		{
			resultNode = add(resultNode, tmp->value);
		}

		tmp = tmp->next;
	}

	return resultNode;
}

Node* Difference(Node* firstNode, Node* secondNode)
{
	if (isEmpty(firstNode)) return nullptr;
	if (isEmpty(secondNode)) return copyNode(firstNode);

	Node* resultNode = nullptr;
	Node* tmp = firstNode;

	while (tmp != nullptr)
	{
		if (!isContain(secondNode, tmp->value))
		{
			resultNode = add(resultNode, tmp->value);
		}

		tmp = tmp->next;
	}

	return resultNode;
}

Node* Symmetric_Difference(Node* firstNode, Node* secondNode)
{
	Node* unionNode = Union(firstNode, secondNode);
	Node* intersectionNode = Intersection(firstNode, secondNode);
	Node* result = Difference(unionNode, intersectionNode);

	deleteNode(unionNode);
	deleteNode(intersectionNode);

	return result;
}

vector<string> getAllResNode(int count1, int count2)
{
	auto start = chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	vector<string> values;

	start = chrono::high_resolution_clock::now();
	Node* nodeSetA = create(count1, 0, 100);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	values.push_back(to_string(duration.count()));

	start = chrono::high_resolution_clock::now();
	int power = getSize(nodeSetA);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	values.push_back(to_string(duration.count()));

	start = chrono::high_resolution_clock::now();
	bool isSubAA = isSubNode(nodeSetA, nodeSetA);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	values.push_back(to_string(duration.count()));

	Node* nodeSetB = create(count2, 0, 100);
	start = chrono::high_resolution_clock::now();
	bool isSubAB = isSubNode(nodeSetA, nodeSetB);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	values.push_back(to_string(duration.count()));

	start = chrono::high_resolution_clock::now();
	bool isAA = isEquivalent(nodeSetA, nodeSetA);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	values.push_back(to_string(duration.count()));

	start = chrono::high_resolution_clock::now();
	bool isAB = isEquivalent(nodeSetA, nodeSetB);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	values.push_back(to_string(duration.count()));

	start = chrono::high_resolution_clock::now();
	Node* nodeSetC = Union(nodeSetA, nodeSetB);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	values.push_back(to_string(duration.count()));

	start = chrono::high_resolution_clock::now();
	nodeSetC = Intersection(nodeSetA, nodeSetB);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	values.push_back(to_string(duration.count()));

	start = chrono::high_resolution_clock::now();
	nodeSetC = Difference(nodeSetA, nodeSetB);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	values.push_back(to_string(duration.count()));

	start = chrono::high_resolution_clock::now();
	nodeSetC = Difference(nodeSetB, nodeSetA);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	values.push_back(to_string(duration.count()));

	start = chrono::high_resolution_clock::now();
	nodeSetC = Symmetric_Difference(nodeSetB, nodeSetA);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	values.push_back(to_string(duration.count()));

	return values;
}