#pragma once
#include "string"
#include <vector>

class Set {
private:
    struct Node {
        int Data;
        Node* Next;
    };
    Node* Start;

public:
    Set();
    Set(int count, int min, int max);
    ~Set();

    bool IsEmpty();
    bool IsMember(int val);
    void Add(int val);
    int getPower();
    std::string toString(std::string delimitor);

    Set* Copy();
    bool IsSubset(Set* otherSet);
    bool IsEquivalent(Set* otherSet);
    Set* Union(Set* otherSet);
    Set* Intersection(Set* otherSet);
    Set* Difference(Set* otherSet);
    Set* SymmetricDifference(Set* otherSet);

    static Set* CreateEmpty();
    static Set* Create(int count, int min, int max);
    static std::vector<std::string> getAllResSet(int count1, int count2);
};