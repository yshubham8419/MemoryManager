// process.h

#ifndef PROCESS_H
#define PROCESS_H

#include <DoublyLinkedList.h>
#include <MemoryBlock.h> 
struct process {
    int id;
    int size;
    int arrival_time;
    int execution_time;
    int exit_time;
    Node<MemoryBlock> *memory_node;

    process(int process_id, int process_size, int arrival_t, int exec_time);
    
    bool operator<(const process& other) const;
};
bool operator==(const process& lhs, const process& rhs);

extern process null_process;  // Declaration of null_process

#endif // PROCESS_H