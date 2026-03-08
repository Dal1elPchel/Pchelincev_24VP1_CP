#pragma once
#include <list>
#include <string>

class SetList 
{
private:
    std::list<int> elements;

public:
    SetList();
    SetList(int count, int min, int max);

    bool IsEmpty();
    bool IsMember(int val);
    void Add(int val);
    int GetPower();
    std::string ToString(std::string delimiter);

    SetList* Copy();
    bool IsSubset(SetList* otherSet);
    bool IsEquivalent(SetList* otherSet);
    SetList* Union(SetList* otherSet);
    SetList* Intersection(SetList* otherSet);
    SetList* Difference(SetList* otherSet);
    SetList* SymmetricDifference(SetList* otherSet);

    static SetList* CreateEmpty();
    static SetList* Create(int count, int min, int max);
};