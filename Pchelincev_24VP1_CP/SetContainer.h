#pragma once
#include <set>
#include <string>

class SetContainer {
private:
    std::set<int> elements;

public:
    SetContainer();
    SetContainer(int count, int min, int max);

    bool IsEmpty();
    bool IsMember(int val);
    void Add(int val);
    int GetPower();
    std::string ToString(std::string delimiter);

    SetContainer* Copy();
    bool IsSubset(SetContainer* otherSet);
    bool IsEquivalent(SetContainer* otherSet);
    SetContainer* Union(SetContainer* otherSet);
    SetContainer* Intersection(SetContainer* otherSet);
    SetContainer* Difference(SetContainer* otherSet);
    SetContainer* SymmetricDifference(SetContainer* otherSet);

    static SetContainer* CreateEmpty();
    static SetContainer* Create(int count, int min, int max);
};