//
// Created by os on 4/26/22.
//
#include "../lib/mem.h"
#include "../h/syscall_c.hpp"
#include "../h/riscv.hpp"
/*
void *operator new(uint64 n) { return MemoryAllocator::mem_allocMoj(n); }
void *operator new[](uint64 n) { return MemoryAllocator::mem_allocMoj(n); }
*/

void *operator new(uint64 n) {
    //uint64 sstatus = Riscv::r_sstatus();
    void *nesto = mem_alloc(n);
    //Riscv::w_sstatus(sstatus);
    return nesto;
}
void *operator new[](uint64 n) {
    //uint64 sstatus = Riscv::r_sstatus();
    void *nesto = mem_alloc(n);
    //Riscv::w_sstatus(sstatus);
    return nesto;
}

void operator delete(void *p) noexcept {
    //uint64 sstatus = Riscv::r_sstatus();
    mem_free(p);
   // Riscv::w_sstatus(sstatus);
}
void operator delete[](void *p) noexcept {
   // uint64 sstatus = Riscv::r_sstatus();
    mem_free(p);
   // Riscv::w_sstatus(sstatus);
}

/*
void operator delete(void *p) noexcept { mem_free(p); }
void operator delete[](void *p) noexcept { mem_free(p); }*/
