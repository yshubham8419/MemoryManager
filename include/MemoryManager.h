#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H
#include<Process.h>
#include <DoublyLinkedList.h>

class MemoryManager{
private:    
   DoublyLinkedList<MemoryBlock> blocks;
   Node<MemoryBlock>* findNode(int size);
   #ifdef NEXT_FIT
    Node<MemoryBlock>* nextFitIterator;
   #endif

public:
    MemoryManager(int);
    ~MemoryManager();

    // Simulate the allocation of memory for a process object
    bool allocate(process& proc);

    // Simulate the deallocation of memory for a process object
    void deallocate(process proc);

    // Display the current memory allocation 
    void display();
};

#endif // FIRST_FIT_MEMORY_MANAGER_H
