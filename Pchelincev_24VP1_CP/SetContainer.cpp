#include "SetContainer.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

SetContainer::SetContainer() {}

SetContainer::SetContainer(int count, int min, int max)
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

bool SetContainer::IsEmpty() 
{
    return elements.empty();
}

bool SetContainer::IsMember(int val) 
{
    return elements.find(val) != elements.end();
}

void SetContainer::Add(int val) 
{
    elements.insert(val);
}

int SetContainer::GetPower() 
{
    return elements.size();
}

string SetContainer::ToString(string delimiter) 
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

SetContainer* SetContainer::Copy() 
{
    SetContainer* newSet = new SetContainer();
    newSet->elements = this->elements;
    return newSet;
}

bool SetContainer::IsSubset(SetContainer* otherSet) 
{
    if (otherSet->IsEmpty()) return false;

    for (int elem : elements) {
        if (!otherSet->IsMember(elem)) return false;
    }

    return true;
}

bool SetContainer::IsEquivalent(SetContainer* otherSet) 
{
    return (this->IsSubset(otherSet) && otherSet->IsSubset(this));
}

SetContainer* SetContainer::Union(SetContainer* otherSet) 
{
    if (this->IsEmpty()) return otherSet->Copy();
    if (otherSet->IsEmpty()) return this->Copy();

    SetContainer* resultSet = new SetContainer();

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

SetContainer* SetContainer::Intersection(SetContainer* otherSet) 
{
    if (this->IsEmpty() || otherSet->IsEmpty()) return new SetContainer();

    SetContainer* resultSet = new SetContainer();

    for (int elem : elements)
    {
        if (otherSet->IsMember(elem)) 
        {
            resultSet->Add(elem);
        }
    }

    return resultSet;
}

SetContainer* SetContainer::Difference(SetContainer* otherSet)
{
    if (this->IsEmpty()) return new SetContainer();
    if (otherSet->IsEmpty()) return this->Copy();

    SetContainer* resultSet = new SetContainer();

    for (int elem : elements)
    {
        if (!otherSet->IsMember(elem))
        {
            resultSet->Add(elem);
        }
    }

    return resultSet;
}

SetContainer* SetContainer::SymmetricDifference(SetContainer* otherSet)
{
    SetContainer* unionSet = this->Union(otherSet);
    SetContainer* intersectionSet = this->Intersection(otherSet);
    SetContainer* resultSet = unionSet->Difference(intersectionSet);

    delete unionSet;
    delete intersectionSet;

    return resultSet;
}

SetContainer* SetContainer::CreateEmpty() 
{
    return new SetContainer();
}

SetContainer* SetContainer::Create(int count, int min, int max) 
{
    return new SetContainer(count, min, max);
}