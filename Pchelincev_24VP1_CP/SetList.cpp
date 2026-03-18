#include "SetList.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>
#include <chrono>
#include <string>

using namespace std;

SetList::SetList() {}

SetList::SetList(int count, int min, int max) 
{
    int availableCount = max - min + 1;

    if (count > availableCount) 
    {
        throw string{ "Ќевозможно создать множество: в диапазоне [" +
                      to_string(min) + ", " + to_string(max) +
                      "] недостаточно чисел (нужно " + to_string(count) +
                      ", доступно " + to_string(availableCount) + ")" };
    }

    srand(time(nullptr));

    while (count > 0) 
    {
        int randValue = min + rand() % (max - min + 1);

        int oldPower = GetPower();
        Add(randValue);

        if (GetPower() > oldPower)
        {
            count--;
        }
    }
}

bool SetList::IsEmpty() 
{
    return elements.empty();
}

bool SetList::IsMember(int val)
{
    for (int elem : elements) 
    {
        if (elem == val) return true;
    }
    return false;
}

void SetList::Add(int val) 
{
    if (!IsMember(val)) {
        elements.push_back(val);
    }
}

int SetList::GetPower() 
{
    return elements.size();
}

string SetList::ToString(string delimiter) 
{
    if (IsEmpty()) 
    {
        return "ѕустое множество";
    }

    string result =  "";
    for (int elem : elements)
    {
        result += to_string(elem) + delimiter;
    }

    result.pop_back();
    return result;
}

SetList* SetList::Copy()
{
    SetList* newSet = new SetList();
    newSet->elements = this->elements;
    return newSet;
}

bool SetList::IsSubset(SetList* otherSet)
{
    if (otherSet->IsEmpty()) return false;

    for (int elem : elements) 
    {
        if (!otherSet->IsMember(elem)) return false;
    }

    return true;
}

bool SetList::IsEquivalent(SetList* otherSet) 
{
    return (this->IsSubset(otherSet) && otherSet->IsSubset(this));
}

SetList* SetList::Union(SetList* otherSet) 
{
    if (this->IsEmpty()) return otherSet->Copy();
    if (otherSet->IsEmpty()) return this->Copy();

    SetList* resultSet = new SetList();

    for (int elem : elements)
    {
        resultSet->Add(elem);
    }

    for (int elem : otherSet->elements) 
    {
        resultSet->Add(elem);
    }

    return resultSet;
}

SetList* SetList::Intersection(SetList* otherSet)
{
    if (this->IsEmpty() || otherSet->IsEmpty()) return new SetList();

    SetList* resultSet = new SetList();

    for (int elem : elements) 
    {
        if (otherSet->IsMember(elem))
        {
            resultSet->Add(elem);
        }
    }

    return resultSet;
}

SetList* SetList::Difference(SetList* otherSet) 
{
    if (this->IsEmpty()) return new SetList();
    if (otherSet->IsEmpty()) return this->Copy();

    SetList* resultSet = new SetList();

    for (int elem : elements) 
    {
        if (!otherSet->IsMember(elem)) 
        {
            resultSet->Add(elem);
        }
    }

    return resultSet;
}

SetList* SetList::SymmetricDifference(SetList* otherSet) 
{
    SetList* unionSet = this->Union(otherSet);
    SetList* intersectionSet = this->Intersection(otherSet);
    SetList* resultSet = unionSet->Difference(intersectionSet);

    delete unionSet;
    delete intersectionSet;

    return resultSet;
}

SetList* SetList::CreateEmpty()
{
    return new SetList();
}

SetList* SetList::Create(int count, int min, int max)
{
    return new SetList(count, min, max);
}

vector<string> SetList::getAllResList(int count1, int count2)
{
    auto start = chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    vector<string> values;

    start = chrono::high_resolution_clock::now();
    SetList* SetA = new SetList(count1, 0, 100);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    values.push_back(to_string(duration.count()));

    start = chrono::high_resolution_clock::now();
    int power = SetA->GetPower();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    values.push_back(to_string(duration.count()));

    start = chrono::high_resolution_clock::now();
    bool isSubAA = SetA->IsSubset(SetA);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    values.push_back(to_string(duration.count()));

    SetList* SetB = new SetList(count2, 0, 100);
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
    SetList* SetC = SetA->Union(SetB);
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
