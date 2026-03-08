#pragma once
#include <string>

class SetString {
private:
    std::string elements;

public:
    SetString();
    SetString(int count, int min, int max);

    bool IsEmpty();
    bool IsMember(int val);
    void Add(int val);
    int GetPower();
    std::string ToString(std::string delimiter);

    SetString* Copy();
    bool IsSubset(SetString* otherSet);
    bool IsEquivalent(SetString* otherSet);
    SetString* Union(SetString* otherSet);
    SetString* Intersection(SetString* otherSet);
    SetString* Difference(SetString* otherSet);
    SetString* SymmetricDifference(SetString* otherSet);

    static SetString* CreateEmpty();
    static SetString* Create(int count, int min, int max);
};