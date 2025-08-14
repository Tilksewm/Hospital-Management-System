#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Medicine.h"
#include <vector>

// Node for the linked list
struct Node {
    Medicine data;
    Node* next;
    Node(const Medicine& med) : data(med), next(nullptr) {}
};

class LinkedList {
private:


public:
    LinkedList() : head(nullptr) {}
    ~LinkedList();

    Node* head;
    void add(const Medicine& med);
    Node* find(const std::string& name);
    void remove(const std::string& name);
    std::vector<Medicine> toVector() const;
    void clear();
};

#endif
