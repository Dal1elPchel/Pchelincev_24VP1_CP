#include "SetString.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <string>

using namespace std;

vector<int> parseString(const string& str) 
{
    vector<int> result;
    if (str.empty()) return result;

    stringstream ss(str);
    string token;
    while (getline(ss, token, '|'))
    { 
        if (!token.empty())
        {
            result.push_back(stoi(token));
        }
    }
    return result;
}

SetString::SetString() : elements("") {}

SetString::SetString(int count, int min, int max) : elements("") 
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

bool SetString::IsEmpty() 
{
    return elements.empty();
}

bool SetString::IsMember(int val)
{
    if (elements.empty()) return false;

    vector<int> values = parseString(elements);
    for (int v : values)
    {
        if (v == val) return true;
    }
    return false;
}

void SetString::Add(int val) 
{
    if (IsMember(val)) return;

    if (elements.empty()) 
    {
        elements = to_string(val);
    }
    else
    {
        elements += "|" + to_string(val);

        vector<int> values = parseString(elements);
        sort(values.begin(), values.end());

        elements = "";
        for (size_t i = 0; i < values.size(); i++) 
        {
            if (i > 0) elements += "|";
            elements += to_string(values[i]);
        }
    }
}

int SetString::GetPower()
{
    if (elements.empty()) return 0;

    vector<int> values = parseString(elements);
    return values.size();
}

string SetString::ToString(string delimiter)
{
    if (IsEmpty())
    {
        return "ѕустое множество";
    }

    vector<int> values = parseString(elements);
    string result = "";

    for (size_t i = 0; i < values.size(); i++)
    {
        result += to_string(values[i]);
        if (i < values.size() - 1) 
        {
            result += delimiter;
        }
    }

    return result;
}

SetString* SetString::Copy()
{
    SetString* newSet = new SetString();
    newSet->elements = this->elements;
    return newSet;
}

bool SetString::IsSubset(SetString* otherSet)
{
    if (otherSet->IsEmpty()) return false;

    vector<int> thisValues = parseString(this->elements);
    for (int val : thisValues)
    {
        if (!otherSet->IsMember(val)) return false;
    }

    return true;
}

bool SetString::IsEquivalent(SetString* otherSet)
{
    return (this->IsSubset(otherSet) && otherSet->IsSubset(this));
}

SetString* SetString::Union(SetString* otherSet) 
{
    if (this->IsEmpty()) return otherSet->Copy();
    if (otherSet->IsEmpty()) return this->Copy();

    SetString* resultSet = new SetString();

    vector<int> thisValues = parseString(this->elements);
    for (int val : thisValues)
    {
        resultSet->Add(val);
    }

    vector<int> otherValues = parseString(otherSet->elements);
    for (int val : otherValues)
    {
        resultSet->Add(val);
    }

    return resultSet;
}

SetString* SetString::Intersection(SetString* otherSet)
{
    if (this->IsEmpty() || otherSet->IsEmpty()) return new SetString();

    SetString* resultSet = new SetString();

    vector<int> thisValues = parseString(this->elements);
    for (int val : thisValues) 
    {
        if (otherSet->IsMember(val))
        {
            resultSet->Add(val);
        }
    }

    return resultSet;
}

SetString* SetString::Difference(SetString* otherSet) 
{
    if (this->IsEmpty()) return new SetString();
    if (otherSet->IsEmpty()) return this->Copy();

    SetString* resultSet = new SetString();

    vector<int> thisValues = parseString(this->elements);
    for (int val : thisValues) 
    {
        if (!otherSet->IsMember(val))
        {
            resultSet->Add(val);
        }
    }

    return resultSet;
}

SetString* SetString::SymmetricDifference(SetString* otherSet)
{
    SetString* unionSet = this->Union(otherSet);
    SetString* intersectionSet = this->Intersection(otherSet);
    SetString* resultSet = unionSet->Difference(intersectionSet);

    delete unionSet;
    delete intersectionSet;

    return resultSet;
}

SetString* SetString::CreateEmpty()
{
    return new SetString();
}

SetString* SetString::Create(int count, int min, int max)
{
    return new SetString(count, min, max);
}

std::vector<std::string> SetString::getAllResString(int count1, int count2)
{
    auto start = chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    vector<string> values;

    start = chrono::high_resolution_clock::now();
    SetString* SetA = new SetString(count1, 0, 100);
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

    SetString* SetB = new SetString(count2, 0, 100);
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
    SetString* SetC = SetA->Union(SetB);
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
