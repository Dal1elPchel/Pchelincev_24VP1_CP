#include "Set.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <chrono>

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

std::vector<std::string> Set::getAllResSet(int count1, int count2)
{
    auto start = chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    vector<string> values;

    start = chrono::high_resolution_clock::now();
    Set* SetA = new Set(count1, 0, 100);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    values.push_back(to_string(duration.count()));

    start = chrono::high_resolution_clock::now();
    int power = SetA->getPower();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    values.push_back(to_string(duration.count()));

    start = chrono::high_resolution_clock::now();
    bool isSubAA = SetA->IsSubset(SetA);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    values.push_back(to_string(duration.count()));

    Set* SetB = new Set(count2, 0, 100);
    start = chrono::high_resolution_clock::now();
    bool isSubAB = SetA->IsSubset(SetB);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    values.push_back(to_string(duration.count()));

    start = chrono::high_resolution_clock::now();
    bool isAA = SetA->IsEquivalent(SetA);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    values.push_back(to_string(duration.count()));

    start = chrono::high_resolution_clock::now();
    bool isAB = SetA->IsEquivalent(SetB);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    values.push_back(to_string(duration.count()));

    start = chrono::high_resolution_clock::now();
    Set* SetC = SetA->Union(SetB);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    values.push_back(to_string(duration.count()));

    start = chrono::high_resolution_clock::now();
    SetC = SetA->Intersection(SetB);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    values.push_back(to_string(duration.count()));

    start = chrono::high_resolution_clock::now();
    SetC = SetA->Difference(SetB);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    values.push_back(to_string(duration.count()));

    start = chrono::high_resolution_clock::now();
    SetC = SetB->Difference(SetA);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    values.push_back(to_string(duration.count()));

    start = chrono::high_resolution_clock::now();
    SetC = SetB->SymmetricDifference(SetA);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    values.push_back(to_string(duration.count()));

    return values;
}