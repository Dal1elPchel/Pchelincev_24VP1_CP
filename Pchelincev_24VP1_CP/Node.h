
#pragma once
#include "string"
#include <vector>

struct Node
{
	int value;
	Node* next;
};

Node* createEmpty();
bool isEmpty(Node* firstElem);
bool isContain(Node* firstElem, int value);
Node* add(Node* firstElem, int value);
Node* create(int count, int min, int max);
int getSize(Node* firstElem);
std::string out(Node* firstElem, const std::string delimiter);
Node* deleteNode(Node* firstSet);
Node* copyNode(Node* firstElem);
bool isSubNode(Node* inSet, Node* outSet);
bool isEquivalent(Node* inSet, Node* outSet);
Node* Union(Node* firstSet, Node* secondSet);
Node* Intersection(Node* firstSet, Node* secondSet);
Node* Difference(Node* firstSet, Node* secondSet);
Node* Symmetric_Difference(Node* firstSet, Node* secondSet);
std::vector<std::string> getAllResNode(int count1, int count2);