//
// Created by os on 4/22/22.
//
#ifndef PROJECT_BASE_V1_0_MEMORYALLOCATOR_HPP
#define PROJECT_BASE_V1_0_MEMORYALLOCATOR_HPP

#include "../lib/hw.h"

/*struct HeapSegHdr{
    size_t length;
    HeapSegHdr* next;
    HeapSegHdr* last;
    bool free;
    //void CombineForward();
  //  void CombineBackward();
    HeapSegHdr* Split(size_t splitLength);
};

void InitializeHeap(void* heapAddress);

void* malloc(size_t size);
void free(void* address);*/


class MemoryAllocator {

public:

    struct FreeMem {
        FreeMem* next; // Next in the list
        FreeMem* prev; // Previous in the list
        size_t size; // Size of the free fragment
        bool taken;
    };


    static FreeMem *fmem_head;

    static void MemoryAllocatorinit();

    static void *mem_allocMoj(size_t size);

    static int mem_freeMoj(void* ptr);

};



#endif //PROJECT_BASE_V1_0_MEMORYALLOCATOR_HPP
