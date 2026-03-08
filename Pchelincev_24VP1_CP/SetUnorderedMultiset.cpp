#include "SetUnorderedMultiset.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <unordered_set>

using namespace std;

SetUnorderedMultiset::SetUnorderedMultiset() {}

SetUnorderedMultiset::SetUnorderedMultiset(int count, int min, int max) 
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

        if (!IsMember(randValue))
        {
            Add(randValue);
            count--;
        }
    }
}

bool SetUnorderedMultiset::IsEmpty()
{
    return elements.empty();
}

bool SetUnorderedMultiset::IsMember(int val) 
{
    auto range = elements.equal_range(val);
    return range.first != range.second;
}

void SetUnorderedMultiset::Add(int val)
{
    if (!IsMember(val)) 
    {
        elements.insert(val);
    }
}

int SetUnorderedMultiset::GetPower()
{
    return elements.size();
}

string SetUnorderedMultiset::ToString(string delimiter) 
{
    if (IsEmpty()) 
    {
        return "ѕустое множество";
    }

    string result = "";
    for (int elem : elements)
    {
        result += to_string(elem) + delimiter;
    }

    result.pop_back();
    return result;
}

SetUnorderedMultiset* SetUnorderedMultiset::Copy()
{
    SetUnorderedMultiset* newSet = new SetUnorderedMultiset();
    newSet->elements = this->elements;
    return newSet;
}

bool SetUnorderedMultiset::IsSubset(SetUnorderedMultiset* otherSet) 
{
    if (otherSet->IsEmpty()) return false;

    
    unordered_multiset<int> otherElements = otherSet->elements;

    for (auto it = elements.begin(); it != elements.end(); ++it)
    {
        int val = *it;
        int countThis = elements.count(val);
        int countOther = otherElements.count(val);

        if (countThis > countOther) return false;
    }

    return true;
}

bool SetUnorderedMultiset::IsEquivalent(SetUnorderedMultiset* otherSet)
{
    return (this->IsSubset(otherSet) && otherSet->IsSubset(this));
}

SetUnorderedMultiset* SetUnorderedMultiset::Union(SetUnorderedMultiset* otherSet)
{
    if (this->IsEmpty()) return otherSet->Copy();
    if (otherSet->IsEmpty()) return this->Copy();

    SetUnorderedMultiset* resultSet = new SetUnorderedMultiset();

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

SetUnorderedMultiset* SetUnorderedMultiset::Intersection(SetUnorderedMultiset* otherSet)
{
    if (this->IsEmpty() || otherSet->IsEmpty()) return new SetUnorderedMultiset();

    SetUnorderedMultiset* resultSet = new SetUnorderedMultiset();

    unordered_set<int> uniqueElements;
    for (int elem : elements) 
    {
        uniqueElements.insert(elem);
    }

    for (int val : uniqueElements)
    {
        int countThis = elements.count(val);
        int countOther = otherSet->elements.count(val);
        int minCount = min(countThis, countOther);

        for (int i = 0; i < minCount; i++)
        {
            resultSet->Add(val);
        }
    }

    return resultSet;
}

SetUnorderedMultiset* SetUnorderedMultiset::Difference(SetUnorderedMultiset* otherSet) 
{
    if (this->IsEmpty()) return new SetUnorderedMultiset();
    if (otherSet->IsEmpty()) return this->Copy();

    SetUnorderedMultiset* resultSet = new SetUnorderedMultiset();

    unordered_multiset<int> otherElements = otherSet->elements;

    for (int val : elements)
    {
        auto it = otherElements.find(val);
        if (it == otherElements.end()) 
        {
            resultSet->Add(val);
        }
        else 
        {
            otherElements.erase(it);
        }
    }

    return resultSet;
}

SetUnorderedMultiset* SetUnorderedMultiset::SymmetricDifference(SetUnorderedMultiset* otherSet)
{
    SetUnorderedMultiset* unionSet = this->Union(otherSet);
    SetUnorderedMultiset* intersectionSet = this->Intersection(otherSet);
    SetUnorderedMultiset* resultSet = unionSet->Difference(intersectionSet);

    delete unionSet;
    delete intersectionSet;

    return resultSet;
}

SetUnorderedMultiset* SetUnorderedMultiset::CreateEmpty() 
{
    return new SetUnorderedMultiset();
}

SetUnorderedMultiset* SetUnorderedMultiset::Create(int count, int min, int max) 
{
    return new SetUnorderedMultiset(count, min, max);
}