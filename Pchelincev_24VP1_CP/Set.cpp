#include "Set.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

Set::Set() 
{
    Start = nullptr;
}

Set::Set(int count, int min, int max) 
{
    Start = nullptr;


    int avaliableCount = max - min + 1;

    if (count > avaliableCount) 
    {
        throw string{ "Ќевозможно создать множество: в диапазоне [" +
                      to_string(min) + ", " + to_string(max) + "] недостаточно чисел (нужно " +
                      to_string(count) + ", доступно " + to_string(avaliableCount) + ")" };
    }

    srand(time(nullptr));

    while (count > 0) 
    {
        int randValue = min + rand() % (max - min + 1);

        int oldPower = getPower();
        Add(randValue);

        if (getPower() > oldPower) 
        {
            count--;
        }
    }
}

Set::~Set() 
{
    Node* current = Start;
    while (current != nullptr)
    {
        Node* temp = current;
        current = current->Next;
        delete temp;
    }
    Start = nullptr;
}

bool Set::IsEmpty() 
{
    return Start == nullptr;
}

bool Set::IsMember(int val) 
{
    Node* current = Start;
    while (current != nullptr) 
    {
        if (current->Data == val) 
        {
            return true;
        }
        current = current->Next;
    }
    return false;
}

void Set::Add(int val) 
{
    if (IsMember(val)) 
    {
        return;
    }

    Node* newNode = new Node;
    newNode->Data = val;
    newNode->Next = Start;
    Start = newNode;
}

int Set::getPower() 
{
    int count = 0;
    Node* current = Start;
    while (current != nullptr)
    {
        count++;
        current = current->Next;
    }
    return count;
}

string Set::toString(string delimitor) 
{
    string outString;

    if (IsEmpty()) {
        outString = "ѕустое множество";
        return outString;
    }

    Node* current = Start;
    while (current != nullptr) 
    {
        outString += to_string(current->Data) + delimitor;
        current = current->Next;
    }

    outString.pop_back();

    return outString;
}

Set* Set::CreateEmpty() 
{
    return new Set();
}

Set* Set::Create(int count, int min, int max)
{
    return new Set(count, min, max);
}

Set* Set::Copy()
{
    Set* newSet = new Set();
    Node* current = Start;

    while (current != nullptr)
    {
        newSet->Add(current->Data);
        current = current->Next;
    }

    return newSet;
}

bool Set::IsSubset(Set* otherSet)
{
    if (otherSet->IsEmpty()) return false;

    Node* current = this->Start;
    while (current != nullptr)
    {
        if (!otherSet->IsMember(current->Data)) return false;
        current = current->Next;
    }

    return true;
}

bool Set::IsEquivalent(Set* otherSet)
{
    return (this->IsSubset(otherSet) && otherSet->IsSubset(this));
}

Set* Set::Union(Set* otherSet)
{
    if (this->IsEmpty()) return otherSet->Copy();
    if (otherSet->IsEmpty()) return this->Copy();

    Set* resultSet = new Set();
    Node* current = this->Start;

    while (current != nullptr)
    {
        resultSet->Add(current->Data);
        current = current->Next;
    }

    current = otherSet->Start;
    while (current != nullptr)
    {
        resultSet->Add(current->Data);
        current = current->Next;
    }

    return resultSet;
}

Set* Set::Intersection(Set* otherSet)
{
    if (this->IsEmpty() || otherSet->IsEmpty()) return new Set();

    Set* resultSet = new Set();
    Node* current = this->Start;

    while (current != nullptr)
    {
        if (otherSet->IsMember(current->Data))
        {
            resultSet->Add(current->Data);
        }
        current = current->Next;
    }

    return resultSet;
}

Set* Set::Difference(Set* otherSet)
{
    if (this->IsEmpty()) return new Set();

    if (otherSet->IsEmpty()) return this->Copy();

    Set* resultSet = new Set();
    Node* current = this->Start;

    while (current != nullptr)
    {
        if (!otherSet->IsMember(current->Data))
        {
            resultSet->Add(current->Data);
        }
        current = current->Next;
    }

    return resultSet;
}

Set* Set::SymmetricDifference(Set* otherSet)
{
    Set* unionSet = this->Union(otherSet);
    Set* intersectionSet = this->Intersection(otherSet);
    Set* resultSet = unionSet->Difference(intersectionSet);

    delete unionSet;
    delete intersectionSet;

    return resultSet;
}