// doubly_linked_list.h

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
    
public:
    Node<T>* head;
    Node<T>* tail;

    DoublyLinkedList();
    ~DoublyLinkedList();

    void insertAfter(Node<T>* prevNode, const T& value);
    void remove(Node<T>* node);
    void clear();
    void append(const T& value);
};

#endif // DOUBLY_LINKED_LIST_H
