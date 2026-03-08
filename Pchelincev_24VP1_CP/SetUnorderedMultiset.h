#pragma once
#include <unordered_set>
#include <string>

class SetUnorderedMultiset {
private:
    std::unordered_multiset<int> elements;

public:
    SetUnorderedMultiset();
    SetUnorderedMultiset(int count, int min, int max);

    bool IsEmpty();
    bool IsMember(int val);
    void Add(int val);
    int GetPower();
    std::string ToString(std::string delimiter);

    SetUnorderedMultiset* Copy();
    bool IsSubset(SetUnorderedMultiset* otherSet);
    bool IsEquivalent(SetUnorderedMultiset* otherSet);
    SetUnorderedMultiset* Union(SetUnorderedMultiset* otherSet);
    SetUnorderedMultiset* Intersection(SetUnorderedMultiset* otherSet);
    SetUnorderedMultiset* Difference(SetUnorderedMultiset* otherSet);
    SetUnorderedMultiset* SymmetricDifference(SetUnorderedMultiset* otherSet);

    static SetUnorderedMultiset* CreateEmpty();
    static SetUnorderedMultiset* Create(int count, int min, int max);
};