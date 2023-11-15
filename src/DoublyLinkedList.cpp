// doubly_linked_list.cpp

#include <DoublyLinkedList.h>
#include <MemoryBlock.h>

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template <typename T>
void DoublyLinkedList<T>::insertAfter(Node<T>* prevNode, const T& value) {
    if (!prevNode) {
        std::cerr << "Error: Cannot insert after a null node." << std::endl;
        return;
    }

    Node<T>* newNode = new Node<T>(value);
    newNode->prev = prevNode;
    newNode->next = prevNode->next;

    if (prevNode->next) {
        prevNode->next->prev = newNode;
    } else {
        tail = newNode;
    }

    prevNode->next = newNode;
}

template <typename T>
void DoublyLinkedList<T>::remove(Node<T>* node) {
    if (!node) {
        std::cerr << "Error: Cannot remove a null node." << std::endl;
        return;
    }

    if (node->prev) {
        node->prev->next = node->next;
    } else {
        head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        tail = node->prev;
    }

    delete node;
}

template <typename T>
void DoublyLinkedList<T>::clear() {
    Node<T>* current = head;
    Node<T>* next;
    while (current) {
        next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
}

template <typename T>
void DoublyLinkedList<T>::append(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (!head) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

// Explicit instantiation to avoid linker issues
template class DoublyLinkedList<MemoryBlock>;  // Change int to the desired type

// Add explicit instantiation for other types if needed
