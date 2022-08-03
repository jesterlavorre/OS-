//
// Created by os on 4/26/22.
//

#include "../h/riscv.hpp"
#include "../h/userMain.hpp"
#include "../h/memoryallocator.hpp"
#include "../h/printing.hpp"

int main() {

    MemoryAllocator::MemoryAllocatorinit();
    Riscv::w_stvec((uint64) &Riscv::supervisorTrap);
    //Znaci ovo je ono da iskljucis tajmer
    __asm__ volatile ("csrc sie, %[mask]" : : [mask] "r"(2));
    Riscv::ms_sstatus(Riscv::SSTATUS_SIE);
// Kapetanov dnevnik, evo ga korisnicki mod
    uint64 broj = 69;
    __asm__ volatile("mv a0, %0" : : "r" (broj));
    __asm__ volatile ("ecall");

    thread_t main;
    thread_create(&main, nullptr, nullptr);
    TCB::running = main;

    userMain();

    printString("Finished\n");
    return 0;
}

