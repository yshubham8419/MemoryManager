// first_fit_memory_manager.cpp

#include <MemoryManager.h>
#include <MemoryBlock.h>
#include <iostream>

MemoryManager::MemoryManager(int total_size) {
    MemoryBlock block(total_size);
    blocks.append(block);
}

MemoryManager::~MemoryManager() {
    blocks.clear();
}

bool MemoryManager::allocate(process& proc) {
    auto node = findNode(proc.size);

    if (node == nullptr) {
        return false; // No suitable block found
    }

    MemoryBlock& block = node->data;

    if (block.size == proc.size) {
        block.allocated = true;
        block.highlighted=true;
        proc.memory_node = node;
        block.id = proc.id;
        return true;
    } else {
        block.allocated = true;
        block.highlighted=true;
        block.id = proc.id;
        proc.memory_node = node;
        MemoryBlock new_block(block.size - proc.size);
        new_block.highlighted=true;
        block.size = proc.size;
        blocks.insertAfter(node, new_block);

        return true;
    }
}

void MemoryManager::deallocate(process proc) {
    Node<MemoryBlock> *memory_node = proc.memory_node;
    memory_node->data.allocated=false;
    if(memory_node->next && !(memory_node->next->data.allocated)){
        #ifdef NEXT_FIT
            if(nextFitIterator == (memory_node->next)){
                nextFitIterator = memory_node;
            }
        #endif
        memory_node->data.size += memory_node->next->data.size;
        blocks.remove(memory_node->next);
        
    }
    if(memory_node->prev && !(memory_node->prev->data.allocated)){
        #ifdef NEXT_FIT
            if(nextFitIterator == memory_node){
                nextFitIterator = (memory_node->prev);
            }
        #endif
        memory_node->prev->data.size += (memory_node->data.size);
        blocks.remove(memory_node);
    }
}
Node<MemoryBlock> *MemoryManager::findNode(int size){

    //first fit
    #ifdef FIRST_FIT
    auto itr = blocks.head;
    while (itr != nullptr) {
        MemoryBlock& block = itr->data;

        if (!block.allocated && block.size >= size) {
            return itr;
        }

        itr = itr->next;
    }
    return nullptr; // No suitable block found
    #endif

    #ifdef BEST_FIT
    auto itr = blocks.head;
    Node<MemoryBlock>* bestFitNode = nullptr;
    int bestFitSize = INT32_MAX;

    while (itr != nullptr) {
        MemoryBlock& block = itr->data;

        if (!block.allocated && block.size >= size && block.size < bestFitSize) {
            bestFitNode = itr;
            bestFitSize = block.size;
        }

        itr = itr->next;
    }

    return bestFitNode;
    #endif


    #ifdef NEXT_FIT

    if (!nextFitIterator) {
        nextFitIterator = blocks.head;
    }

    auto itr = nextFitIterator;

    do {
        MemoryBlock& block = itr->data;

        if (!block.allocated && block.size >= size) {
            nextFitIterator = itr; // Update the next fit iterator
            return itr;
        }

        itr = itr->next ? itr->next : blocks.head; // Move to the next block or wrap around to the beginning

    } while (itr != nextFitIterator);

    return nullptr; // No suitable block found
    #endif

    #ifdef WORST_FIT
    auto itr = blocks.head;
    Node<MemoryBlock>* worstFitNode = nullptr;
    int worstFitSize = -1; // Initialize with a value that cannot be a valid block size

    while (itr != nullptr) {
        MemoryBlock& block = itr->data;
        if ((!block.allocated) && (block.size >= size) && (block.size > worstFitSize)) {
            worstFitNode = itr;
            worstFitSize = block.size;
        }
        itr = itr->next;
    }
    return worstFitNode;
    #endif
    
    return nullptr;
}
#define RED_TEXT "\033[31m"
#define RESET_TEXT "\033[0m"

void MemoryManager::display(){
    Node<MemoryBlock>* current = blocks.head;
    while (current != nullptr) {
        if (current->data.allocated) {
            std::cout <<((current->data.highlighted)?RED_TEXT:RESET_TEXT)<< "{ pid_" << current->data.id << " : " << current->data.size << " } ";
        } else {
            std::cout <<((current->data.highlighted)?RED_TEXT:RESET_TEXT)<< "{ empty : " << current->data.size << " } ";
        }
        current->data.highlighted=false;
        current = current->next;
    }
    std::cout << std::endl;
}