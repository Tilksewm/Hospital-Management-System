#include "LinkedList.h"
#include <iostream>

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::add(const Medicine& med) {
    Node* newNode = new Node(med);
    newNode->next = head;
    head = newNode;
}

Node* LinkedList::find(const std::string& name) {
    Node* current = head;
    while (current) {
        if (current->data.name == name) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void LinkedList::remove(const std::string& name) {
    if (!head) return;

    if (head->data.name == name) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;
    while (current->next) {
        if (current->next->data.name == name) {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
            return;
        }
        current = current->next;
    }
}

std::vector<Medicine> LinkedList::toVector() const {
    std::vector<Medicine> vec;
    Node* current = head;
    while (current) {
        vec.push_back(current->data);
        current = current->next;
    }
    return vec;
}

void LinkedList::clear() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}
