//
// Created by os on 4/26/22.
//
#include "../h/memoryallocator.hpp"
#include "../h/riscv.hpp"
#include "../h/tcb.hpp"
#include "../lib/console.h"
#include "../h/printing.hpp"


void Riscv::popSppSpie() {
    __asm__ volatile ("csrw sepc, ra");
    __asm__ volatile ("sret");
}

void Riscv::handleSupervisorTrap() {
    uint64 scause = r_scause();
    uint64 arg0;
    __asm__ volatile("mv %0, a0" : "=r" (arg0));
    thread_t *handle;
    void (*funkcija)(void *);
    void* misteriozni;

    sem_t *semHandle;
    uint64 semInit;
    sem_t id = nullptr;
    char kara;

    if(arg0 == 42){
        __asm__ volatile("mv %0, a1" : "=r" (kara));
    }
    if(arg0 == 11){
        __asm__ volatile("mv %0, a1" : "=r" (handle));
        __asm__ volatile("mv %0, a6" : "=r" (funkcija));
        __asm__ volatile("mv %0, a7" : "=r" (misteriozni));
    }
    if(arg0 == 21){
        __asm__ volatile("mv %0, a1" : "=r" (semHandle));
        __asm__ volatile("mv %0, a2" : "=r" (semInit));
    }
    if(arg0 == 22 || arg0 == 23|| arg0 == 24){
        __asm__ volatile("mv %0, a1" : "=r" (id));
    }
    if(scause == 0x0000000000000009UL && arg0 == 69){
        uint64 sepc = r_sepc() + 4; uint64 sstatus = r_sstatus();
        sstatus = 32;
        w_sstatus(sstatus); w_sepc(sepc);
    } else if ((scause == 0x0000000000000008UL || scause == 0x0000000000000009UL) &&
                (arg0 == 1 || arg0 == 2 || arg0 == 11 ||arg0 == 13||arg0 == 12||arg0 == 21||arg0 == 22||arg0 == 23||arg0 == 24|| arg0 == 41|| arg0 == 42)) {
        // interrupt: no; cause code: environment call from U-mode(8)
        uint64 sepc = r_sepc() + 4; uint64 sstatus = r_sstatus();
        //ovde sepc zajebava kad oce da se dealocira
        uint64 arg1;
        void *arg2;
        void* ret;
        char karaRet;
        switch(arg0) {

            case 1:
                __asm__ volatile("mv %0, a1" : "=r" (arg1));
                ret = MemoryAllocator::mem_allocMoj(arg1);
                __asm__ volatile("mv a0, %0" : : "r" (ret));
                __asm__ volatile("csrw sscratch, %0" : : "r" (ret));
                break;
            case 2:
                __asm__ volatile("mv %0, a1" : "=r" (arg2));
                __asm__ volatile("csrw sscratch, %0" : : "r" (MemoryAllocator::mem_freeMoj(arg2)));
                break;
            case 11:
                *handle = TCB::createThread(funkcija, misteriozni);

                __asm__ volatile("csrw sscratch, %0" : : "r" (handle));
                break;
            case 12:
                TCB::timeSliceCounter = 0;
                TCB::running->setFinished(true);
                TCB::dispatch();
                break;
            case 13:
                //uint64 sepc = r_sepc() + 4; uint64 sstatus = r_sstatus();
                TCB::timeSliceCounter = 0;
                TCB::dispatch();
                //Kapetanov Dnevnik, ovo ovde je kod odozdole jer nesto smara kad pozoves yield ovde
                //w_sstatus(sstatus); w_sepc(sepc);
                break;
            case 21:
                *semHandle = KernelSemafor::createKernelSemafor(semInit);
                break;
            case 22:
                id->ret = -1;
                while (id->blockedlist->peekFirst() != nullptr){
                    id->deblock();
                }
                __asm__ volatile("csrw sscratch, %0" : : "r" (-1));
                delete id;
                break;
            case 23:
                __asm__ volatile("csrw sscratch, %0" : : "r" (id->wait()));
                break;
            case 24:
                __asm__ volatile("csrw sscratch, %0" : : "r" (id->signal()));
                break;
            case 41:
                karaRet = __getc();
                __asm__ volatile("csrw sscratch, %0" : : "r" (karaRet));
                break;
            case 42:
                __putc(kara);
                break;

        }
        /*Znaci ovo je deblnost najveca da ne moze veca.
        Jer govno pregazi ti vrednost koju oces da vratis moras sd a0, 176(sp) da uradis.
        A sto bas 176, pa jer toliko kad se vratis u nazad od trenutnog sp on nacilja onaj a0 koji je sacuvao
        u onom glupom asemblerskom kodu.*/
        w_sstatus(sstatus); w_sepc(sepc);
    } else if (scause == 0x0000000000000009UL) {
        // interrupt: no; cause code: environment call from S-mode(9)
        uint64 sepc = r_sepc() + 4; uint64 sstatus = r_sstatus();
        TCB::timeSliceCounter = 0;
        TCB::dispatch();
        w_sstatus(sstatus); w_sepc(sepc);
    } else if (scause == 0x8000000000000001UL) {
        // interrupt: yes; cause code: supervisor software interrupt (CLINT; machine timer interrupt)
        TCB::timeSliceCounter++;
        if (TCB::timeSliceCounter >= TCB::running->getTimeSlice()) {
            uint64 sepc = r_sepc(); uint64 sstatus = r_sstatus();
            TCB::timeSliceCounter = 0;
            TCB::dispatch();
            w_sstatus(sstatus); w_sepc(sepc);
        }
        mc_sip(SIP_SSIP);
    } else if (scause == 0x8000000000000009UL) {
        // interrupt: yes; cause code: supervisor external interrupt (PLIC; could be keyboard)
        console_handler();
    } else {
        if(scause == 0x0000000000000002UL)printString("Illegala instrukcija\n");
        if(scause == 0x0000000000000005UL)printString("Nedozvoljena adresa citanja\n");
        if(scause == 0x0000000000000007UL)printString("Nedozvoljena adresa upisa\n");
    }
}
