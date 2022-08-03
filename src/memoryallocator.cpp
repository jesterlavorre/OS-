//
// Created by os on 4/22/22.
//
#include "../h/memoryallocator.hpp"



MemoryAllocator::FreeMem* MemoryAllocator::fmem_head;

void MemoryAllocator::MemoryAllocatorinit() {

    size_t size = ((size_t)HEAP_END_ADDR - ((size_t)HEAP_START_ADDR));

    fmem_head = (MemoryAllocator::FreeMem*)HEAP_START_ADDR;
    fmem_head->size = size;
    fmem_head ->next = nullptr;
    fmem_head->prev = nullptr;
    fmem_head->taken = false;

}
int tryToJoin (MemoryAllocator::FreeMem* cur) {
        cur->size += cur->next->size;
        cur->next = cur->next->next;
        if (cur->next) cur->next->prev = cur;
        return 1;
}

int MemoryAllocator::mem_freeMoj(void *ptr) {

    MemoryAllocator::FreeMem* help = (MemoryAllocator::FreeMem*)((char*)ptr - sizeof(MemoryAllocator::FreeMem));

    MemoryAllocator::FreeMem* cur = help;

    cur->taken = false;

   /* if(cur->next->taken == false){
        cur->size += cur->next->size;
        cur->next = cur->next->next;
        if (cur->next) cur->next->prev = cur;
    }
    if(cur->prev != nullptr)
    if(cur->prev->taken == false){
        cur->prev->size += cur->size;
        cur->next->prev = cur->prev;
        cur->prev->next = cur->next;
    }*/
    if(cur->prev != nullptr)
        tryToJoin(cur->prev);
    if(cur->next != nullptr)
        tryToJoin(cur);

    return 0;

}
void *MemoryAllocator::mem_allocMoj(size_t size) {
    uint64 realSize = 0;
    MemoryAllocator::FreeMem* p = fmem_head;
    MemoryAllocator::FreeMem* newMem = nullptr;
    if(size < MEM_BLOCK_SIZE){
        realSize = MEM_BLOCK_SIZE;
    }else if((size % MEM_BLOCK_SIZE) != 0){
        realSize = (((size / MEM_BLOCK_SIZE) + 1) * MEM_BLOCK_SIZE);
    }else realSize = size;
    realSize += sizeof(MemoryAllocator::FreeMem);

    for(; p != nullptr; p = p->next){
        if(p->size >= realSize && p->taken == false){
            p->size -= realSize;
            newMem = (MemoryAllocator::FreeMem*)((char*)p + p->size);
            newMem->size = realSize;
            newMem->next = p->next;
            p->next = newMem;
            newMem->prev = p;
            if(newMem->next != nullptr)
            newMem->next->prev = newMem;
            newMem->taken = true;
            break;
        }
    }

    if(newMem != nullptr) return (void*)((char*)newMem + sizeof(MemoryAllocator::FreeMem));
    if(newMem == nullptr) return nullptr;
    return nullptr;
}
