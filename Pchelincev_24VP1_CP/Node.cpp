#include "Node.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "string"

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

Node* create(int count, int min, int max, bool isA)
{

	int avaliableCount = 0;
	if (isA)
	{
		int minAvaliable = min;
		if (minAvaliable % 2 != 0) minAvaliable++;

		int maxAvaliable = max;
		if (maxAvaliable % 2 != 0) maxAvaliable--;

		if (minAvaliable <= maxAvaliable) avaliableCount = (maxAvaliable - minAvaliable) / 2 + 1;
	}
	else
	{
		int minAvaliable = min;
		int remainder = minAvaliable % 4;
		if (remainder != 0) minAvaliable += (4 - remainder);

		int maxAvaliable = max;
		remainder = maxAvaliable % 4;
		if (remainder != 0) maxAvaliable -= remainder;

		if (minAvaliable <= maxAvaliable) avaliableCount = (maxAvaliable - minAvaliable) / 4 + 1;
	}

	if (count > avaliableCount)
	{
		string condition = isA ? "четных" : "кратных 4";
		throw string{ "Невозможно создать множество: в диапазоне [" +
					  to_string(min) + ", " + to_string(max) + "] недостаточно " +
					  condition + " чисел (нужно " + to_string(count) +
					  ", доступно " + to_string(avaliableCount) + ")" };
	}

	Node* newNode = nullptr;

	while (count > 0)
	{
		int randValue = min + rand() % (max - min + 1);

		bool cond = isA ? (randValue % 2 == 0) : (randValue % 4 == 0);

		if (cond)
		{
			newNode = add(newNode, randValue);

			if (newNode->value == randValue)
			{
				count--;
			}
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